// Shoot Them Up Game. All Right Reserved.


#include "UI/STUPlayerHUDWidget.h"
#include "Components/STUHealthComponent.h"
#include "Components/STUWeaponComponent.h"
#include "STuUtils.h"

float USTUPlayerHUDWidget::GetHealthPercent() const {
    const auto health_component =
        STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(GetOwningPlayerPawn());
    if (health_component == nullptr) {
        return 0.0f;
    }

    return health_component->GetHealthPercent();
}

bool USTUPlayerHUDWidget::GetCurrentWeaponUIData(FWeaponUIData& ui_data) const {
    const auto weapon_component =
        STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(GetOwningPlayerPawn());
    return weapon_component != nullptr &&
           weapon_component->GetWeaponUIData(ui_data);
}

bool USTUPlayerHUDWidget::GetCurrentAmmoData(FAmmoData& ammo_data) const {
    const auto weapon_component =
        STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(GetOwningPlayerPawn());
    return weapon_component != nullptr &&
           weapon_component->GetAmmoData(ammo_data);
}

bool USTUPlayerHUDWidget::IsPlayerAlive() const {
    const auto health_component =
        STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(GetOwningPlayerPawn());
    return health_component != nullptr &&
           !health_component->IsDead();
}

bool USTUPlayerHUDWidget::IsPlayerSpectating() const {
    const auto controller = GetOwningPlayer();
    return controller != nullptr &&
           controller->GetStateName() == NAME_Spectating;
}