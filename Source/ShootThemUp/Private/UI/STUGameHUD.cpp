// Shoot Them Up Game. All Right Reserved.

#include "UI/STUGameHUD.h"
#include "Engine/Canvas.h"
#include "Blueprint/UserWidget.h"
#include "STUGameModeBase.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUGameHUD, All, All);

void ASTUGameHUD::DrawHUD() {
    Super::DrawHUD();
    //DrawCrossHair();
}

void ASTUGameHUD::BeginPlay() {
    Super::BeginPlay();

    GameWidgets.Add(ESTUMatchState::InProgress,
                    CreateWidget<UUserWidget>(GetWorld(), player_hud_widget_class_));
    GameWidgets.Add(ESTUMatchState::Pause,
                    CreateWidget<UUserWidget>(GetWorld(), pause_widget_class_));
    GameWidgets.Add(ESTUMatchState::GameOver,
                    CreateWidget<UUserWidget>(GetWorld(), game_over_widget_class_));

    for (auto game_widget_pair : GameWidgets) {
        const auto game_widget = game_widget_pair.Value;
        if (game_widget == nullptr) {
            continue;
        }

        game_widget->AddToViewport();
        game_widget->SetVisibility(ESlateVisibility::Hidden);
    }


    if (GetWorld() != nullptr) {
        const auto game_mode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());
        if (game_mode != nullptr) {
            game_mode->OnMatchStateChanged.AddUObject(this, &ASTUGameHUD::OnMatchStateChanged);
        }
    }
}

void ASTUGameHUD::DrawCrossHair() {
    const TInterval<float> center(Canvas->SizeX * 0.5f, Canvas->SizeY * 0.5f);

    const float half_line_size = 10.0f;
    const float line_thickness = 2.0f;
    const FLinearColor line_color = FLinearColor::Green;

    DrawLine(center.Min - half_line_size, center.Max, center.Min + half_line_size, center.Max,
             line_color, line_thickness);
    DrawLine(center.Min, center.Max - half_line_size, center.Min, center.Max + half_line_size,
             line_color, line_thickness);
}

void ASTUGameHUD::OnMatchStateChanged(ESTUMatchState state) {
    if (CurrentWidget != nullptr) {
        CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
    }

    if (GameWidgets.Contains(state)) {
        CurrentWidget = GameWidgets[state];
    }

    if (CurrentWidget != nullptr) {
        CurrentWidget->SetVisibility(ESlateVisibility::Visible);
    }

    UE_LOG(LogSTUGameHUD, Display, TEXT("Match state changed: %s"), *UEnum::GetValueAsString(state));
}