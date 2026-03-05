#pragma once

#include "cocos2d.h"
#include "configs/LevelConfig.h"
#include "json/document.h"

USING_NS_CC;

class LevelConfigLoader {
public:
  static LevelConfig loadLevelConfig(int level);
};