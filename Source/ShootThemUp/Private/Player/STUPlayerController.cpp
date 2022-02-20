// Shoot Them Up Game. All Right Reserved.

#include "Player/STUPlayerController.h"
#include "Components/STURespawnComponent.h"
#include "STUGameModeBase.h"
#include "STUGameInstance.h"

ASTUPlayerController::ASTUPlayerController() {
    RespawnComponent = CreateDefaultSubobject<USTURespawnComponent>("STURespawnComponent");
}

void ASTUPlayerController::BeginPlay() {
    Super::BeginPlay();

    if (GetWorld() != nullptr) {
        const auto game_mode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());
        if (game_mode != nullptr) {
            game_mode->OnMatchStateChanged.AddUObject(this,
                                                      &ASTUPlayerController::OnMatchStateChanged);
        }
    }
}

void ASTUPlayerController::SetupInputComponent() {
    Super::SetupInputComponent();

    if (InputComponent == nullptr) {
        return;
    }

    InputComponent->BindAction("PauseGame", IE_Pressed, this, &ASTUPlayerController::OnPauseGame);
    InputComponent->BindAction("Mute", IE_Pressed, this, &ASTUPlayerController::OnMuteSound);
}

void ASTUPlayerController::OnPauseGame() {
    if (GetWorld() == nullptr
        || GetWorld()->GetAuthGameMode() == nullptr) {
        return;
    }

    GetWorld()->GetAuthGameMode()->SetPause(this);
}

void ASTUPlayerController::OnMatchStateChanged(ESTUMatchState state) {
    if (state == ESTUMatchState::InProgress) {
        SetInputMode(FInputModeGameOnly());
        bShowMouseCursor = false;
    } else {
        SetInputMode(FInputModeUIOnly());
        bShowMouseCursor = true;
    }
}

void ASTUPlayerController::OnMuteSound() {
    if (GetWorld() == nullptr) {
        return;
    }

    const auto stu_game_instance = GetWorld()->GetGameInstance<USTUGameInstance>();
    if (stu_game_instance == nullptr) {
        return;
    }

    stu_game_instance->ToggleVolume();
}