#pragma once

#include "cocos2d.h"

USING_NS_CC;

class UndoButtonView: public Sprite {
 private:
  UndoButtonView();
 public:
  static UndoButtonView* create();
  ~UndoButtonView();

  void updateView();

  void setCallback(std::function<void()> callback);

 private:
  void onButtonClicked(Touch* touch, Event* event);

  std::function<void()> callback_;
  EventListenerTouchOneByOne* touch_listener_;
};