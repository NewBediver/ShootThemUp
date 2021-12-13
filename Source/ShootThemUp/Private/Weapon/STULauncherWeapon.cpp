// Shoot Them Up Game. All Right Reserved.


#include "Weapon/STULauncherWeapon.h"
#include "Engine/World.h"
#include "Weapon/STUProjectile.h"

void ASTULauncherWeapon::StartFire() {
    MakeShot();
}

void ASTULauncherWeapon::MakeShot() {
    if (GetWorld() == nullptr ||
        IsAmmoEmpty()) {
        StopFire();
        return;
    }

    FVector trace_start;
    FVector trace_end;
    if (!GetTraceData(trace_start, trace_end)) {
        StopFire();
        return;
    }

    FHitResult hit_result;
    MakeHit(hit_result, trace_start, trace_end);

    const auto end_point = hit_result.bBlockingHit ? hit_result.ImpactPoint : trace_end;
    const auto direction = (end_point - GetMuzzleWorldLocation()).GetSafeNormal();

    const FTransform spawn_transform(FRotator::ZeroRotator, GetMuzzleWorldLocation());
    auto projectile = GetWorld()->SpawnActorDeferred<ASTUProjectile>(ProjectileClass, spawn_transform);
    if (projectile != nullptr) {
        projectile->SetShotDirection(direction);
        projectile->SetOwner(GetOwner());
        projectile->FinishSpawning(spawn_transform);
    }

    DecreaseAmmo();
}

bool ASTULauncherWeapon::GetTraceData(FVector& trace_start, FVector& trace_end) const {
    FVector view_location;
    FRotator view_rotation;
    if (!GetPlayerViewPoint(view_location, view_rotation)) {
        return false;
    }

    trace_start = view_location;
    trace_end = trace_start + view_rotation.Vector() * trace_max_distance_;
    return true;
}