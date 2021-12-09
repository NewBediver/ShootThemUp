// Shoot Them Up Game. All Right Reserved.

#include "Components/STUWeaponComponent.h"
#include "Weapon/STUBaseWeapon.h"
#include "GameFramework/Character.h"

USTUWeaponComponent::USTUWeaponComponent() {
    PrimaryComponentTick.bCanEverTick = false;
}

void USTUWeaponComponent::Fire() {
    if (current_weapon_ == nullptr) {
        return;
    }
    current_weapon_->Fire();
}

void USTUWeaponComponent::BeginPlay() {
    Super::BeginPlay();
    SpawnWeapon();
}

void USTUWeaponComponent::SpawnWeapon() {
    if (GetWorld() == nullptr) {
        return;
    }

    const auto character = Cast<ACharacter>(GetOwner());
    if (character == nullptr) {
        return;
    }

    current_weapon_ = GetWorld()->SpawnActor<ASTUBaseWeapon>(WeaponClass);
    if (current_weapon_ == nullptr) {
        return;
    }

    FAttachmentTransformRules attachment_rules(EAttachmentRule::SnapToTarget, false);
    current_weapon_->AttachToComponent(character->GetMesh(), attachment_rules,
                                       WeaponAttachPointName);
    current_weapon_->SetOwner(character);
}