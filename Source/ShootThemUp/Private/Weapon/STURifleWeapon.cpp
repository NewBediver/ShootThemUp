// Shoot Them Up Game. All Right Reserved.


#include "Weapon/STURifleWeapon.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

void ASTURifleWeapon::StartFire() {
    MakeShot();
    GetWorldTimerManager().SetTimer(shot_timer_handle_, this, &ASTURifleWeapon::MakeShot,
                                    time_between_shots_, true);
}

void ASTURifleWeapon::StopFire() {
    GetWorldTimerManager().ClearTimer(shot_timer_handle_);
}

void ASTURifleWeapon::MakeShot() {
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
        DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), trace_end, FColor::Red, false, 3.0f, 0,
                      3.0f);
    }
}

bool ASTURifleWeapon::GetTraceData(FVector& trace_start, FVector& trace_end) const {
    FVector view_location;
    FRotator view_rotation;
    if (!GetPlayerViewPoint(view_location, view_rotation)) {
        return false;
    }

    trace_start = view_location;
    const auto half_rad = FMath::DegreesToRadians(bullet_spread_);
    const auto shoot_direction = FMath::VRandCone(view_rotation.Vector(), half_rad);
    trace_end = trace_start + shoot_direction * trace_max_distance_;
    return true;
}