#include"game.h"

Game::Game(SGE::Window& window){
  window.SetVSync(false);
  window.SetStats({"SnakeGL", 720, 720});
}

Game::~Game(){
}

static float timer = 1;
static float frames = 0;

void Game::OnUpdate(float deltaSeconds){
  ++frames;
  timer -= deltaSeconds;

  if (timer <= 0){
    SGE_LOG_INFO("FPS: ", frames);
    frames = 0;
    timer = 1;
  }
}
