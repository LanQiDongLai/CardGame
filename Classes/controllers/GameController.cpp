#include "controllers/GameController.h"

#include <iostream>

#include "services/CardMatcher.h"
#include "services/LevelConfigLoader.h"

GameController::GameController(GameView* game_view) : game_view_(game_view) {
  card_manager_ = CardManager::create();
  undo_manager_ = UndoManager::create();
}

GameController::~GameController() {}

GameController* GameController::create() {
  auto game_model = GameModel::create();
  auto game_view = GameView::create(game_model);
  return new GameController(game_view);
}

void GameController::startGame(int level) {
  auto level_config = LevelConfigLoader::loadLevelConfig(level);
  auto scene = Scene::create();
  scene->addChild(game_view_);
  initCards(level_config);
  auto undo_button_view = UndoButtonView::create();
  undo_button_view->setCallback([this]() { this->handleUndoButtonClick(); });
  scene->addChild(undo_button_view);
  auto director = Director::getInstance();
  director->runWithScene(scene);
}

void GameController::initCards(const LevelConfig& level_config) {
  for (auto card_config : level_config.getPlayfieldCards()) {
    auto card_model = CardModel::create(
        card_config->number + 1, card_config->suit_type, card_config->stage,
        card_config->position + Vec2(100, 800), false);
    auto card_view = CardView::create(card_model);
    card_view->setClickCallBack(
        [this](int card_id) { this->handleTableCardClick(card_id); });
    game_view_->addTableCard(card_view);
    card_manager_->addCardView(card_model->getId(), card_view);
  }
  int stack_card_count = level_config.getStackCards().size();
  int count = 0;
  for (auto card_config : level_config.getStackCards()) {
    count++;
    static Vec2 offset = Vec2(400 - (stack_card_count - 1) * 100, 600);
    offset += Vec2(100, 0);
    auto card_model = CardModel::create(
        card_config->number + 1, card_config->suit_type, card_config->stage,
        card_config->position + offset, false);
    auto card_view = CardView::create(card_model);
    card_view->setClickCallBack(
        [this](int card_id) { this->handleBackUpCardClick(card_id); });
    game_view_->addBackupCard(card_view);
    card_manager_->addCardView(card_model->getId(), card_view);
  }
}

void GameController::handleBackUpCardClick(int card_id) {
  auto card_view = card_manager_->getCardView(card_id);
  if (card_view->getCardModel()->getCardStage() == CardStage::CS_BACKUP) {
    undo_manager_->recordMoveAction(card_id, CardStage::CS_BACKUP,
                                    card_view->getCardModel()->getPosition(),
                                    CardStage::CS_SELECTED, Vec2(800, 600));
    card_view->playMoveAnimation(Vec2(800, 600));
  }
}

void GameController::handleTableCardClick(int card_id) {
  auto card_view = card_manager_->getCardView(card_id);
  auto card_model = card_view->getCardModel();
  auto card_in_hand = game_view_->getTopPlayerHandCard();
  game_view_->pushPlayerHandCard(card_view);
  printf("canMatch: %d\n",
         card_in_hand
             ? CardMatcher::canMatch(card_model->getNumber(),
                                      card_in_hand->getNumber())
             : -1);
  bool is_card_in_hand_match =
      !card_in_hand ||
      CardMatcher::canMatch(card_model->getNumber(), card_in_hand->getNumber());
  if (card_model->getCardStage() == CardStage::CS_UNSELECTED &&
      is_card_in_hand_match) {
    undo_manager_->recordMoveAction(card_id, CardStage::CS_UNSELECTED,
                                    card_model->getPosition(),
                                    CardStage::CS_SELECTED, Vec2(800, 600));
    card_view->playMoveAnimation(Vec2(800, 600));
  }
}

void GameController::handleUndoButtonClick() {
  auto move_record = undo_manager_->undo();
  if (move_record.valid) {
    auto card_view = card_manager_->getCardView(move_record.card_id);
    card_view->getCardModel()->setCardStage(move_record.from_stage);
    card_view->playMoveAnimation(move_record.from_position);
  }
}