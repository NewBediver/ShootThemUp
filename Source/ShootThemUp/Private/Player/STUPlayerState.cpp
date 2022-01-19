// Shoot Them Up Game. All Right Reserved.

#include "Player/STUPlayerState.h"

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