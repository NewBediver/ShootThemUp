// Shoot Them Up Game. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "STUPlayerState.generated.h"

UCLASS()
class SHOOTTHEMUP_API ASTUPlayerState : public APlayerState {
    GENERATED_BODY()

  public:
    void SetTeamID(int32 id);
    int32 GetTeamID() const;

    void SetTeamColor(const FLinearColor& color);
    FLinearColor GetTeamColor() const;

  private:
    int32 TeamID;
    FLinearColor TeamColor;
};
