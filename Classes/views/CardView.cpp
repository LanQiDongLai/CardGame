#include "Views/CardView.h"

USING_NS_CC;

CardView::CardView(CardModel& card) : card_(card) { updateView(card); }

void CardView::initTouchListener() {
  touch_listener_ = EventListenerTouchOneByOne::create();
  touch_listener_->setSwallowTouches(true);
  touch_listener_->onTouchBegan = CC_CALLBACK_2(CardView::onTouchBegan, this);
  touch_listener_->onTouchEnded = CC_CALLBACK_2(CardView::onTouchEnded, this);
  _eventDispatcher->addEventListenerWithSceneGraphPriority(touch_listener_,
                                                           this);
}

CardView::~CardView() {}

CardView* CardView::create(CardModel& card) {
  CardView* card_view = new CardView(card);
  if (!card_view) {
    CC_SAFE_DELETE(card_view);
    return nullptr;
  }
  card_view->autorelease();
  card_view->initTouchListener();
  return card_view;
}

void CardView::updateView(CardModel& card) {
  this->setContentSize(Size(200, 300));
  this->removeAllChildrenWithCleanup(true);
  this->setPosition(card.getPosition());
  if (card.isFaceDown()) {
    auto card_back = LayerColor::create(Color4B::GRAY, 200, 300);
    this->addChild(card_back, 0);
    return;
  }
  auto card_general = Sprite::create("res/card_general.png");
  this->addChild(card_general, 0);
  bool is_black;
  Sprite* suit_sprite;
  suit_sprite = Sprite::create(getSuitResourcePath(card));
  suit_sprite->setPosition(Vec2(50, 100));
  this->addChild(suit_sprite, 1);
  Sprite* big_number_sprite;
  big_number_sprite = Sprite::create(getNumberResourcePath(card, true));
  big_number_sprite->setPosition(Vec2(0, -20));
  this->addChild(big_number_sprite, 2);
  Sprite* small_number_sprite;
  small_number_sprite = Sprite::create(getNumberResourcePath(card, false));
  small_number_sprite->setPosition(Vec2(-50, 100));
  this->addChild(small_number_sprite, 2);
}

std::string CardView::getCardGeneralResourcePath(CardModel& card) {
  return "res/card_general.png";
}

std::string CardView::getSuitResourcePath(CardModel& card) {
  switch (card.getCardSuitType()) {
    case CardSuitType::CST_HEARTS:
      return "res/suits/heart.png";
    case CardSuitType::CST_DIAMONDS:
      return "res/suits/diamond.png";
    case CardSuitType::CST_CLUBS:
      return "res/suits/club.png";
    case CardSuitType::CST_SPADES:
      return "res/suits/spade.png";
    default:
      return "";
  }
}

std::string CardView::getNumberResourcePath(CardModel& card, bool is_big) {
  bool is_black = (card.getCardSuitType() == CardSuitType::CST_CLUBS ||
                   card.getCardSuitType() == CardSuitType::CST_SPADES);
  switch (card.getCardFaceType()) {
    case CardFaceType::CFT_ACE:
      return "res/number/" +
             (is_big ? std::string("big") : std::string("small")) + "_" +
             (is_black ? std::string("black") : std::string("red")) + "_A.png";
    case CardFaceType::CFT_JACK:
      return "res/number/" +
             (is_big ? std::string("big") : std::string("small")) + "_" +
             (is_black ? std::string("black") : std::string("red")) + "_J.png";
    case CardFaceType::CFT_QUEEN:
      return "res/number/" +
             (is_big ? std::string("big") : std::string("small")) + "_" +
             (is_black ? std::string("black") : std::string("red")) + "_Q.png";
    case CardFaceType::CFT_KING:
      return "res/number/" +
             (is_big ? std::string("big") : std::string("small")) + "_" +
             (is_black ? std::string("black") : std::string("red")) + "_K.png";
    default:
      return "res/number/" +
             (is_big ? std::string("big") : std::string("small")) + "_" +
             (is_black ? std::string("black") : std::string("red")) + "_" +
             std::to_string(card.getNumber()) + ".png";
      break;
  }
}

void CardView::playFlipAnimation(CardModel& card) {
  card.setFaceDirection(!card.isFaceDown());
  auto flip = FlipX3D::create(0.5f);
  auto update_func = CallFunc::create([this, &card]() { updateView(card); });
  auto sequence = Sequence::create(flip, update_func, nullptr);
  this->runAction(sequence);
}

void CardView::playMoveAnimation(Vec2 new_position) {
  auto move = MoveTo::create(0.5f, new_position);
  this->runAction(move);
}

void CardView::setClickCallBack(std::function<void()> callback) {
  click_callback_ = callback;
}

bool CardView::onTouchBegan(Touch* touch, Event* event) {
  Vec2 locationInNode = this->convertToNodeSpace(touch->getLocation());
  Size size = this->getContentSize();
  Rect rect = Rect(0, 0, size.width, size.height);
  if (rect.containsPoint(locationInNode)) {
    if (click_callback_) {
      click_callback_();
    }
    return true;
  }
  return false;
}

void CardView::onTouchEnded(Touch* touch, Event* event) {
}