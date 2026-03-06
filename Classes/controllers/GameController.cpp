#include "controllers/GameController.h"

#include <iostream>

#include "services/LevelConfigLoader.h"

GameController::GameController(GameView* game_view) : game_view_(game_view) {
  card_manager_ = CardManager::getInstance();
}

GameController::~GameController() {}

GameController* GameController::create() {
  auto game_view = GameView::create();
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
    game_view_->addChild(card_view);
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
    game_view_->addChild(card_view, count);
    card_manager_->addCardView(card_model->getId(), card_view);
  }
}

void GameController::handleCardClick(int card_id) {
  auto card_model = card_manager_->getCardView(card_id)->getCardModel();
  card_model->setNumber(6);
  CardView* card_view = card_manager_->getCardView(card_id);
  if (card_view) {
    card_view->updateView();
  }
}

void GameController::handleUndoButtonClick() {
  std::cout << "Undo button clicked" << std::endl;
}