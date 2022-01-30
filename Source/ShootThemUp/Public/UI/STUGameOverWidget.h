// Shoot Them Up Game. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUCoreTypes.h"
#include "STUGameOverWidget.generated.h"

class UVerticalBox;

UCLASS()
class SHOOTTHEMUP_API USTUGameOverWidget : public UUserWidget {
    GENERATED_BODY()

  public:
    bool Initialize() override;

  protected:
    UPROPERTY(meta = (BindWidget))
    UVerticalBox* PlayerStatBox = nullptr;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PlayerStatRowWidgetClass;

  private:
    void OnMatchStateChanged(ESTUMatchState state);
    void UpdatePlayersStat();
};
