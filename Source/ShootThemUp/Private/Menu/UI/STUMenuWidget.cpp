// Shoot Them Up Game. All Right Reserved.

#include "Menu/UI/STUMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "STUGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUMenuWidget, All, All);

void USTUMenuWidget::NativeOnInitialized() {
    Super::NativeOnInitialized();

    if (StartGameButton != nullptr) {
        StartGameButton->OnClicked.AddDynamic(this, &USTUMenuWidget::OnStartGame);
    }

    if (QuitGameButton != nullptr) {
        QuitGameButton->OnClicked.AddDynamic(this, &USTUMenuWidget::OnQuitGame);
    }
}

void USTUMenuWidget::OnStartGame() {
    if (GetWorld() == nullptr) {
        return;
    }

    const auto stu_game_instance = GetWorld()->GetGameInstance<USTUGameInstance>();
    if (stu_game_instance == nullptr) {
        return;
    }

    if (stu_game_instance->GetStartupLevelName().IsNone()) {
        UE_LOG(LogSTUMenuWidget, Error, TEXT("Level name is none."));
        return;
    }

    UGameplayStatics::OpenLevel(this, stu_game_instance->GetStartupLevelName());
}

void USTUMenuWidget::OnQuitGame() {
    UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}