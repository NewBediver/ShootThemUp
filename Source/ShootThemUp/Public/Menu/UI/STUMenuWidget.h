// Shoot Them Up Game. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUMenuWidget.generated.h"

class UButton;

UCLASS()
class SHOOTTHEMUP_API USTUMenuWidget : public UUserWidget {
    GENERATED_BODY()

  protected:
    void NativeOnInitialized() override;

    UPROPERTY(meta = (Bindwidget))
    UButton* StartGameButton = nullptr;

  private:
    UFUNCTION()
    void OnStartGame();
};
