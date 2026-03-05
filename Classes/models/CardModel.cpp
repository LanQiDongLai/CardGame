#include "models/CardModel.h"

CardModel::CardModel() {
  suit_type_ = CardSuitType::CST_NONE;
  number_ = 0;
  face_type_ = CardFaceType::CFT_NONE;
  card_stage_ = CardStage::CS_NONE;
  position_ = {0, 0};
  is_face_down_ = true;
}

CardModel::~CardModel() {}

CardModel::CardModel(int number, CardSuitType suit_type, CardStage stage,
                     Vec2 position, bool is_face_down) {
  number_ = number;
  suit_type_ = suit_type;
  card_stage_ = stage;
  face_type_ = CardFaceType(CFT_NONE + number);
  position_ = position;
  is_face_down_ = is_face_down;
}

CardModel *CardModel::create(int number, CardSuitType suit_type, CardStage stage,
                              Vec2 position, bool is_face_down) {
  CardModel* card_model = new CardModel(number, suit_type, stage, position,
                                        is_face_down);
  if (card_model) {
    card_model->autorelease();
    return card_model;
  }
  CC_SAFE_DELETE(card_model);
  return nullptr;
}

void CardModel::setNumber(int number) {
  number_ = number;
  face_type_ = CardFaceType(CFT_NONE + number);
}

void CardModel::setSuitType(CardSuitType suit_type) { suit_type_ = suit_type; }

void CardModel::setCardStage(CardStage stage) { card_stage_ = stage; }

void CardModel::setPosition(Vec2 position) { position_ = position; }

void CardModel::setFaceDirection(bool is_face_down) {
  is_face_down_ = is_face_down;
}

int CardModel::getNumber() { return number_; }

CardSuitType CardModel::getCardSuitType() { return suit_type_; }

CardStage CardModel::getCardStage() { return card_stage_; }

Vec2 CardModel::getPosition() { return position_; }

CardFaceType CardModel::getCardFaceType() { return face_type_; }

bool CardModel::isFaceDown() {
  return is_face_down_;
}

int CardModel::getId() {
  return (intptr_t)this;
}