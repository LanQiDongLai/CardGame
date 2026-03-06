#include "configs/LevelConfig.h"

int LevelConfig::getLevel() const {
  return level_;
}

void LevelConfig::setLevel(int level) {
  level_ = level;
}

Vector<CardConfig*> LevelConfig::getPlayfieldCards() const {
  return playfield_cards_;
}

void LevelConfig::addPlayfieldCards(CardConfig *card) {
  playfield_cards_.pushBack(card);
}

Vector<CardConfig*> LevelConfig::getStackCards() const {
  return stack_cards_;
}

void LevelConfig::addStackCards(CardConfig *card) {
  stack_cards_.pushBack(card);
}