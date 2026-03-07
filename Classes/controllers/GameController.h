#pragma once

#include "cocos2d.h"
#include "views/GameView.h"
#include "configs/LevelConfig.h"
#include "managers/CardManager.h"
#include "managers/UndoManager.h"
#include <string>

USING_NS_CC;

// 游戏控制器，负责游戏的整体流程控制，包括初始化游戏界面、设置精灵鼠标事件的回调函数、处理游戏逻辑等

class GameController {
 private:
  GameController(GameView *game_view);

 public:
  static GameController *create();
  ~GameController();
  // 开始游戏
  void startGame(int level);
  // 处理备份牌点击事件
  void handleBackUpCardClick(int card_id);
  // 处理桌面牌点击事件
  void handleTableCardClick(int card_id);
  // 处理撤销按钮点击事件
  void handleUndoButtonClick();

 private:
  // 初始化游戏界面上的牌
  void initCards(const LevelConfig &level_config);
  CardManager *card_manager_;
  UndoManager *undo_manager_;
  GameView *game_view_;
};