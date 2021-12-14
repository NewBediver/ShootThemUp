// Shoot Them Up Game. All Right Reserved.

#include "Components/STUWeaponComponent.h"
#include "Weapon/STUBaseWeapon.h"
#include "GameFramework/Character.h"
#include "Animations/STUEquipFinishedAnimNotify.h"
#include "Animations/STUReloadFinishedAnimNotify.h"
#include "Animations/AnimUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, All)

constexpr static int32 WEAPON_NUM = 2;

USTUWeaponComponent::USTUWeaponComponent() {
    PrimaryComponentTick.bCanEverTick = false;
}

void USTUWeaponComponent::StartFire() {
    if (!CanFire()) {
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
    if (!CanEquip()) {
        return;
    }

    current_weapon_index_ = (current_weapon_index_ + 1) % weapons_.Num();
    EquipWeapon(current_weapon_index_);
}

void USTUWeaponComponent::Reload() {
    ChangeClip();
}

void USTUWeaponComponent::BeginPlay() {
    Super::BeginPlay();

    checkf(WeaponData.Num() == WEAPON_NUM, TEXT("Our character can hold only %i weapon items!"), WEAPON_NUM);

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

    for (auto weapon_data : WeaponData) {
        auto weapon = GetWorld()->SpawnActor<ASTUBaseWeapon>(weapon_data.WeaponClass);
        if (weapon == nullptr) {
            continue;
        }

        weapon->FOnClipEmpty.AddUObject(this, &USTUWeaponComponent::OnEmptyClip);
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
  if (weapon_index < 0 ||
    weapon_index >= weapons_.Num()) {
        UE_LOG(LogWeaponComponent, Display, TEXT("Invalid weapon index"));
        return;
    }

    const auto character = Cast<ACharacter>(GetOwner());
    if (character == nullptr) {
        return;
    }

    if (current_weapon_ != nullptr) {
        current_weapon_->StopFire();
        AttachWeaponToSocket(current_weapon_, character->GetMesh(), WeaponArmorySocketName);
    }

    current_weapon_ = weapons_[weapon_index];
    const auto current_weapon_data = WeaponData.FindByPredicate(
        [&](const FWeaponData& data) { return data.WeaponClass == current_weapon_->GetClass(); });
    current_reload_anim_montage_ = current_weapon_data != nullptr ?
                                   current_weapon_data->ReloadAnimMontage :
                                   nullptr;

    AttachWeaponToSocket(current_weapon_, character->GetMesh(), WeaponEquipSocketName);
    equip_anim_in_progress_ = true;
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
    auto equip_finished_notify =
        AnimUtils::FindNotifyByClass<USTUEquipFinishedAnimNotify>(EquipAnimMontage);
    if (equip_finished_notify != nullptr) {
        equip_finished_notify->OnNotified.AddUObject(this, &USTUWeaponComponent::OnEquipFinished);
    } else {
        UE_LOG(LogWeaponComponent, Error, TEXT("Equip anim notify is forgotten to set!"));
        checkNoEntry();
    }

    for (auto weapon_data : WeaponData) {
        auto reload_finished_notify =
            AnimUtils::FindNotifyByClass<USTUReloadFinishedAnimNotify>(weapon_data.ReloadAnimMontage);
        if (reload_finished_notify == nullptr) {
            UE_LOG(LogWeaponComponent, Error, TEXT("Equip anim notify is forgotten to set!"));
            checkNoEntry();
        }
        reload_finished_notify->OnNotified.AddUObject(this, &USTUWeaponComponent::OnReloadFinished);
    }
}

void USTUWeaponComponent::OnEquipFinished(USkeletalMeshComponent* mesh) {
    const auto character = Cast<ACharacter>(GetOwner());
    if (character == nullptr ||
        character->GetMesh() != mesh) {
        return;
    }

    equip_anim_in_progress_ = false;
}

void USTUWeaponComponent::OnReloadFinished(USkeletalMeshComponent* mesh) {
    const auto character = Cast<ACharacter>(GetOwner());
    if (character == nullptr ||
        character->GetMesh() != mesh) {
        return;
    }

    reload_anim_in_progress_ = false;
}

bool USTUWeaponComponent::CanFire() const {
    return current_weapon_ != nullptr &&
           !equip_anim_in_progress_ &&
           !reload_anim_in_progress_;
}

bool USTUWeaponComponent::CanEquip() const {
    return !equip_anim_in_progress_ &&
           !reload_anim_in_progress_;
}

bool USTUWeaponComponent::CanReload() const {
    return current_weapon_ != nullptr &&
           !equip_anim_in_progress_ &&
           !reload_anim_in_progress_ &&
           current_weapon_->CanReload();
}

void USTUWeaponComponent::OnEmptyClip() {
    ChangeClip();
}

void USTUWeaponComponent::ChangeClip() {
    if (!CanReload()) {
        return;
    }
    current_weapon_->StopFire();
    current_weapon_->ChangeClip();
    reload_anim_in_progress_ = true;
    PlayAnimMontage(current_reload_anim_montage_);
}