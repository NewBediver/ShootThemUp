// Shoot Them Up Game. All Right Reserved.

#include "UI/STUPauseWidget.h"
#include "GameFramework/GameModeBase.h"
#include "Components/Button.h"

bool USTUPauseWidget::Initialize() {
    const auto init_status = Super::Initialize();

    if (ClearPauseButton != nullptr) {
        ClearPauseButton->OnClicked.AddDynamic(this, &USTUPauseWidget::OnClearPause);
    }

    return init_status;
}

void USTUPauseWidget::OnClearPause() {
    if (GetWorld() == nullptr
        || GetWorld()->GetAuthGameMode() == nullptr) {
        return;
    }

    GetWorld()->GetAuthGameMode()->ClearPause();
}