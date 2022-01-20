// Shoot Them Up Game. All Right Reserved.

#include "UI/STUGameDataWidget.h"
#include "STUGameModeBase.h"
#include "Player/STUPlayerState.h"

int32 USTUGameDataWidget::GetKillsNum() const {
  const auto player_state = GetSTUPlayerState();
  return player_state != nullptr ? player_state->GetKillNum() : 0;
}

int32 USTUGameDataWidget::GetCurrentRoundNum() const {
  const auto game_mode = GetSTUGameMode();
  return game_mode != nullptr ? game_mode->GetCurrentRountNum() : 0;
}

int32 USTUGameDataWidget::GetTotalRoundsNum() const {
  const auto game_mode = GetSTUGameMode();
  return game_mode != nullptr ? game_mode->GetGameData().RoundsNum : 0;
}

int32 USTUGameDataWidget::GetRoundSecondsRemaining() const {
  const auto game_mode = GetSTUGameMode();
  return game_mode != nullptr ? game_mode->GetRoundSecondsRemaining() : 0;
}

ASTUGameModeBase* USTUGameDataWidget::GetSTUGameMode() const {
    return GetWorld() != nullptr ? Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode()) : nullptr;
}

ASTUPlayerState* USTUGameDataWidget::GetSTUPlayerState() const {
    return GetOwningPlayer() != nullptr ? Cast<ASTUPlayerState>(GetOwningPlayer()->PlayerState) : nullptr;
}