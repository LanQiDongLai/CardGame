#include "controllers/GameController.h"
#include <iostream>

GameController::GameController(GameView *game_view) : game_view_(game_view) {
}

GameController::~GameController() {
}

GameController *GameController::create() {
  auto game_view = GameView::create();
  return new GameController(game_view);
}

void GameController::startGame(std::string level_path) {
  std::cout << "Starting game with level: " << level_path << std::endl;
}

void GameController::handleCardClick(int card_id) {
  std::cout << "Card clicked with ID: " << card_id << std::endl;
}

void GameController::handleUndoButtonClick() {
  std::cout << "Undo button clicked" << std::endl;
}