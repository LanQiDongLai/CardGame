#pragma once

#include "cocos2d.h"
#include "utils/CommonDef.h"

USING_NS_CC;

struct CardConfig : public Ref {
  int number;
  CardSuitType suit_type;
  CardStage stage;
  Vec2 position;
};

class LevelConfig {
 public:

  int getLevel() const;
  void setLevel(int level);

  Vector<CardConfig*> getPlayfieldCards() const;
  void addPlayfieldCards(CardConfig *card);

 private:
  int level_;
  Vector<CardConfig*> playfield_cards_;
};