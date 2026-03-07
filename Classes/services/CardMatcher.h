#pragma once
#include <cmath>

// 卡牌匹配器，负责判断两张牌是否可以匹配
class CardMatcher {
 public:
  static bool canMatch(int number_1, int number_2);
};