// Shoot Them Up Game. All Right Reserved.

#include "UI/STUGoToMenuWidget.h"
#include "Components/Button.h"
#include "STUGameInstance.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUGoToMenuWidget, All, All);

void USTUGoToMenuWidget::NativeOnInitialized() {
    Super::NativeOnInitialized();

    if (GoToMenuButton != nullptr) {
        GoToMenuButton->OnClicked.AddDynamic(this, &USTUGoToMenuWidget::OnGoToMenu);
    }
}

void USTUGoToMenuWidget::OnGoToMenu() {
    if (GetWorld() == nullptr) {
        return;
    }

    const auto stu_game_instance = GetWorld()->GetGameInstance<USTUGameInstance>();
    if (stu_game_instance == nullptr) {
        return;
    }

    if (stu_game_instance->GetStartupLevel().LevelName.IsNone()) {
        UE_LOG(LogSTUGoToMenuWidget, Error, TEXT("Menu level name is none."));
        return;
    }

    UGameplayStatics::OpenLevel(this, stu_game_instance->GetMenuLevelName());
}