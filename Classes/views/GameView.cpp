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

void GameView::pushPlayerHandCard(CardView *card) {
  player_hand_card_sprites_.pushBack(card);
  game_model_->pushPlayerHandCard(card->getCardModel());
  switch (card->getCardModel()->getCardStage()) {
  case CardStage::CS_UNSELECTED:
    game_model_->removeTableCard(card->getCardModel()->getId());
    break;
  case CardStage::CS_BACKUP:
    game_model_->popBackupCard();
    break;
  default:
    break;
  }
}

void GameView::popPlayerHandCard(CardView *card, CardStage new_stage) {
  player_hand_card_sprites_.eraseObject(card);
  auto top_card = game_model_->popPlayerHandCard();
  card->getCardModel()->setCardStage(new_stage);
  switch (new_stage) {
  case CardStage::CS_UNSELECTED:
    game_model_->addTableCard(card->getCardModel());
    break;
  case CardStage::CS_BACKUP:
    game_model_->pushBackupCard(card->getCardModel());
    break;
  default:
    break;
  }
}

void GameView::addBackupCard(CardView *card) {
  backup_card_sprites_.pushBack(card);
  game_model_->pushBackupCard(card->getCardModel());
  this->addChild(card);
}

void GameView::addUndoButton(UndoButtonView *undo_button) {
  this->addChild(undo_button);
}

CardModel* GameView::getTableCardById(int card_id) {
  for (auto card_view : table_card_sprites_) {
    if (card_view->getCardModel()->getId() == card_id) {
      return card_view->getCardModel();
    }
  }
  return nullptr;
}

CardModel* GameView::getTopPlayerHandCard() {
  if (game_model_->isPlayerHandEmpty()) {
    return nullptr;
  }
  return game_model_->getTopPlayerHandCard();
}

CardModel* GameView::getTopBackupCard() {
  if (game_model_->isBackupEmpty()) {
    return nullptr;
  }
  return game_model_->getTopBackupCard();
}