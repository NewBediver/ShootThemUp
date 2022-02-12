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
    if (LevelImage != nullptr) {
        LevelImage->SetColorAndOpacity(is_selected ? FLinearColor::Red : FLinearColor::White);
    }
}

void USTULevelItemWidget::NativeOnInitialized() {
    Super::NativeOnInitialized();

    if (LevelSelectButton != nullptr) {
        LevelSelectButton->OnClicked.AddDynamic(this, &USTULevelItemWidget::OnLevelItemClicked);
        LevelSelectButton->OnHovered.AddDynamic(this, &USTULevelItemWidget::OnLevelItemHovered);
        LevelSelectButton->OnUnhovered.AddDynamic(this, &USTULevelItemWidget::OnLevelItemUnhovered);
    }
}

void USTULevelItemWidget::OnLevelItemClicked() {
    OnLevelSelected.Broadcast(LevelData);
}

void USTULevelItemWidget::OnLevelItemHovered() {
    if (FrameImage != nullptr) {
        FrameImage->SetVisibility(ESlateVisibility::Visible);
    }
}

void USTULevelItemWidget::OnLevelItemUnhovered() {
    if (FrameImage != nullptr) {
        FrameImage->SetVisibility(ESlateVisibility::Hidden);
    }
}