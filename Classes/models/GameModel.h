#pragma once

#include "cocos2d.h"
#include "models/CardModel.h"
#include <stack>
#include <vector>

USING_NS_CC;

// 游戏模型类，包含了游戏的基本数据结构和状态信息
class GameModel {
 private:
  GameModel();
 public:
  static GameModel *create();
  ~GameModel();

  void addTableCard(CardModel *card);
  void removeTableCard(int card_id);

  void pushPlayerHandCard(CardModel *card);
  CardModel* popPlayerHandCard();
  bool isPlayerHandEmpty() const;

  void pushBackupCard(CardModel *card);
  void popBackupCard();
  bool isBackupEmpty() const;

  CardModel* getTopBackupCard();
  CardModel* getTopPlayerHandCard();

 private:
  std::stack<CardModel*> player_hand_cards_;
  std::stack<CardModel*> backup_cards_;
  std::vector<CardModel*> table_cards_;
};