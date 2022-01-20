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

    void Killed(AController* killer_controller, AController* victim_controller);

    FGameData GetGameData() const;
    int32 GetCurrentRountNum() const;
    int32 GetRoundSecondsRemaining() const;

  protected:
    UPROPERTY(EditDefaultsOnly, Category = "Game")
    TSubclassOf<AAIController> AIControllerClass;

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    TSubclassOf<APawn> AIPawnClass;

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    FGameData GameData;

  private:
    void SpawnBots();
    void StartRound();
    void GameTimerUpdate();

    void ResetPlayers();
    void ResetOnePlayer(AController* controller);

    void CreateTeamsInfo();
    FLinearColor DetermineColorByTeamID(int32 team_id) const;
    void SetPlayerColor(AController* controller);

    void LogPlayerInfo();

    int32 CurrentRound = 1;
    int32 RoundCountDown = 0;
    FTimerHandle GameRoundTimerHandle;
};
