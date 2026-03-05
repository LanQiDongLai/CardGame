#pragma once

#include "cocos2d.h"

USING_NS_CC;

class UndoButtonView: public Sprite {
 private:
  UndoButtonView();
  void initTouchListener();
 public:
  static UndoButtonView* create();
  ~UndoButtonView();

  void updateView();

  void setCallback(std::function<void()> callback);

 private:
  bool onTouchBegan(Touch* touch, Event* event);
  void onTouchEnded(Touch* touch, Event* event);

  std::function<void()> callback_;
  EventListenerTouchOneByOne* touch_listener_;
};