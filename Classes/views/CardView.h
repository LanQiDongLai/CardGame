#pragma once

#include "cocos2d.h"
#include "models/CardModel.h"

USING_NS_CC;

class CardView: public Sprite {
public:
  CardView(CardModel& card);
  ~CardView();
  void updateView(CardModel& card);
  void playFlipAnimation(CardModel& card);
  void playMoveAnimation(Vec2 new_position);
  void setClickCallBack(std::function<void()> callback);
 private:
  std::string getCardGeneralResourcePath(CardModel& card);
  std::string getSuitResourcePath(CardModel& card);
  std::string getNumberResourcePath(CardModel& card, bool is_big);

  void onMouseUp(Event* event);
  void onMouseDown(Event* event);

  std::function<void()> click_callback_;
  CardModel& card_;
};