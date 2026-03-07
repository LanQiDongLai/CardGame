#pragma once

#include "models/GameModel.h"
#include "views/CardView.h"
#include "views/UndoButtonView.h"
#include "cocos2d.h"

USING_NS_CC;

// 游戏视图类，负责显示游戏界面，包括桌面牌、玩家手牌、备份牌和撤销按钮等元素
class GameView: public Layer {
 private:
  GameView(GameModel* game_model);
 public:
  static GameView *create(GameModel* game_model);
  ~GameView();

  void addTableCard(CardView *card);
  void addBackupCard(CardView *card);
  void addUndoButton(UndoButtonView *undo_button);

  GameModel* getGameModel();

 private:

  std::function<void()> undo_button_callback_;

  Vector<CardView*> table_card_sprites_;
  Vector<CardView*> player_hand_card_sprites_;
  Vector<CardView*> backup_card_sprites_;

  EventListenerTouchOneByOne* undo_button_touch_listener_;

  GameModel* game_model_;
};