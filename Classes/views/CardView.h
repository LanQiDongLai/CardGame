#pragma once

#include "cocos2d.h"
#include "models/CardModel.h"

USING_NS_CC;

class CardView: public Sprite {
private:
  CardView(CardModel& card);
  void initTouchListener();
public:
  ~CardView();
  static CardView* create(CardModel& card);
  void updateView(CardModel& card);
  void playFlipAnimation(CardModel& card);
  void playMoveAnimation(Vec2 new_position);
  void setClickCallBack(std::function<void()> callback);
 private:
  std::string getCardGeneralResourcePath(CardModel& card);
  std::string getSuitResourcePath(CardModel& card);
  std::string getNumberResourcePath(CardModel& card, bool is_big);

  bool onTouchBegan(Touch* touch, Event* event);
  void onTouchEnded(Touch* touch, Event* event);

  std::function<void()> click_callback_;
  CardModel& card_;
  EventListenerTouchOneByOne* touch_listener_;
};