// Shoot Them Up Game. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/STUBaseWidget.h"
#include "STUCoreTypes.h"
#include "STUMenuWidget.generated.h"

class UButton;
class UHorizontalBox;
class USTUGameInstance;
class USTULevelItemWidget;

UCLASS()
class SHOOTTHEMUP_API USTUMenuWidget : public USTUBaseWidget {
    GENERATED_BODY()

  protected:
    void NativeOnInitialized() override;
    void OnAnimationFinished_Implementation(const UWidgetAnimation* animation);

    UPROPERTY(meta = (Bindwidget))
    UButton* StartGameButton = nullptr;

    UPROPERTY(meta = (Bindwidget))
    UButton* QuitGameButton = nullptr;

    UPROPERTY(meta = (Bindwidget))
    UHorizontalBox* LevelItemsBox = nullptr;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> LevelItemWidgetClass;

    UPROPERTY(meta = (BindWidgetAnim), Transient)
    UWidgetAnimation* HideAnimation = nullptr;

  private:
    UFUNCTION()
    void OnStartGame();

    UFUNCTION()
    void OnQuitGame();

    void InitLevelItems();
    void OnLevelSelected(const FLevelData& data);
    USTUGameInstance* GetSTUGameInstance() const;

    UPROPERTY()
    TArray<USTULevelItemWidget*> LevelItemWidgets;
};
