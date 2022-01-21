// Shoot Them Up Game. All Right Reserved.

#include "Components/STURespawnComponent.h"
#include "STUGameModeBase.h"

USTURespawnComponent::USTURespawnComponent() {
    PrimaryComponentTick.bCanEverTick = false;
}

void USTURespawnComponent::Respawn(int32 respawn_time) {
    if (GetWorld() == nullptr) {
        return;
    }

    RespawnCountDown = respawn_time;
    GetWorld()->GetTimerManager().SetTimer(
        RespawnTimerHandle, this, &USTURespawnComponent::RespawnTimerUpdate, 1.0f, true);
}

void USTURespawnComponent::RespawnTimerUpdate() {
    if (--RespawnCountDown == 0) {
        if (GetWorld() == nullptr) {
            return;
        }
        GetWorld()->GetTimerManager().ClearTimer(RespawnTimerHandle);

        const auto game_mode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());
        if (game_mode == nullptr) {
            return;
        }

        game_mode->RespawnRequest(Cast<AController>(GetOwner()));
    }
}