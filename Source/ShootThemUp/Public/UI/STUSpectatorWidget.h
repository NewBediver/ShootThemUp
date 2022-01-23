// Shoot Them Up Game. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUSpectatorWidget.generated.h"

UCLASS()
class SHOOTTHEMUP_API USTUSpectatorWidget : public UUserWidget {
    GENERATED_BODY()

  public:
    UFUNCTION(BlueprintCallable, Category = "UI")
    bool GetRespawnTime(int32& count_down_time) const;
};