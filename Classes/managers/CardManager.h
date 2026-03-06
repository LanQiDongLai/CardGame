#pragma once

#include "cocos2d.h"
#include "models/CardModel.h"
#include "views/CardView.h"
USING_NS_CC;

class CardManager {
 public:
  static CardManager* getInstance() {
    static CardManager instance;
    return &instance;
  }

  void addCardView(int card_id, CardView* card_view) {
    card_views_[card_id] = card_view;
  }

  CardView* getCardView(int card_id) {
    auto it = card_views_.find(card_id);
    if (it != card_views_.end()) {
      return it->second;
    }
    return nullptr;
  }

 private:
  CardManager() {}
  std::unordered_map<int, CardView*> card_views_;
};