// Shoot Them Up Game. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUPlayerStatRowWidget.generated.h"

class UImage;
class UTextBlock;

UCLASS()
class SHOOTTHEMUP_API USTUPlayerStatRowWidget : public UUserWidget {
    GENERATED_BODY()

  public:
    void SetPlayerName(const FText& text);
    void SetKills(const FText& text);
    void SetDeaths(const FText& text);
    void SetTeam(const FText& text);
    void SetPlayerIndicatorVisibility(bool visible);
    void SetTeamColor(const FLinearColor& color);

  protected:
    UPROPERTY(meta = (BindWidget))
    UTextBlock* PlayerNameTextBlock = nullptr;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* KillsTextBlock = nullptr;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* DeathsTextBlock = nullptr;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* TeamTextBlock = nullptr;

    UPROPERTY(meta = (BindWidget))
    UImage* PlayerIndicatorWidget = nullptr;

    UPROPERTY(meta = (BindWidget))
    UImage* TeamImage = nullptr;
};
