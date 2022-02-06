// Shoot Them Up Game. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUCoreTypes.h"
#include "STULevelItemWidget.generated.h"

class UButton;
class UTextBlock;
class UImage;

UCLASS()
class SHOOTTHEMUP_API USTULevelItemWidget : public UUserWidget {
    GENERATED_BODY()

  public:
    FOnLevelSelectedSignature OnLevelSelected;

    void SetLevelData(const FLevelData& data);
    FLevelData GetLevelData();

    void SetSelected(bool is_selected);

  protected:
    void NativeOnInitialized() override;

    UPROPERTY(meta = (BindWidget))
    UButton* LevelSelectButton = nullptr;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* LevelNameTextBlock = nullptr;

    UPROPERTY(meta = (BindWidget))
    UImage* LevelImage = nullptr;

    UPROPERTY(meta = (BindWidget))
    UImage* FrameImage = nullptr;

  private:
    UFUNCTION()
    void OnLevelItemClicked();

    FLevelData LevelData;
};
