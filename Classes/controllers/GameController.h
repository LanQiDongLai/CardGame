#pragma once

#include "cocos2d.h"
#include "views/GameView.h"
#include "configs/LevelConfig.h"
#include "managers/CardManager.h"
#include <string>

USING_NS_CC;
class GameController {
 private:
  GameController(GameView *game_view);

 public:
  static GameController *create();
  ~GameController();
  void startGame(int level);
  void handleCardClick(int card_id);
  void handleUndoButtonClick();

 private:
  void initCards(const LevelConfig &level_config);
  CardManager *card_manager_;
  GameView *game_view_;
};