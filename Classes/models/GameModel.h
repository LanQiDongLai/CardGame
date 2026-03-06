#pragma once

#include "cocos2d.h"
#include "models/CardModel.h"
#include <stack>
#include <vector>

USING_NS_CC;

class GameModel : public Ref {
 private:
  GameModel();
 public:
  static GameModel *create();
  ~GameModel();

  void addTableCard(CardModel *card);
  void removeTableCard(int card_id);

  void pushPlayerHandCard(CardModel *card);
  void popPlayerHandCard(int card_id);

  void pushBackupCard(CardModel *card);
  void popBackupCard();
  bool isBackupEmpty() const;
  CardModel* getTopBackupCard();

 private:
  std::stack<CardModel*> player_hand_cards_;
  std::stack<CardModel*> backup_cards_;
  std::vector<CardModel*> table_cards_;
};