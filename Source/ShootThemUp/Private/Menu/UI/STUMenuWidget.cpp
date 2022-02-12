// Shoot Them Up Game. All Right Reserved.

#include "Menu/UI/STUMenuWidget.h"
#include "Menu/UI/STULevelItemWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "STUGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/HorizontalBox.h"
#include "STUGameInstance.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUMenuWidget, All, All);

void USTUMenuWidget::NativeOnInitialized() {
    Super::NativeOnInitialized();

    if (StartGameButton != nullptr) {
        StartGameButton->OnClicked.AddDynamic(this, &USTUMenuWidget::OnStartGame);
    }

    if (QuitGameButton != nullptr) {
        QuitGameButton->OnClicked.AddDynamic(this, &USTUMenuWidget::OnQuitGame);
    }

    InitLevelItems();
}

void USTUMenuWidget::OnAnimationFinished_Implementation(const UWidgetAnimation* animation) {
    if (animation != HideAnimation) {
        return;
    }

    const auto stu_game_instance = GetSTUGameInstance();
    if (stu_game_instance == nullptr) {
        return;
    }

    UGameplayStatics::OpenLevel(this, stu_game_instance->GetStartupLevel().LevelName);
}

void USTUMenuWidget::OnStartGame() {
    PlayAnimation(HideAnimation);
}

void USTUMenuWidget::OnQuitGame() {
    UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}

void USTUMenuWidget::InitLevelItems() {
    const auto stu_game_instance = GetSTUGameInstance();
    if (stu_game_instance == nullptr) {
        return;
    }

    checkf(stu_game_instance->GetLevelsData().Num() != 0, TEXT("Levels data must not be empty!"));

    if (LevelItemsBox == nullptr) {
        return;
    }
    LevelItemsBox->ClearChildren();

    for (auto level_data : stu_game_instance->GetLevelsData()) {
        const auto level_item_widget =
            CreateWidget<USTULevelItemWidget>(GetWorld(), LevelItemWidgetClass);
        if (level_item_widget == nullptr) {
            continue;
        }

        level_item_widget->SetLevelData(level_data);
        level_item_widget->OnLevelSelected.AddUObject(this, &USTUMenuWidget::OnLevelSelected);

        LevelItemsBox->AddChild(level_item_widget);
        LevelItemWidgets.Add(level_item_widget);
    }

    if (stu_game_instance->GetStartupLevel().LevelName.IsNone()) {
        OnLevelSelected(stu_game_instance->GetLevelsData()[0]);
    } else {
        OnLevelSelected(stu_game_instance->GetStartupLevel());
    }
}

void USTUMenuWidget::OnLevelSelected(const FLevelData& data) {
    const auto stu_game_instance = GetSTUGameInstance();
    if (stu_game_instance == nullptr) {
        return;
    }

    stu_game_instance->SetStartupLevel(data);

    for (auto level_item_widget : LevelItemWidgets) {
        if (level_item_widget != nullptr) {
            const auto is_selected = data.LevelName == level_item_widget->GetLevelData().LevelName;
            level_item_widget->SetSelected(is_selected);
        }
    }
}

USTUGameInstance* USTUMenuWidget::GetSTUGameInstance() const {
    if (GetWorld() == nullptr) {
        return nullptr;
    }

    return GetWorld()->GetGameInstance<USTUGameInstance>();
}