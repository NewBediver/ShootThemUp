// Shoot Them Up Game. All Right Reserved.

#include "UI/STUHealthBarWidget.h"
#include "Components/ProgressBar.h"

void USTUHealthBarWidget::SetHealthPercent(float percent) {
    if (HealthProgressBar == nullptr) {
        return;
    }

    const auto health_bar_visibility =
        (percent > PercentVisibilityThreshold || FMath::IsNearlyZero(percent))
            ? ESlateVisibility::Hidden
            : ESlateVisibility::Visible;
    HealthProgressBar->SetVisibility(health_bar_visibility);
    
    const auto health_bar_color = percent > PercentColorThreshold ? GoodColor : BadColor;
    HealthProgressBar->SetFillColorAndOpacity(health_bar_color);

    HealthProgressBar->SetPercent(percent);
}