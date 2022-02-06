// Shoot Them Up Game. All Right Reserved.

#include "Menu/UI/STULevelItemWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void USTULevelItemWidget::SetLevelData(const FLevelData& data) {
    LevelData = data;

    if (LevelNameTextBlock != nullptr) {
        LevelNameTextBlock->SetText(FText::FromName(LevelData.LevelDisplayName));
    }

    if (LevelImage != nullptr) {
        LevelImage->SetBrushFromTexture(LevelData.LevelThumb);
    }
}

FLevelData USTULevelItemWidget::GetLevelData() {
    return LevelData;
}

void USTULevelItemWidget::SetSelected(bool is_selected) {
    if (FrameImage != nullptr) {
        FrameImage->SetVisibility(is_selected ? ESlateVisibility::Visible
                                              : ESlateVisibility::Hidden);
    }
}

void USTULevelItemWidget::NativeOnInitialized() {
    Super::NativeOnInitialized();

    if (LevelSelectButton != nullptr) {
        LevelSelectButton->OnClicked.AddDynamic(this, &USTULevelItemWidget::OnLevelItemClicked);
    }
}

void USTULevelItemWidget::OnLevelItemClicked() {
    OnLevelSelected.Broadcast(LevelData);
}