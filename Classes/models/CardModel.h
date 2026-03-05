#pragma once

#include "cocos2d.h"
#include "utils/CommonDef.h"

USING_NS_CC;

class CardModel : public Ref {
 private:
  CardModel();
  CardModel(int number, CardSuitType suit_type, CardStage stage,
            Vec2 position, bool is_face_down);
 public:
  static CardModel *create(int number, CardSuitType suit_type, CardStage stage,
                     Vec2 position, bool is_face_down);
  ~CardModel();
  void setNumber(int number);
  void setSuitType(CardSuitType suit_type);
  void setCardStage(CardStage stage);
  void setPosition(Vec2 position);
  void setFaceDirection(bool is_face_down);

  int getNumber();
  CardSuitType getCardSuitType();
  CardStage getCardStage();
  Vec2 getPosition();
  CardFaceType getCardFaceType();
  bool isFaceDown();
  int getId();

 private:
  CardSuitType suit_type_;
  CardFaceType face_type_;
  CardStage card_stage_;
  Vec2 position_;
  bool is_face_down_;
  int number_;
};