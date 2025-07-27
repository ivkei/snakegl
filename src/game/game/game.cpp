#include"game.h"

Game::Game(SGE::Window& window){
}

Game::~Game(){
}

void Game::OnUpdate(float deltaSeconds){
  SGE_LOG_SUCCESS(std::fixed, "Update: ", deltaSeconds);
}
