// Shoot Them Up Game. All Right Reserved.

#include "Weapon/Components/STUWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Kismet/GameplayStatics.h"
#include "Components/DecalComponent.h"
#include "Sound/SoundCue.h"

USTUWeaponFXComponent::USTUWeaponFXComponent() {
    PrimaryComponentTick.bCanEverTick = false;
}

void USTUWeaponFXComponent::PlayImpactFX(const FHitResult& hit) {
    auto impact_data = default_impact_data_;

    if (hit.PhysMaterial.IsValid()) {
        const auto phys_mat = hit.PhysMaterial.Get();
        if (impact_data_map_.Contains(phys_mat)) {
            impact_data = impact_data_map_[phys_mat];
        }
    }

    // niagara
    UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), impact_data.NiagaraEffect,
                                                   hit.ImpactPoint, hit.ImpactNormal.Rotation());

    // decal
    auto decal_component = UGameplayStatics::SpawnDecalAtLocation(
        GetWorld(), impact_data.DecalData.Material, impact_data.DecalData.Size, hit.ImpactPoint,
        hit.ImpactNormal.Rotation());

    if (decal_component != nullptr) {
        decal_component->SetFadeOut(impact_data.DecalData.LifeTime,
                                    impact_data.DecalData.FadeOutTime);
    }

    // sound
    UGameplayStatics::PlaySoundAtLocation(GetWorld(), impact_data.Sound, hit.ImpactPoint);
}