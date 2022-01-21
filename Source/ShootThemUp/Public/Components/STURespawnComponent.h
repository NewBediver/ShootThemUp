// Shoot Them Up Game. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STURespawnComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTTHEMUP_API USTURespawnComponent : public UActorComponent {
    GENERATED_BODY()

  public:
    USTURespawnComponent();
    void Respawn(int32 respawn_time);

    int32 GetRespawnCountDown() const;
    bool IsRespawnInProgress() const;

  private:
    void RespawnTimerUpdate();

    FTimerHandle RespawnTimerHandle;
    int32 RespawnCountDown = 0;
};
