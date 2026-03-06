#include "controllers/GameController.h"

#include <iostream>

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
        [this](int card_id) { this->handleCardClick(card_id); });
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
        [this](int card_id) { this->handleCardClick(card_id); });
    game_view_->addBackupCard(card_view);
    card_manager_->addCardView(card_model->getId(), card_view);
  }
}

void GameController::handleCardClick(int card_id) {
  auto card_view = card_manager_->getCardView(card_id);
  undo_manager_->recordMoveAction(card_id, CardStage::CS_SELECTED, card_view->getCardModel()->getPosition(),
                                  CardStage::CS_SELECTED, Vec2(800, 600));
  card_view->playMoveAnimation(Vec2(800, 600));
}

void GameController::handleUndoButtonClick() {
  auto move_record = undo_manager_->undo();
  if (move_record.valid) {
    printf("Undoing move: card_id=%d, from_stage=%d, from_position=(%.1f, %.1f), to_stage=%d, to_position=(%.1f, %.1f)\n",
           move_record.card_id, move_record.from_stage, move_record.from_position.x,
           move_record.from_position.y, move_record.to_stage, move_record.to_position.x,
           move_record.to_position.y);
    auto card_view = card_manager_->getCardView(move_record.card_id);
    card_view->playMoveAnimation(move_record.from_position);
  }
}