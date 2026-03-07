#include "services/LevelConfigLoader.h"

LevelConfig LevelConfigLoader::loadLevelConfig(int level) {
  std::string file_path = "res/levels/level_" + std::to_string(level) + ".json";
  std::string file_content = FileUtils::getInstance()->getStringFromFile(file_path);
  rapidjson::Document document;
  document.Parse(file_content.c_str());
  LevelConfig level_config;
  level_config.setLevel(level);
  if(file_content.empty() || document.HasParseError()) {
    CCLOG("Failed to load level config file: %s", file_path.c_str());
    return level_config;
  }
  if (document.HasMember("Playfield") && document["Playfield"].IsArray()) {
    const rapidjson::Value& playfield = document["Playfield"];
    for (rapidjson::Value::ConstValueIterator it = playfield.Begin(); it != playfield.End(); ++it) {
      CardConfig *card_config = new CardConfig();
      card_config->number = ((*it)["CardFace"].GetInt());
      card_config->suit_type = (static_cast<CardSuitType>((*it)["CardSuit"].GetInt()));
      card_config->stage = CardStage::CS_TABLE;
      card_config->position = (Vec2((*it)["Position"]["x"].GetInt(), (*it)["Position"]["y"].GetInt()));
      level_config.addPlayfieldCards(card_config);
    }
  }
  if (document.HasMember("Stack") && document["Stack"].IsArray()) {
    const rapidjson::Value& stock = document["Stack"];
    for (rapidjson::Value::ConstValueIterator it = stock.Begin(); it != stock.End(); ++it) {
      CardConfig *card_config = new CardConfig();
      card_config->number = ((*it)["CardFace"].GetInt());
      card_config->suit_type = (static_cast<CardSuitType>((*it)["CardSuit"].GetInt()));
      card_config->stage = CardStage::CS_BACKUP;
      card_config->position = Vec2(0, 0);
      level_config.addStackCards(card_config);
    }
  }
  return level_config;
}