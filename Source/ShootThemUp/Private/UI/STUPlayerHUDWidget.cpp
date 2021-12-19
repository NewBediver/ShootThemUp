// Shoot Them Up Game. All Right Reserved.


#include "UI/STUPlayerHUDWidget.h"
#include "Components/STUHealthComponent.h"
#include "Components/STUWeaponComponent.h"

float USTUPlayerHUDWidget::GetHealthPercent() const {
    const auto health_component = GetHealthComponent();
    if (health_component == nullptr) {
        return 0.0f;
    }

    return health_component->GetHealthPercent();
}

bool USTUPlayerHUDWidget::GetCurrentWeaponUIData(FWeaponUIData& ui_data) const {
    const auto weapon_component = GetWeaponComponent();
    return weapon_component != nullptr &&
           weapon_component->GetWeaponUIData(ui_data);
}

bool USTUPlayerHUDWidget::GetCurrentAmmoData(FAmmoData& ammo_data) const {
    const auto weapon_component = GetWeaponComponent();
    return weapon_component != nullptr &&
           weapon_component->GetAmmoData(ammo_data);
}

bool USTUPlayerHUDWidget::IsPlayerAlive() const {
    const auto health_component = GetHealthComponent();
    return health_component != nullptr &&
           !health_component->IsDead();
}

bool USTUPlayerHUDWidget::IsPlayerSpectating() const {
    const auto controller = GetOwningPlayer();
    return controller != nullptr &&
           controller->GetStateName() == NAME_Spectating;
}

USTUWeaponComponent* USTUPlayerHUDWidget::GetWeaponComponent() const {
    const auto player = GetOwningPlayerPawn();
    if (player == nullptr) {
        return nullptr;
    }

    const auto component = player->GetComponentByClass(USTUWeaponComponent::StaticClass());
    return Cast<USTUWeaponComponent>(component);
}

USTUHealthComponent* USTUPlayerHUDWidget::GetHealthComponent() const {
    const auto player = GetOwningPlayerPawn();
    if (player == nullptr) {
        return nullptr;
    }

    const auto component = player->GetComponentByClass(USTUHealthComponent::StaticClass());
    return Cast<USTUHealthComponent>(component);
}