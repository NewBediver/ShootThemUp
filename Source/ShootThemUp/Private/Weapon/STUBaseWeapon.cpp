// Shoot Them Up Game. All Right Reserved.

#include "Weapon/STUBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All);

ASTUBaseWeapon::ASTUBaseWeapon() {
    PrimaryActorTick.bCanEverTick = false;

    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
    SetRootComponent(WeaponMesh);
}

void ASTUBaseWeapon::Fire() {
    MakeShot();
}

void ASTUBaseWeapon::BeginPlay() {
    Super::BeginPlay();

    check(WeaponMesh);
}

void ASTUBaseWeapon::MakeShot() {
    if (GetWorld() == nullptr) {
        return;
    }

    FVector trace_start;
    FVector trace_end;
    if (!GetTraceData(trace_start, trace_end)) {
        return;
    }

    FHitResult hit_result;
    MakeHit(hit_result, trace_start, trace_end);

    if (hit_result.bBlockingHit &&
        FVector::DotProduct(hit_result.ImpactPoint - GetMuzzleWorldLocation(),
                            trace_end - GetMuzzleWorldLocation()) > 0.0f) {
        MakeDamage(hit_result);
        DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), hit_result.ImpactPoint, FColor::Red,
                      false, 3.0f, 0, 3.0f);
        DrawDebugSphere(GetWorld(), hit_result.ImpactPoint, 10.0f, 24, FColor::Yellow, false, 5.0f);
    } else {
        DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), trace_end, FColor::Red, false, 3.0f, 0, 3.0f);
    }
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

bool ASTUBaseWeapon::GetTraceData(FVector& trace_start, FVector& trace_end) const {
    FVector view_location;
    FRotator view_rotation;
    if (!GetPlayerViewPoint(view_location, view_rotation)) {
        return false;
    }

    trace_start = view_location;
    trace_end = trace_start + view_rotation.Vector() * trace_max_distance_;
    return true;
}

void ASTUBaseWeapon::MakeHit(FHitResult& hit_result, const FVector& trace_start,
                             const FVector& trace_end) const {
    FCollisionQueryParams collision_params;
    collision_params.AddIgnoredActor(GetOwner());
    GetWorld()->LineTraceSingleByChannel(hit_result, trace_start, trace_end,
                                         ECollisionChannel::ECC_Visibility, collision_params);
}

void ASTUBaseWeapon::MakeDamage(const FHitResult& hit_result) {
    const auto damaged_actor = hit_result.GetActor();
    if (damaged_actor == nullptr) {
        return;
    }

    damaged_actor->TakeDamage(damage_amount_, FDamageEvent(), GetPlayerController(), this);
}