#include "views/GameView.h"

GameView::GameView(GameModel* game_model): game_model_(game_model) {
}

GameView *GameView::create(GameModel* game_model) {
  GameView* game_view = new GameView(game_model);
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
  game_model_->addTableCard(card->getCardModel());
  this->addChild(card);
}

void GameView::addPlayerHandCard(CardView *card) {
  player_hand_card_sprites_.pushBack(card);
  game_model_->pushPlayerHandCard(card->getCardModel());
  this->addChild(card);
}

void GameView::addBackupCard(CardView *card) {
  backup_card_sprites_.pushBack(card);
  game_model_->pushBackupCard(card->getCardModel());
  this->addChild(card);
}

void GameView::addUndoButton(UndoButtonView *undo_button) {
  this->addChild(undo_button);
}