// Shoot Them Up Game. All Right Reserved.

#include "Components/STUAIWeaponComponent.h"
#include "Weapon/STUBaseWeapon.h"

void USTUAIWeaponComponent::StartFire() {
    if (!CanFire()) {
        return;
    }

    if (current_weapon_->IsAmmoEmpty()) {
        NextWeapon();
    } else {
        current_weapon_->StartFire();
    }
}

void USTUAIWeaponComponent::NextWeapon() {
    if (!CanEquip()) {
        return;
    }
    int32 next_index = (current_weapon_index_ + 1) % weapons_.Num();
    while (next_index != current_weapon_index_) {
        if (!weapons_[next_index]->IsAmmoEmpty()) {
            break;
        }
        next_index = (next_index + 1) % weapons_.Num();
    }

    if (current_weapon_index_ != next_index) {
        current_weapon_index_ = next_index;
        EquipWeapon(current_weapon_index_);
    }
}