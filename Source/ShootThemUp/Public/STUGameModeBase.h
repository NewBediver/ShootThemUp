// Shoot Them Up Game. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "STUCoreTypes.h"
#include "STUGameModeBase.generated.h"

class AAIController;

UCLASS()
class SHOOTTHEMUP_API ASTUGameModeBase : public AGameModeBase {
    GENERATED_BODY()

  public:
    explicit ASTUGameModeBase();

    void StartPlay() override;
    UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

  protected:
    UPROPERTY(EditDefaultsOnly, Category = "Game")
    TSubclassOf<AAIController> AIControllerClass;

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    TSubclassOf<APawn> AIPawnClass;

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    FGameData GameData;

  private:
    void SpawnBots();
};
