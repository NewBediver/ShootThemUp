// Shoot Them Up Game. All Right Reserved.


#include "UI/STUPlayerHUDWidget.h"
#include "Components/STUHealthComponent.h"
#include "Components/STUWeaponComponent.h"

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

bool USTUPlayerHUDWidget::GetWeaponUIData(FWeaponUIData& ui_data) const {
    const auto player = GetOwningPlayerPawn();
    if (player == nullptr) {
        return false;
    }

    const auto component = player->GetComponentByClass(USTUWeaponComponent::StaticClass());
    const auto weapon_component = Cast<USTUWeaponComponent>(component);
    if (weapon_component == nullptr) {
        return false;
    }

    return weapon_component->GetWeaponUIData(ui_data);
}