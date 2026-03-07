#pragma once

#include "cocos2d.h"

USING_NS_CC;

// 撤销按钮视图类，负责显示撤销按钮，并处理用户的点击事件
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