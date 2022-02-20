// Shoot Them Up Game. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "STUCoreTypes.h"
#include "STUPlayerController.generated.h"

class USTURespawnComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUPlayerController : public APlayerController {
    GENERATED_BODY()

  public:
    ASTUPlayerController();

  protected:
    void BeginPlay() override;
    void SetupInputComponent() override; 

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USTURespawnComponent* RespawnComponent = nullptr; 

  private:
    void OnPauseGame();
    void OnMatchStateChanged(ESTUMatchState state);
    void OnMuteSound();
};
