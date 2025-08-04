#include"game.h"

#include"glm/gtc/matrix_transform.hpp"

Game::Game(SGE::Window& window, std::string execDir){
  window.SetVSync(false);

  SGE_LOG_INFO("Start creating proj mat");
  glm::mat4 proj = glm::ortho(0.0f, (float)window.Width(), 0.0f, (float)window.Height(), -1.0f, 1.0f);
  SGE_LOG_INFO("Done creating proj mat");

  SGE_LOG_INFO("Start specifying shaders");

  SGE::TSRenderer::Instance()->FragShader((execDir + RES_DIR + "shaders/fragP.glsl").c_str());
  SGE::TSRenderer::Instance()->VertShader((execDir + RES_DIR + "shaders/vertP.glsl").c_str());
  SGE::TSRenderer::Instance()->Uniform("uProj", proj);

  SGE_LOG_INFO("Done specifying shaders");

  SGE_LOG_INFO("Shader dir: ", (execDir + RES_DIR + "shaders/"));
}

Game::~Game(){
}

static float timer = 1;
static float frames = 0;

void Game::OnUpdate(float deltaSeconds){
  ++frames;
  timer -= deltaSeconds;

  SGE::TSRenderer::Instance()->Clear();
  SGE::TSRenderer::Instance()->Quad(glm::vec2(100, 100), glm::vec2(200, 200), glm::vec4(0.2f, 0.8f, 0.6f, 1.0f));
  SGE::TSRenderer::Instance()->Circle(glm::vec2(400, 500), 100, 30, true);
  SGE::TSRenderer::Instance()->Circle(glm::vec2(0, 0), 100, 30, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
  SGE::TSRenderer::Instance()->Circle(glm::vec2(720, 720), 100, 30, glm::vec4(0.8f, 0.2f, 0.0f, 1.0f), glm::vec4(0.5f, 0.8f, 0.0f, 1.0f));
  SGE::TSRenderer::Instance()->Trig(glm::vec2(100, 400), glm::vec2(100, 100), glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
  SGE::TSRenderer::Instance()->Render();

  if (timer <= 0){
    SGE_LOG_INFO("FPS: ", frames);
    frames = 0;
    timer = 1;
  }
}
