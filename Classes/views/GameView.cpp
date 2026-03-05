#include "views/GameView.h"

GameView::GameView() {
}

GameView *GameView::create() {
  GameView* game_view = new GameView();
  if (game_view && game_view->init()) {
    game_view->autorelease();
    return game_view;
  }
  CC_SAFE_DELETE(game_view);
  return nullptr;
}

GameView::~GameView() {
}

void GameView::addTableCard(CardView *card) {
  table_card_sprites_.pushBack(card);
  addChild(card);
}

void GameView::addPlayerHandCard(CardView *card) {
  player_hand_card_sprites_.pushBack(card);
  addChild(card);
}

void GameView::addBackupCard(CardView *card) {
  backup_card_sprites_.pushBack(card);
  addChild(card);
}

void GameView::addUndoButton(UndoButtonView *undo_button) {
  addChild(undo_button);
}