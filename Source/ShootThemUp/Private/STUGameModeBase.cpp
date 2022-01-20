// Shoot Them Up Game. All Right Reserved.

#include "STUGameModeBase.h"
#include "Player/STUBaseCharacter.h"
#include "Player/STUPlayerController.h"
#include "UI/STUGameHUD.h"
#include "AIController.h"
#include "Player/STUPlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUGameModeBase, All, All);

ASTUGameModeBase::ASTUGameModeBase() {
    DefaultPawnClass = ASTUBaseCharacter::StaticClass();
    PlayerControllerClass = ASTUPlayerController::StaticClass();
    HUDClass = ASTUGameHUD::StaticClass();
    PlayerStateClass = ASTUPlayerState::StaticClass();
}

void ASTUGameModeBase::StartPlay() {
    Super::StartPlay();

    SpawnBots();
    CreateTeamsInfo();

    CurrentRound = 1;
    StartRound();
}

UClass* ASTUGameModeBase::GetDefaultPawnClassForController_Implementation(
    AController* InController) {
    if (InController != nullptr &&
        InController->IsA<AAIController>()) {
        return AIPawnClass;
    }
    return Super::GetDefaultPawnClassForController_Implementation(InController);
}

void ASTUGameModeBase::Killed(AController* killer_controller, AController* victim_controller) {
    const auto killer_player_state = killer_controller != nullptr
                                         ? Cast<ASTUPlayerState>(killer_controller->PlayerState)
                                         : nullptr;
    const auto victim_player_state = victim_controller != nullptr
                                         ? Cast<ASTUPlayerState>(victim_controller->PlayerState)
                                         : nullptr;

    if (killer_player_state != nullptr) {
        killer_player_state->AddKill();
    }

    if (victim_player_state != nullptr) {
        victim_player_state->AddDeath();
    }
}

void ASTUGameModeBase::SpawnBots() {
    if (GetWorld() == nullptr) {
        return;
    }

    for (int32 i = 0; i < GameData.PlayersNum - 1; ++i) {
        FActorSpawnParameters spawn_info;
        spawn_info.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

        const auto stu_ai_controller = GetWorld()->SpawnActor<AAIController>(AIControllerClass, spawn_info);
        RestartPlayer(stu_ai_controller);
    }
}

void ASTUGameModeBase::StartRound() {
    RoundCountDown = GameData.RoundTime;
    GetWorldTimerManager().SetTimer(GameRoundTimerHandle, this, &ASTUGameModeBase::GameTimerUpdate,
                                    1.0f, true);
}

void ASTUGameModeBase::GameTimerUpdate() {
    UE_LOG(LogSTUGameModeBase, Display, TEXT("Time: %i / Round: %i/%i"), RoundCountDown,
           CurrentRound, GameData.RoundsNum);

    if (--RoundCountDown == 0) {
        GetWorldTimerManager().ClearTimer(GameRoundTimerHandle);

        if (CurrentRound + 1 <= GameData.RoundsNum) {
            ++CurrentRound;
            ResetPlayers();
            StartRound();
        } else {
            UE_LOG(LogSTUGameModeBase, Display, TEXT("======== GAME OVER ========"));
            LogPlayerInfo();
        }
    }
}

void ASTUGameModeBase::ResetPlayers() {
    if (GetWorld() == nullptr) {
        return;
    }

    for (auto it = GetWorld()->GetControllerIterator(); it; ++it) {
        ResetOnePlayer(it->Get());
    }
}

void ASTUGameModeBase::ResetOnePlayer(AController* controller) {
    if (controller != nullptr
            && controller->GetPawn() != nullptr) {
        controller->GetPawn()->Reset();
    }

    RestartPlayer(controller);
    SetPlayerColor(controller);
}

void ASTUGameModeBase::CreateTeamsInfo() {
    if (GetWorld() == nullptr) {
        return;
    }

    int32 team_id = 1;
    for (auto it = GetWorld()->GetControllerIterator(); it; ++it) {
        const auto controller = it->Get();
        if (controller == nullptr) {
            continue;
        }
        
        const auto player_state = Cast<ASTUPlayerState>(controller->PlayerState);
        if (player_state == nullptr) {
            continue;
        }

        player_state->SetTeamID(team_id);
        player_state->SetTeamColor(DetermineColorByTeamID(team_id));
        SetPlayerColor(controller);

        team_id = team_id == 1 ? 2 : 1;
    }
}

FLinearColor ASTUGameModeBase::DetermineColorByTeamID(int32 team_id) const {
    if (team_id - 1 < GameData.TeamColors.Num()) {
        return GameData.TeamColors[team_id - 1];
    }
    UE_LOG(LogSTUGameModeBase, Warning, TEXT("No color for team id: %i, set to default: %s"),
           team_id, *GameData.DefaultTeamColor.ToString());
    return GameData.DefaultTeamColor;
}

void ASTUGameModeBase::SetPlayerColor(AController* controller) {
    if (controller == nullptr) {
        return;
    }

    const auto character = Cast<ASTUBaseCharacter>(controller->GetPawn());
    if (character == nullptr) {
        return;
    }

    const auto player_state = Cast<ASTUPlayerState>(controller->PlayerState);
    if (player_state == nullptr) {
        return;
    }

    character->SetPlayerColor(player_state->GetTeamColor());
}

void ASTUGameModeBase::LogPlayerInfo() {
    if (GetWorld() == nullptr) {
        return;
    }

    for (auto it = GetWorld()->GetControllerIterator(); it; ++it) {
        const auto controller = it->Get();
        if (controller == nullptr) {
            continue;
        }

        const auto player_state = Cast<ASTUPlayerState>(controller->PlayerState);
        if (player_state == nullptr) {
            continue;
        }

        player_state->LogInfo();
    }
}