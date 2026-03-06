#include "managers/CardManager.h"

CardManager::CardManager() {
}

CardManager* CardManager::getInstance() {
  static CardManager instance;
  return &instance;
}

void CardManager::addCardView(int card_id, CardView* card_view) {
  card_views_[card_id] = card_view;
}

CardView* CardManager::getCardView(int card_id) {
  auto it = card_views_.find(card_id);
  if (it != card_views_.end()) {
    return it->second;
  }
  return nullptr;
}