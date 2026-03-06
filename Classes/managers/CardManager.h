#pragma once

#include "cocos2d.h"
#include "models/CardModel.h"
#include "views/CardView.h"
USING_NS_CC;

class CardManager {
 private:
  CardManager();
 public:
  ~CardManager();
  static CardManager* create();

  void addCardView(int card_id, CardView* card_view);

  CardView* getCardView(int card_id);

 private:
  std::unordered_map<int, CardView*> card_views_;
};