#pragma once
#include "cocos2d.h"
#include "utils/CommonDef.h"

USING_NS_CC;

// 撤销管理器，负责记录玩家的操作历史，并提供撤销功能
class UndoManager {
 private:
  UndoManager();
 public:
  // 移动记录结构体，包含一次移动操作的详细信息
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
  // 记录一次移动操作
  void recordMoveAction(int card_id, CardStage from_stage, Vec2 from_position,
                        CardStage to_stage, Vec2 to_position);
  // 检查是否有可撤销的操作
  bool canUndo() const;
  // 执行撤销操作，返回撤销的记录
  MoveRecord undo();

 private:

  std::vector<MoveRecord> move_history_;
};