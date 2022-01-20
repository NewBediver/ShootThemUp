// Shoot Them Up Game. All Right Reserved.

#include "Player/STUPlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUPlayerState, All, All);

void ASTUPlayerState::SetTeamID(int32 id) {
    TeamID = id;
}

int32 ASTUPlayerState::GetTeamID() const {
    return TeamID;
}

void ASTUPlayerState::SetTeamColor(const FLinearColor& color) {
    TeamColor = color;
}

FLinearColor ASTUPlayerState::GetTeamColor() const {
    return TeamColor;
}

void ASTUPlayerState::AddKill() {
    ++KillsNum;
}

int32 ASTUPlayerState::GetKillNum() const {
    return KillsNum;
}

void ASTUPlayerState::AddDeath() {
    ++DeathsNum;
}

int32 ASTUPlayerState::GetDeathsNum() const {
    return DeathsNum;
}

void ASTUPlayerState::LogInfo() {
    UE_LOG(LogSTUPlayerState, Display, TEXT("TeamID: %i, Kills: %i, Death: %i"), TeamID, KillsNum,
           DeathsNum);
}