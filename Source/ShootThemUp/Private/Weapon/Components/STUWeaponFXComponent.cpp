// Shoot Them Up Game. All Right Reserved.

#include "Weapon/Components/STUWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"

USTUWeaponFXComponent::USTUWeaponFXComponent() {
    PrimaryComponentTick.bCanEverTick = false;
}

void USTUWeaponFXComponent::PlayImpactFX(const FHitResult& hit) {
    UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), effect_, hit.ImpactPoint,
                                                   hit.ImpactNormal.Rotation());
}