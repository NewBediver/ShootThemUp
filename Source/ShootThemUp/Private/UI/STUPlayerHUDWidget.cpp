// Shoot Them Up Game. All Right Reserved.


#include "UI/STUPlayerHUDWidget.h"
#include "Components/STUHealthComponent.h"

float USTUPlayerHUDWidget::GetHealthPercent() const {
    const auto player = GetOwningPlayerPawn();
    if (player == nullptr) {
        return 0.0f;
    }

    const auto component = player->GetComponentByClass(USTUHealthComponent::StaticClass());
    const auto health_component = Cast<USTUHealthComponent>(component);
    if (health_component == nullptr) {
        return 0.0f;
    }

    return health_component->GetHealthPercent();
}