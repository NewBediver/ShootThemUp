// Shoot Them Up Game. All Right Reserved.


#include "Weapon/STULauncherWeapon.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Weapon/STUProjectile.h"
#include "Kismet/GameplayStatics.h"

void ASTULauncherWeapon::StartFire() {
    MakeShot();
}

void ASTULauncherWeapon::MakeShot() {
    if (GetWorld() == nullptr) {
        return;
    }

    FVector trace_start;
    FVector trace_end;
    if (!GetTraceData(trace_start, trace_end)) {
        return;
    }

    const FTransform spawn_transform(FRotator::ZeroRotator, GetMuzzleWorldLocation());
    auto projectile = UGameplayStatics::BeginDeferredActorSpawnFromClass(
        GetWorld(), ProjectileClass, spawn_transform);

    // Set projectile params

    UGameplayStatics::FinishSpawningActor(projectile, spawn_transform);

    /* FHitResult hit_result;
    MakeHit(hit_result, trace_start, trace_end);

    if (hit_result.bBlockingHit &&
        FVector::DotProduct(hit_result.ImpactPoint - GetMuzzleWorldLocation(),
                            trace_end - GetMuzzleWorldLocation()) > 0.0f) {
        MakeDamage(hit_result);
        DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), hit_result.ImpactPoint, FColor::Red,
                      false, 3.0f, 0, 3.0f);
        DrawDebugSphere(GetWorld(), hit_result.ImpactPoint, 10.0f, 24, FColor::Yellow, false, 5.0f);
    } else {
        DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), trace_end, FColor::Red, false, 3.0f, 0,
                      3.0f);
    }*/
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