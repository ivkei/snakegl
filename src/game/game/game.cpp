#include"game.h"

#include"glm/gtc/matrix_transform.hpp"

#include<filesystem>

static std::unique_ptr<Snake> GetInitSnake(Game& game){
  return std::make_unique<Snake>(3, glm::vec2(3, 5), glm::vec2(-1, 0), [&](){game.Reset();}, [&](){game.Reset();});
}

static std::unique_ptr<AppleManager> GetInitAppleManager(Field& field, Snake& snake){
  return std::make_unique<AppleManager>(field, snake, 5);
}

void Game::Reset(){
  _pSnake = GetInitSnake(*this);
  _pAppleManager = GetInitAppleManager(*_pField, *_pSnake);
}

Game::Game(SGE::Window& window)
: _pField(new Field(10, 11, 0.95f, 0.95f, 0.025f, 0.025f, glm::vec4(0.43f, 0.76f, 0.46f, 1.0), glm::vec4(0.025f, 0.25f, 0.167f, 1.0f))),
  _pAppleManager(nullptr),
  _pSnake(GetInitSnake(*this)){
  window.SetVSync(false);

  SGE_LOG_INFO("Start creating proj mat");
  glm::mat4 proj = glm::ortho(0.0f, (float)_pField->Width(), 0.0f, (float)_pField->Height(), -1.0f, 1.0f);
  SGE_LOG_INFO("Done creating proj mat");

  SGE_LOG_INFO("Start specifying shaders");

  std::filesystem::path execDir = SGE::GetExecDir();

  SGE_LOG_INFO("Exec dir: ", execDir.string());

  SGE::TSRenderer::Instance()->FragShader((execDir / RES_DIR / "shaders/fragP.glsl").string().c_str(), true); //Indirect because windows likes to return wchar* instead of char*
  SGE::TSRenderer::Instance()->VertShader((execDir / RES_DIR / "shaders/vertP.glsl").string().c_str(), true);
  SGE::TSRenderer::Instance()->Uniform("uProj", proj);

  SGE_LOG_INFO("Done specifying shaders");

  SGE_LOG_INFO("Shader dir: ", (execDir / RES_DIR / "shaders"));

  _pAppleManager = GetInitAppleManager(*_pField, *_pSnake);

  window.SetKeyCallback(SNAKEGL_KEY_W, [&](){_pSnake->QueryMoveUp();});
  window.SetKeyCallback(SNAKEGL_KEY_A, [&](){_pSnake->QueryMoveLeft();});
  window.SetKeyCallback(SNAKEGL_KEY_S, [&](){_pSnake->QueryMoveDown();});
  window.SetKeyCallback(SNAKEGL_KEY_D, [&](){_pSnake->QueryMoveRight();});
  window.SetKeyCallback(SNAKEGL_KEY_ESC, [&](){Reset();});
  window.SetKeyCallback(SNAKEGL_KEY_SPC, [&](){Reset();});
}

Game::~Game(){
}

static float fpsTimer = 1;
static float fpsFrames = 0;

static const float snakeMovesEverySeconds = 0.2f;
static float snakeMoveTimer = snakeMovesEverySeconds;

void Game::OnUpdate(float deltaSeconds){
  ++fpsFrames;
  fpsTimer -= deltaSeconds;

  //Move
  snakeMoveTimer -= deltaSeconds;
  if (snakeMoveTimer <= 0){
    _pSnake->Move(*_pField, *_pAppleManager);
    snakeMoveTimer = snakeMovesEverySeconds;
  }

  _pField->Draw();
  _pSnake->Draw(*_pField);
  _pAppleManager->DrawApples(*_pField);
  SGE::TSRenderer::Instance()->Render();

  //Fps (debug)
  if (fpsTimer <= 0){
    SGE_LOG_INFO("FPS: ", fpsFrames);
    fpsFrames = 0;
    fpsTimer = 1;
  }
}
