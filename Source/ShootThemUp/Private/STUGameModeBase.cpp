// Shoot Them Up Game. All Right Reserved.

#include "STUGameModeBase.h"
#include "Player/STUBaseCharacter.h"
#include "Player/STUPlayerController.h"
#include "UI/STUGameHUD.h"
#include "AIController.h"

ASTUGameModeBase::ASTUGameModeBase() {
    DefaultPawnClass = ASTUBaseCharacter::StaticClass();
    PlayerControllerClass = ASTUPlayerController::StaticClass();
    HUDClass = ASTUGameHUD::StaticClass();
}

void ASTUGameModeBase::StartPlay() {
    Super::StartPlay();

    SpawnBots();
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