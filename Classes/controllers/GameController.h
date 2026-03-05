#pragma once

#include "views/GameView.h"
#include <string>

class GameController {
 private:
  GameController(GameView *game_view);

 public:
  static GameController *create();
  ~GameController();
  void startGame(std::string level_path);
  void handleCardClick(int card_id);
  void handleUndoButtonClick();

 private:
  GameView *game_view_;
};