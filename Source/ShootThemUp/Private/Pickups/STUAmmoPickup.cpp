// Shoot Them Up Game. All Right Reserved.

#include "Pickups/STUAmmoPickup.h"
#include "Components/STUHealthComponent.h"
#include "Components/STUWeaponComponent.h"
#include "STUUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogAmmoPickup, All, All);

bool ASTUAmmoPickup::GivePickupTo(APawn* PlayerPawn) {
    const auto health_component = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(PlayerPawn);
    if (health_component == nullptr ||
        health_component->IsDead()) {
        return false;
    }

    const auto weapon_component = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(PlayerPawn);
    if (weapon_component == nullptr) {
        return false;
    }

    return weapon_component->TryToAddAmmo(WeaponType, clips_amount_);
}
