#include "views/UndoButtonView.h"

UndoButtonView::UndoButtonView() {
  updateView();
}

UndoButtonView *UndoButtonView::create() {
  UndoButtonView* undo_button_view = new UndoButtonView();
  if (undo_button_view && undo_button_view->init()) {
    undo_button_view->autorelease();
    return undo_button_view;
  }
  CC_SAFE_DELETE(undo_button_view);
  return nullptr;
}

UndoButtonView::~UndoButtonView() {
}

void UndoButtonView::updateView() {
}

void UndoButtonView::setCallback(std::function<void()> callback) {
  callback_ = callback;
}

void UndoButtonView::onButtonClicked(Touch* touch, Event* event) {
  if (callback_) {
    callback_();
  }
}