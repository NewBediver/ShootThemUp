// Shoot Them Up Game. All Right Reserved.

#include "STUGameModeBase.h"
#include "Player/STUBaseCharacter.h"
#include "Player/STUPlayerController.h"
#include "UI/STUGameHUD.h"
#include "AIController.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUGameModeBase, All, All);

ASTUGameModeBase::ASTUGameModeBase() {
    DefaultPawnClass = ASTUBaseCharacter::StaticClass();
    PlayerControllerClass = ASTUPlayerController::StaticClass();
    HUDClass = ASTUGameHUD::StaticClass();
}

void ASTUGameModeBase::StartPlay() {
    Super::StartPlay();

    SpawnBots();

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
            StartRound();
        } else {
            UE_LOG(LogSTUGameModeBase, Display, TEXT("======== GAME OVER ========"));
        }
    }
}