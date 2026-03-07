#include "services/CardMatcher.h"

bool CardMatcher::canMatch(int number_1, int number_2) {
  if (std::abs(number_1 - number_2) == 1 || (number_1 == 1 && number_2 == 13) ||
      (number_1 == 13 && number_2 == 1)) {
    return true;
  }
  return false;
}