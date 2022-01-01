// Shoot Them Up Game. All Right Reserved.

#include "Weapon/Components/STUWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "PhysicalMaterials/PhysicalMaterial.h"

USTUWeaponFXComponent::USTUWeaponFXComponent() {
    PrimaryComponentTick.bCanEverTick = false;
}

void USTUWeaponFXComponent::PlayImpactFX(const FHitResult& hit) {
    auto effect = default_effect_;

    if (hit.PhysMaterial.IsValid()) {
        const auto phys_mat = hit.PhysMaterial.Get();
        if (effects_map_.Contains(phys_mat)) {
            effect = effects_map_[phys_mat];
        }
    }

    UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), effect, hit.ImpactPoint,
                                                   hit.ImpactNormal.Rotation());
}