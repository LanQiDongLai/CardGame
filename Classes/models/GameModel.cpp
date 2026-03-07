#include "models/GameModel.h"

GameModel::GameModel() {
}

GameModel *GameModel::create() {
  GameModel* game_model = new GameModel();
  return game_model;
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

CardModel* GameModel::popPlayerHandCard() {
  if(!player_hand_cards_.empty()) {
    auto top_card = player_hand_cards_.top();
    player_hand_cards_.pop();
    return top_card;
  }
  return nullptr;
}

bool GameModel::isPlayerHandEmpty() const {
  return player_hand_cards_.empty();
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

CardModel* GameModel::getTopPlayerHandCard() {
  if (!player_hand_cards_.empty()) {
    return player_hand_cards_.top();
  }
  return nullptr;
}