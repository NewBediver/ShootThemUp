// Shoot Them Up Game. All Right Reserved.

#include "UI/STUGameHUD.h"
#include "Engine/Canvas.h"
#include "Blueprint/UserWidget.h"

void ASTUGameHUD::DrawHUD() {
    Super::DrawHUD();
    DrawCrossHair();
}

void ASTUGameHUD::BeginPlay() {
    Super::BeginPlay();
    auto player_hud_widget = CreateWidget<UUserWidget>(GetWorld(), player_hud_widget_class_);

    if (player_hud_widget != nullptr) {
        player_hud_widget->AddToViewport();
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