// Shoot Them Up Game. All Right Reserved.


#include "Weapon/STURifleWeapon.h"
#include "Engine/World.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Weapon/Components/STUWeaponFXComponent.h"

ASTURifleWeapon::ASTURifleWeapon() {
    weapon_fx_component_ = CreateDefaultSubobject<USTUWeaponFXComponent>("WeaponFXComponent");
}

void ASTURifleWeapon::StartFire() {
    InitMuzzleFX();
    GetWorldTimerManager().SetTimer(shot_timer_handle_, this, &ASTURifleWeapon::MakeShot,
                                    time_between_shots_, true);
    MakeShot();
}

void ASTURifleWeapon::StopFire() {
    GetWorldTimerManager().ClearTimer(shot_timer_handle_);
    SetMuzzleFXVisibility(false);
}

void ASTURifleWeapon::BeginPlay() {
    Super::BeginPlay();

    check(weapon_fx_component_);
}

void ASTURifleWeapon::MakeShot() {
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

    FVector trace_fx_end = trace_end;
    if (hit_result.bBlockingHit &&
        FVector::DotProduct(hit_result.ImpactPoint - GetMuzzleWorldLocation(),
                            trace_end - GetMuzzleWorldLocation()) > 0.0f) {
        trace_fx_end = hit_result.ImpactPoint;
        MakeDamage(hit_result);
        weapon_fx_component_->PlayImpactFX(hit_result);
    }

    SpawnTraceFX(GetMuzzleWorldLocation(), trace_fx_end);
    DecreaseAmmo();
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

void ASTURifleWeapon::MakeDamage(const FHitResult& hit_result) {
    const auto damaged_actor = hit_result.GetActor();
    if (damaged_actor == nullptr) {
        return;
    }

    damaged_actor->TakeDamage(damage_amount_, FDamageEvent(), GetPlayerController(), this);
}

void ASTURifleWeapon::InitMuzzleFX() {
    if (muzzle_fx_component_ == nullptr) {
        muzzle_fx_component_ = SpawnMuzzleFX();
    }
    SetMuzzleFXVisibility(true);
}

void ASTURifleWeapon::SetMuzzleFXVisibility(bool is_visible) {
    if (muzzle_fx_component_ != nullptr) {
        muzzle_fx_component_->SetPaused(!is_visible);
        muzzle_fx_component_->SetVisibility(is_visible, true);
    }
}

void ASTURifleWeapon::SpawnTraceFX(const FVector& trace_start, const FVector& trace_end) {
    const auto trace_fx_component =
        UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), trace_fx_, trace_start);
    if (trace_fx_component != nullptr) {
        trace_fx_component->SetNiagaraVariableVec3(trace_target_name_, trace_end);
    }
}