// Shoot Them Up Game. All Right Reserved.

#include "Weapon/STUBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All);

ASTUBaseWeapon::ASTUBaseWeapon() {
    PrimaryActorTick.bCanEverTick = false;

    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
    SetRootComponent(WeaponMesh);
}

void ASTUBaseWeapon::StartFire() {}

void ASTUBaseWeapon::StopFire() {}

void ASTUBaseWeapon::MakeShot() {}

bool ASTUBaseWeapon::GetTraceData(FVector& trace_start, FVector& trace_end) const {
    return false;
}

void ASTUBaseWeapon::BeginPlay() {
    Super::BeginPlay();

    check(WeaponMesh);

    current_ammo_ = default_ammo_;
}

APlayerController* ASTUBaseWeapon::GetPlayerController() const {
    const auto player = Cast<ACharacter>(GetOwner());
    if (player == nullptr) {
        return nullptr;
    }

    const auto controller = player->GetController<APlayerController>();
    if (controller == nullptr) {
        return nullptr;
    }

    return controller;
}

bool ASTUBaseWeapon::GetPlayerViewPoint(FVector& view_location, FRotator& view_rotation) const {
    const auto controller = GetPlayerController();
    if (controller == nullptr) {
        return false;
    }

    controller->GetPlayerViewPoint(view_location, view_rotation);
    return true;
}

FVector ASTUBaseWeapon::GetMuzzleWorldLocation() {
    return WeaponMesh->GetSocketTransform(muzzle_socket_name_).GetTranslation();
}

void ASTUBaseWeapon::MakeHit(FHitResult& hit_result, const FVector& trace_start,
                             const FVector& trace_end) const {
    FCollisionQueryParams collision_params;
    collision_params.AddIgnoredActor(GetOwner());
    GetWorld()->LineTraceSingleByChannel(hit_result, trace_start, trace_end,
                                         ECollisionChannel::ECC_Visibility, collision_params);
}

void ASTUBaseWeapon::DecreaseAmmo() {
    --current_ammo_.Bullets;
    LogAmmo();

    if (IsClipEmpty() &&
        !IsAmmoEmpty()) {
        ChangeClip();
    }
}

bool ASTUBaseWeapon::IsAmmoEmpty() const {
  return !current_ammo_.IsInfinite &&
         current_ammo_.Clips == 0 &&
         IsClipEmpty();
}

bool ASTUBaseWeapon::IsClipEmpty() const {
    return current_ammo_.Bullets == 0;
}

void ASTUBaseWeapon::ChangeClip() {
    current_ammo_.Bullets = default_ammo_.Bullets;
    if (!current_ammo_.IsInfinite) {
        --current_ammo_.Clips;
    }
    UE_LOG(LogBaseWeapon, Display, TEXT("----- Change Clip -----"));
}

void ASTUBaseWeapon::LogAmmo() {
    FString ammo_info = "Ammo: " + FString::FromInt(current_ammo_.Bullets) + " / ";
    ammo_info += current_ammo_.IsInfinite ? "Infinite" : FString::FromInt(current_ammo_.Clips);
    UE_LOG(LogBaseWeapon, Display, TEXT("%s"), *ammo_info);
}