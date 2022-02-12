// Shoot Them Up Game. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/STUBaseWidget.h"
#include "STUCoreTypes.h"
#include "STUGameOverWidget.generated.h"

class UVerticalBox;
class UButton;

UCLASS()
class SHOOTTHEMUP_API USTUGameOverWidget : public USTUBaseWidget {
    GENERATED_BODY()

  protected:
    void NativeOnInitialized() override;

    UPROPERTY(meta = (BindWidget))
    UVerticalBox* PlayerStatBox = nullptr;

    UPROPERTY(meta = (BindWidget))
    UButton* ResetLevelButton = nullptr;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PlayerStatRowWidgetClass;

  private:
    void OnMatchStateChanged(ESTUMatchState state);
    void UpdatePlayersStat();

    UFUNCTION()
    void OnResetLevel();
};
