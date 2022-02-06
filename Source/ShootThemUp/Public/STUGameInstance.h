// Shoot Them Up Game. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "STUCoreTypes.h"
#include "STUGameInstance.generated.h"

UCLASS()
class SHOOTTHEMUP_API USTUGameInstance : public UGameInstance {
    GENERATED_BODY()

  public:
    FLevelData GetStartupLevel() const;
    void SetStartupLevel(const FLevelData& data);

    TArray<FLevelData> GetLevelsData() const;
    FName GetMenuLevelName() const;

  protected:
    UPROPERTY(EditDefaultsOnly, Category = "Game", meta = (ToolTip = "Level names must be unique!"))
    TArray<FLevelData> LevelsData;

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    FName MenuLevelName = NAME_None;

  private:
    FLevelData StartupLevel;
};
