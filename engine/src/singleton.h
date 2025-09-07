#pragma once

#include<cstdlib>
#include<thread>
#include<mutex>

namespace SGE{

//Phoenix Singleton (after it destroyed, it can be created again, if the program requires one (Ex: Logger, that got destroyed and had to log destruction of another singleton))
class PhoenixSingleton {
  private:
  inline static PhoenixSingleton* _pInstance = nullptr;
  inline static bool _isDestroyed = false;
  PhoenixSingleton() = default;
  ~PhoenixSingleton() { //private dtor, so pointer to _pInstance cant be deleted
    _isDestroyed = true;
    _pInstance = nullptr; //No delete because the OS clears the left over data on the heap after the execution of the program
  }
  static void ClearLeftData(){
    _pInstance->~PhoenixSingleton();
  }
  public:
  PhoenixSingleton(PhoenixSingleton&&) = delete; //Explicitly delete the move ctor so other special methods dont get generated
  static PhoenixSingleton& Instance() { //Reference returned because operator= is deleted
    if (_pInstance == nullptr){
      if (_isDestroyed){
        _isDestroyed = false;
        new (_pInstance) PhoenixSingleton; //Syntax for new to create new but dont allocate memory
      }
      else{
        _pInstance = new PhoenixSingleton();
      }
      atexit(ClearLeftData);
    }
    return *_pInstance;
  }
};

//Priority Singleton
//Sets priority of destruction when created so multiple singletons are fully customizable in destruction way
//Always destroyed via atexit unlike Phoenix Singleton, that is destroyed after program execution

class PolymorphicLifetimeTracker{ //Choice between struct that stores void* and size and deletes the ptr, or polymorphic class with vtables (for deleteSet)
  private:
  int _priority;
  public:
  PolymorphicLifetimeTracker(int priority)
  : _priority(priority){

  }
  virtual ~PolymorphicLifetimeTracker() = default;
  bool operator>(const PolymorphicLifetimeTracker& other) const {
    return _priority > other._priority;
  }
  bool operator<(const PolymorphicLifetimeTracker& other) const {
    return _priority < other._priority;
  }
};
template<class T>
class ObjectLifetimeTracker : public PolymorphicLifetimeTracker{
  private:
  T* _pDynObj;
  public:
  ObjectLifetimeTracker(T* pDynObj, int priority)
  : PolymorphicLifetimeTracker(std::move(priority)),
   _pDynObj(std::move(pDynObj)){

  }
  ~ObjectLifetimeTracker() override{
    delete _pDynObj;
  }
};
template<class Func>
class FunctionLifetimeTracker : public PolymorphicLifetimeTracker{
  private:
  Func _func;
  public:
  FunctionLifetimeTracker(Func func, int priority)
  : PolymorphicLifetimeTracker(std::move(priority)),
  _func(std::move(func)){

  }
  ~FunctionLifetimeTracker() override{
    _func();
  }
};
class LifetimeTrackerPtr{
  private:
  PolymorphicLifetimeTracker* _pTracked;
  public:
  LifetimeTrackerPtr(PolymorphicLifetimeTracker* tracked)
  : _pTracked(std::move(tracked)){

  }
  bool operator>(const LifetimeTrackerPtr& other) const {
    return *_pTracked > *other._pTracked;
  }
  bool operator<(const LifetimeTrackerPtr& other) const {
    return *_pTracked < *other._pTracked;
  }
  ~LifetimeTrackerPtr(){
    delete _pTracked;
  }
};
#include<set>
static std::multiset<LifetimeTrackerPtr> deleteSet;
//Pops values 1 by 1 in order of priority (< -> >)
static void ClearPriorityData(){
  deleteSet.erase(deleteSet.begin());
}
//Sets the order for destructing specific objects at the end of program
template<class T>
void SetPriorityOfObj(T* pDynObj, int priority){
  deleteSet.emplace(new ObjectLifetimeTracker<T>(std::move(pDynObj), std::move(priority)));
  std::atexit(ClearPriorityData);
}
//Executes function in same priority list as objects destruction
template<class Func>
void SetPriorityOfFunc(Func func, int priority){
  deleteSet.emplace(new FunctionLifetimeTracker<Func>(std::move(func), std::move(priority)));
  std::atexit(ClearPriorityData);
}

class PrioritySingleton{
  private:
  inline static PrioritySingleton* _pInstance = nullptr;
  PrioritySingleton() = default;
  //~PrioritySingleton() = default; //Cant have private dtor because else LifetimeTracker doesnt work
  inline static constexpr int _PRIORITY = 2;
  public:
  PrioritySingleton(PrioritySingleton&&) = delete;
  static PrioritySingleton* const Instance(){
    if (_pInstance == nullptr){
      _pInstance = new PrioritySingleton();
      SetPriorityOfObj(_pInstance, _PRIORITY);
    }
    return _pInstance;
  }
  ~PrioritySingleton(){
  }
};

//Singleton

struct EmptyType{
  EmptyType(...) {}
};
template<class T>
struct CreateNew{
  static T* Create(){
    return new T();
  }
  static void Delete(volatile T* pObj){
    delete pObj;
  }
};
template<class T>
struct PhoenixLifetime{
  static void ScheduleDestruction(void(*deleteFunc)(void)){
    std::atexit(deleteFunc);
  }
};
template<class T>
struct PriorityLifetime{
  static void ScheduleDestruction(void(*deleteFunc)(void)){
    SetPriorityOfFunc(std::move(deleteFunc), GetPriority<T>());
  }
};
template<class T>
struct InfiniteLifetime{
  static void ScheduleDestruction(void(*deleteFunc)(void)){}
};
template<class T>
struct SingleThreaded{
  using SingletonInstance = T;
  using LockGuard = EmptyType;
  inline static const EmptyType mutex{};
};
template<class T>
struct MultiThreaded{
  using SingletonInstance = T;
  using LockGuard = std::lock_guard<std::mutex>;
  inline static std::mutex mutex{};
};

template<
  class T,
  template<class>class LifetimePolicy = PhoenixLifetime,
  template<class>class CreationPolicy = CreateNew,
  template<class>class ThreadingModel = MultiThreaded
>
class Singleton{
  private:
  Singleton() = default;
  using InstanceType = typename ThreadingModel<T>::SingletonInstance;
  using GuardType = typename ThreadingModel<T>::LockGuard;
  inline static InstanceType* _pInstance = nullptr;
  static void DestroySingleton(){
    if (_pInstance != nullptr){
      CreationPolicy<T>::Delete(_pInstance);
      _pInstance = nullptr;
    }
  }
  public:
  Singleton(Singleton&&) = delete;
  static InstanceType* const Instance(){
    if (_pInstance == nullptr){
      GuardType potentialGuard(ThreadingModel<T>::mutex);
      if (_pInstance == nullptr){
        _pInstance = CreationPolicy<T>::Create();
        LifetimePolicy<T>::ScheduleDestruction(DestroySingleton);
      }
    }
    return _pInstance;
  }
};

}
