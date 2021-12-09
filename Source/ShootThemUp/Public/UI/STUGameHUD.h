// Shoot Them Up Game. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "STUGameHUD.generated.h"

/**
 *
 */
UCLASS()
class SHOOTTHEMUP_API ASTUGameHUD : public AHUD {
    GENERATED_BODY()

  public:
    void DrawHUD() override;

  private:
    void DrawCrossHair();
};