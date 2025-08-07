#include"game.h"

#include"renderer/renderer.h"
#include"logic/logic.h"

#include<filesystem>

SGE::Window::Stats SnakeGame::WindowStats = {"SnakeGL", 720, 792, false};

static std::unique_ptr<Snake> GetInitSnake(SnakeGame& game){
  return std::make_unique<Snake>(3, glm::vec2(3, 5), glm::ivec2(-1, 0), glm::vec4(0.67f,0.85f,0.93f,1.0f), glm::ivec2(1, 0));
}

static std::unique_ptr<AppleManager> GetInitAppleManager(Field& field, Snake& snake){
  return std::make_unique<AppleManager>(field, snake, 5, glm::vec4(0.85f, 0.45f, 0.45f, 1.0f));
}

static std::unique_ptr<Field> GetInitField(){
  return std::make_unique<Field>(10, 11, 0.95f, 0.95f, 0.025f, 0.025f, glm::vec4(0.43f, 0.76f, 0.46f, 1.0), glm::vec4(0.025f, 0.25f, 0.167f, 1.0f));
}

void SnakeGame::Reset(){
  _pSnake = GetInitSnake(*this);
  _pAppleManager = GetInitAppleManager(*_pField, *_pSnake);
}

SnakeGame::SnakeGame(SGE::Window& window)
: _pField(GetInitField()),
  _pAppleManager(nullptr),
  _pSnake(GetInitSnake(*this)){
  window.SetVSync(false);

  _pAppleManager = GetInitAppleManager(*_pField, *_pSnake);

  TSRenderer::Instance()->SetupShadersAndCoord(*_pField);
  TSLogic::Instance()->SetKeyCallbacks(&window, _pSnake.get(), this);
}

SnakeGame::~SnakeGame(){
}

static float fpsTimer = 1;
static float fpsFrames = 0;

static const float snakeMovesEverySeconds = TSLogic::Instance()->ExecuteEverySeconds;
static float snakeMoveTimer = snakeMovesEverySeconds;

void SnakeGame::OnUpdate(float deltaSeconds){
  ++fpsFrames;
  fpsTimer -= deltaSeconds;

  //Move
  snakeMoveTimer -= deltaSeconds;
  if (snakeMoveTimer <= 0){
    TSLogic::Instance()->Execute(*_pSnake, *_pField, *_pAppleManager, *this);
    snakeMoveTimer = snakeMovesEverySeconds;
  }

  TSRenderer::Instance()->Render(*_pSnake, *_pField, *_pAppleManager);

  //Fps (debug)
  if (fpsTimer <= 0){
    SGE_LOG_INFO("FPS: ", fpsFrames);
    fpsFrames = 0;
    fpsTimer = 1;
  }
}
