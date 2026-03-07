#include "managers/UndoManager.h"

UndoManager::UndoManager() {}

UndoManager::~UndoManager() {}

UndoManager* UndoManager::create() {
  return new UndoManager();
}

void UndoManager::recordMoveAction(int card_id, CardStage from_stage, Vec2 from_position,
                        CardStage to_stage, Vec2 to_position) {
  move_history_.push_back({true, card_id, from_stage, from_position, to_stage, to_position});
}

bool UndoManager::canUndo() const {
  return !move_history_.empty();
}

UndoManager::MoveRecord UndoManager::undo() {
  if (canUndo()) {
    UndoManager::MoveRecord last_move = move_history_.back();
    move_history_.pop_back();
    return last_move;
  }
  return UndoManager::MoveRecord{false, 0, CardStage::CS_TABLE, Vec2::ZERO, CardStage::CS_TABLE, Vec2::ZERO};
}