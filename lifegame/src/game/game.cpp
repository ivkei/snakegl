#include"game.h"

#include"renderer/renderer.h"
#include"logic/logic.h"

#include<filesystem>

SGE::Window::Stats Game::WindowStats = {"SnakeGL", 1280, 720, false};

static std::unique_ptr<Field> GetInitField(){
  return std::make_unique<Field>(128, 72, 0.95f, 0.95f, 0.025f, 0.025f,
                                 glm::vec4(0.0f, 0.0f, 0.0f, 1.0), glm::vec4(0.1f, 0.1f, 0.1f, 1.0f), glm::vec4(0.85f, 0.08f, 0.2f, 1.0f),
                                 128);
}

void Game::Reset(){
  _pField = GetInitField();
}

Game::Game(SGE::Window& window)
: _pField(GetInitField()){
  window.SetVSync(false);

  TSRenderer::Instance()->SetupShadersAndCoord(*_pField);
  TSLogic::Instance()->SetKeyCallbacks(&window, this);
}

Game::~Game(){
}

static float fpsTimer = 1;
static float fpsFrames = 0;

static const float logicEverySeconds = TSLogic::Instance()->ExecuteEverySeconds;
static float logicTimer = logicEverySeconds;

void Game::OnUpdate(float deltaSeconds){
  ++fpsFrames;
  fpsTimer -= deltaSeconds;

  //Move
  logicTimer -= deltaSeconds;
  if (logicTimer <= 0){
    TSLogic::Instance()->Execute(*_pField, *this);
    logicTimer = logicEverySeconds;
  }

  TSRenderer::Instance()->Render(*_pField);

  //Fps (debug)
  if (fpsTimer <= 0){
    SGE_LOG_INFO("FPS: ", fpsFrames);
    fpsFrames = 0;
    fpsTimer = 1;
  }
}
