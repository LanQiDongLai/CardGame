#include "models/GameModel.h"

GameModel::GameModel() {
}

GameModel *GameModel::create() {
  GameModel* game_model = new GameModel();
  if (game_model) {
    game_model->autorelease();
    return game_model;
  }
  CC_SAFE_DELETE(game_model);
  return nullptr;
}

GameModel::~GameModel() {
}

void GameModel::addTableCard(CardModel *card) {
  table_cards_.push_back(card);
}

void GameModel::removeTableCard(int card_id) {
  for (auto it = table_cards_.begin(); it != table_cards_.end(); ++it) {
    if ((*it)->getId() == card_id) {
      table_cards_.erase(it);
      break;
    }
  }
}

void GameModel::pushPlayerHandCard(CardModel *card) {
  player_hand_cards_.push(card);
}

void GameModel::popPlayerHandCard(int card_id) {
  Stack<CardModel*> temp_stack;
  while (!player_hand_cards_.empty()) {
    CardModel* top_card = player_hand_cards_.top();
    player_hand_cards_.pop();
    if (top_card->getId() == card_id) {
      break;
    }
    temp_stack.push(top_card);
  }
  while (!temp_stack.empty()) {
    player_hand_cards_.push(temp_stack.top());
    temp_stack.pop();
  }
}

void GameModel::pushBackupCard(CardModel *card) {
  backup_cards_.push(card);
}

void GameModel::popBackupCard() {
  if (!backup_cards_.empty()) {
    backup_cards_.pop();
  }
}

bool GameModel::isBackupEmpty() const {
  return backup_cards_.empty();
}

CardModel* GameModel::getTopBackupCard() {
  if (!backup_cards_.empty()) {
    return backup_cards_.top();
  }
  return nullptr;
}