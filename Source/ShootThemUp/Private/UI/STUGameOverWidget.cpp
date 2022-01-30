// Shoot Them Up Game. All Right Reserved.


#include "UI/STUGameOverWidget.h"
#include "STUGameModeBase.h"
#include "Player/STUPlayerState.h"
#include "UI/STUPlayerStatRowWidget.h"
#include "Components/VerticalBox.h"
#include "STUUtils.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void USTUGameOverWidget::NativeOnInitialized() {
    Super::NativeOnInitialized();

    if (GetWorld() != nullptr) {
        const auto game_mode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());
        if (game_mode != nullptr) {
            game_mode->OnMatchStateChanged.AddUObject(this,
                                                      &USTUGameOverWidget::OnMatchStateChanged);
        }
    }

    if (ResetLevelButton != nullptr) {
        ResetLevelButton->OnClicked.AddDynamic(this, &USTUGameOverWidget::OnResetLevel);
    }
}

void USTUGameOverWidget::OnMatchStateChanged(ESTUMatchState state) {
    if (state == ESTUMatchState::GameOver) {
        UpdatePlayersStat();
    }
}

void USTUGameOverWidget::UpdatePlayersStat() {
    if (GetWorld() == nullptr || PlayerStatBox == nullptr) {
        return;
    }

    PlayerStatBox->ClearChildren();

    for (auto it = GetWorld()->GetControllerIterator(); it; ++it) {
        const auto controller = it->Get();
        if (controller == nullptr) {
            continue;
        }

        const auto player_state = Cast<ASTUPlayerState>(controller->PlayerState);
        if (player_state == nullptr) {
            continue;
        }

        const auto player_stat_row_widget =
            CreateWidget<USTUPlayerStatRowWidget>(GetWorld(), PlayerStatRowWidgetClass);
        if (player_stat_row_widget == nullptr) {
            continue;
        }

        player_stat_row_widget->SetPlayerName(FText::FromString(player_state->GetPlayerName()));
        player_stat_row_widget->SetKills(STUUtils::TextFromInt(player_state->GetKillNum()));
        player_stat_row_widget->SetDeaths(STUUtils::TextFromInt(player_state->GetDeathsNum()));
        player_stat_row_widget->SetTeam(STUUtils::TextFromInt(player_state->GetTeamID()));
        player_stat_row_widget->SetPlayerIndicatorVisibility(controller->IsPlayerController());

        PlayerStatBox->AddChild(player_stat_row_widget);
    }
}

void USTUGameOverWidget::OnResetLevel() {
    const FString current_level_name = UGameplayStatics::GetCurrentLevelName(this);
    UGameplayStatics::OpenLevel(this, FName(current_level_name));
}