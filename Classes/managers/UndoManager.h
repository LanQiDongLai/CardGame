#pragma once
#include "cocos2d.h"
#include "utils/CommonDef.h"

USING_NS_CC;

// 撤销管理器，负责记录玩家的操作历史，并提供撤销功能
class UndoManager {
 private:
  UndoManager();
 public:
  struct MoveRecord {
    bool valid;
    int card_id;
    CardStage from_stage;
    Vec2 from_position;
    CardStage to_stage;
    Vec2 to_position;
  };
  static UndoManager* create();
  ~UndoManager();
  void recordMoveAction(int card_id, CardStage from_stage, Vec2 from_position,
                        CardStage to_stage, Vec2 to_position);
  bool canUndo() const;
  MoveRecord undo();

 private:

  std::vector<MoveRecord> move_history_;
};