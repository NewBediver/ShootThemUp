// Shoot Them Up Game. All Right Reserved.

#include "UI/STUPlayerStatRowWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void USTUPlayerStatRowWidget::SetPlayerName(const FText& text) {
    if (PlayerNameTextBlock == nullptr) {
        return;
    }

    PlayerNameTextBlock->SetText(text);
}

void USTUPlayerStatRowWidget::SetKills(const FText& text) {
    if (KillsTextBlock == nullptr) {
        return;
    }

    KillsTextBlock->SetText(text);
}

void USTUPlayerStatRowWidget::SetDeaths(const FText& text) {
    if (DeathsTextBlock == nullptr) {
        return;
    }

    DeathsTextBlock->SetText(text);
}

void USTUPlayerStatRowWidget::SetTeam(const FText& text) {
    if (TeamTextBlock == nullptr) {
        return;
    }

    TeamTextBlock->SetText(text);
}

void USTUPlayerStatRowWidget::SetPlayerIndicatorVisibility(bool visible) {
    if (PlayerIndicatorWidget == nullptr) {
        return;
    }

    PlayerIndicatorWidget->SetVisibility(visible ? ESlateVisibility::Visible
                                                 : ESlateVisibility::Hidden);
}