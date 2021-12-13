// Shoot Them Up Game. All Right Reserved.

#include "Components/STUWeaponComponent.h"
#include "Weapon/STUBaseWeapon.h"
#include "GameFramework/Character.h"
#include "Animations/STUEquipFinishedAnimNotify.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, All)

USTUWeaponComponent::USTUWeaponComponent() {
    PrimaryComponentTick.bCanEverTick = false;
}

void USTUWeaponComponent::StartFire() {
    if (current_weapon_ == nullptr) {
        return;
    }
    current_weapon_->StartFire();
}

void USTUWeaponComponent::StopFire() {
    if (current_weapon_ == nullptr) {
        return;
    }
    current_weapon_->StopFire();
}

void USTUWeaponComponent::NextWeapon() {
    current_weapon_index_ = (current_weapon_index_ + 1) % weapons_.Num();
    EquipWeapon(current_weapon_index_);
}

void USTUWeaponComponent::BeginPlay() {
    Super::BeginPlay();
    InitAnimations();
    SpawnWeapons();
    EquipWeapon(current_weapon_index_);
}

void USTUWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason) {
    current_weapon_ = nullptr;
    for (auto weapon : weapons_) {
        weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
        weapon->Destroy();
    }
    weapons_.Empty();
    Super::EndPlay(EndPlayReason);
}

void USTUWeaponComponent::SpawnWeapons() {
    if (GetWorld() == nullptr) {
        return;
    }

    const auto character = Cast<ACharacter>(GetOwner());
    if (character == nullptr) {
        return;
    }

    for (auto weapon_class : WeaponClasses) {
        auto weapon = GetWorld()->SpawnActor<ASTUBaseWeapon>(weapon_class);
        if (weapon == nullptr) {
            continue;
        }

        weapon->SetOwner(character);
        weapons_.Add(weapon);

        AttachWeaponToSocket(weapon, character->GetMesh(), WeaponArmorySocketName);
    }
}

void USTUWeaponComponent::AttachWeaponToSocket(ASTUBaseWeapon* weapon,
                                               USceneComponent* scene_component,
                                               const FName& socket_name) {
    if (weapon == nullptr ||
        scene_component == nullptr) {
        return;
    }
    FAttachmentTransformRules attachment_rules(EAttachmentRule::SnapToTarget, false);
    weapon->AttachToComponent(scene_component, attachment_rules, socket_name);
}

void USTUWeaponComponent::EquipWeapon(int32 weapon_index) {
    const auto character = Cast<ACharacter>(GetOwner());
    if (character == nullptr) {
        return;
    }

    if (current_weapon_ != nullptr) {
        current_weapon_->StopFire();
        AttachWeaponToSocket(current_weapon_, character->GetMesh(), WeaponArmorySocketName);
    }

    current_weapon_ = weapons_[weapon_index];
    AttachWeaponToSocket(current_weapon_, character->GetMesh(), WeaponEquipSocketName);
    PlayAnimMontage(EquipAnimMontage);
}

void USTUWeaponComponent::PlayAnimMontage(UAnimMontage* animation) {
    const auto character = Cast<ACharacter>(GetOwner());
    if (character == nullptr) {
        return;
    }

    character->PlayAnimMontage(animation);
}

void USTUWeaponComponent::InitAnimations() {
    if (EquipAnimMontage == nullptr) {
        return;
    }
    for (auto notify_event : EquipAnimMontage->Notifies) {
        auto on_equip_end_notify = Cast<USTUEquipFinishedAnimNotify>(notify_event.Notify);
        if (on_equip_end_notify != nullptr) {
            on_equip_end_notify->OnNotified.AddUObject(this, &USTUWeaponComponent::OnEquipFinished);
            break;
        }
    }
}

void USTUWeaponComponent::OnEquipFinished(USkeletalMeshComponent* mesh) {
    const auto character = Cast<ACharacter>(GetOwner());
    if (character == nullptr) {
        return;
    }

    if (character->GetMesh() == mesh) {
        UE_LOG(LogWeaponComponent, Display, TEXT("Equip finished"));
    }
}