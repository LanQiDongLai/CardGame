#pragma once

#include "cocos2d.h"
#include "configs/LevelConfig.h"
#include "json/document.h"

USING_NS_CC;

// 关卡配置加载器，负责从JSON文件中加载关卡配置数据
class LevelConfigLoader {
public:
  static LevelConfig loadLevelConfig(int level);
};