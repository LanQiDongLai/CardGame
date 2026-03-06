#include "views/UndoButtonView.h"
#include "UndoButtonView.h"

UndoButtonView::UndoButtonView() {
}

void UndoButtonView::initTouchListener() {
  touch_listener_ = EventListenerTouchOneByOne::create();
  touch_listener_->setSwallowTouches(true);
  touch_listener_->onTouchBegan = CC_CALLBACK_2(UndoButtonView::onTouchBegan, this);
  touch_listener_->onTouchEnded = CC_CALLBACK_2(UndoButtonView::onTouchEnded, this);
  _eventDispatcher->addEventListenerWithSceneGraphPriority(touch_listener_, this);
}

UndoButtonView *UndoButtonView::create() {
  UndoButtonView* undo_button_view = new UndoButtonView();
  if (!undo_button_view || !undo_button_view->init()) {
    CC_SAFE_DELETE(undo_button_view);
    return nullptr;
  }
  undo_button_view->autorelease();
  undo_button_view->initTouchListener();
  undo_button_view->updateView();
  return undo_button_view;
}

UndoButtonView::~UndoButtonView() {
}

void UndoButtonView::updateView() {
  this->setContentSize(Size(100, 50));
  this->removeAllChildrenWithCleanup(true);
  auto button_background = LayerColor::create(Color4B::BLUE, 100, 50);
  this->addChild(button_background, 0);
  this->setPosition(Vec2(800, 300));
  auto button_label = Label::createWithSystemFont("Undo", "Arial", 24);
  button_label->setPosition(Vec2(50, 25));
  this->addChild(button_label, 1);
}

void UndoButtonView::setCallback(std::function<void()> callback) {
  callback_ = callback;
}

bool UndoButtonView::onTouchBegan(Touch* touch, Event* event) {
  Vec2 locationInNode = this->convertToNodeSpace(touch->getLocation());
  Size size = this->getContentSize();
  Rect rect = Rect(0, 0, size.width, size.height);
  if (rect.containsPoint(locationInNode)) {
    if (callback_) {
      callback_();
    }
    return true;
  }
  return false;
}

void UndoButtonView::onTouchEnded(Touch* touch, Event* event) {
}