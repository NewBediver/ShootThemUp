// Shoot Them Up Game. All Right Reserved.

#include "UI/STUPauseWidget.h"
#include "GameFramework/GameModeBase.h"
#include "Components/Button.h"

void USTUPauseWidget::NativeOnInitialized() {
    Super::NativeOnInitialized();

    if (ClearPauseButton != nullptr) {
        ClearPauseButton->OnClicked.AddDynamic(this, &USTUPauseWidget::OnClearPause);
    }
}

void USTUPauseWidget::OnClearPause() {
    if (GetWorld() == nullptr
        || GetWorld()->GetAuthGameMode() == nullptr) {
        return;
    }

    GetWorld()->GetAuthGameMode()->ClearPause();
}