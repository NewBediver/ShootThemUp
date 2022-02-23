// Shoot Them Up Game. All Right Reserved.

#include "Components/STUHealthComponent.h"
#include "Dev/STUFireDamageType.h"
#include "Dev/STUIceDamageType.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Camera/CameraShakeBase.h"
#include "STUGameModeBase.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Perception/AISense_Damage.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All)

// Sets default values for this component's properties
USTUHealthComponent::USTUHealthComponent() {
    PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void USTUHealthComponent::BeginPlay() {
    Super::BeginPlay();

    check(max_health_ > 0);

    SetHealth(max_health_);

    auto owner = GetOwner();
    if (owner != nullptr) {
        owner->OnTakePointDamage.AddDynamic(this, &USTUHealthComponent::OnTakePointDamage);
        owner->OnTakeRadialDamage.AddDynamic(this, &USTUHealthComponent::OnTakeRadialDamage);
        owner->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::OnTakeAnyDamage);
    }
}

float USTUHealthComponent::GetHealth() const {
    return health_;
}

bool USTUHealthComponent::IsDead() const {
    return FMath::IsNearlyZero(health_);
}

float USTUHealthComponent::GetHealthPercent() const {
    return GetHealth() / max_health_;
}

bool USTUHealthComponent::TryToAddHealth(float health_amount) {
    if (IsDead() || IsHealthFull()) {
        return false;
    }

    SetHealth(health_ + health_amount);
    return true;
}

bool USTUHealthComponent::IsHealthFull() const {
    return FMath::IsNearlyEqual(health_, max_health_);
}

void USTUHealthComponent::HealUpdate() {
    SetHealth(health_ + heal_modifier_);

    if (IsHealthFull() && GetWorld() != nullptr) {
        GetWorld()->GetTimerManager().ClearTimer(heal_time_handle_);
    }
}

void USTUHealthComponent::SetHealth(float NewHealth) {
    const auto next_health = FMath::Clamp(NewHealth, 0.0f, max_health_);
    const auto health_delta = next_health - health_;

    health_ = FMath::Clamp(NewHealth, 0.0f, max_health_);
    OnHealthChanged.Broadcast(health_, health_delta);
}

void USTUHealthComponent::PlayCameraShake() {
    if (IsDead()) {
        return;
    }

    const auto player = Cast<APawn>(GetOwner());
    if (player == nullptr) {
        return;
    }

    const auto controller = player->GetController<APlayerController>();
    if (controller == nullptr || controller->PlayerCameraManager == nullptr) {
        return;
    }

    controller->PlayerCameraManager->StartCameraShake(camera_shake_);
}

void USTUHealthComponent::Killed(AController* killer_controller) {
    if (GetWorld() == nullptr) {
        return;
    }

    const auto game_mode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());
    if (game_mode == nullptr) {
        return;
    }

    const auto player = Cast<APawn>(GetOwner());
    const auto victim_controller = player != nullptr ? player->Controller : nullptr;

    game_mode->Killed(killer_controller, victim_controller);
}

void USTUHealthComponent::OnTakePointDamage(AActor* DamagedActor, float Damage,
                                            AController* InstigatedBy, FVector HitLocation,
                                            UPrimitiveComponent* FHitComponent, FName BoneName,
                                            FVector ShotFromDirection,
                                            const UDamageType* DamageType, AActor* DamageCauser) {
    const auto final_damage = Damage * GetPointDamageModifier(DamagedActor, BoneName);
    UE_LOG(LogHealthComponent, Display, TEXT("On point damage: %f, final damage: %f, bone: %s"), Damage, final_damage,
           *BoneName.ToString());
    ApplyDamage(final_damage, InstigatedBy);
}

void USTUHealthComponent::OnTakeRadialDamage(AActor* DamagedActor, float Damage,
                                             const UDamageType* DamageType, FVector Origin,
                                             FHitResult HitInfo, AController* InstigatedBy,
                                             AActor* DamageCauser) {
    UE_LOG(LogHealthComponent, Display, TEXT("On radial damage: %f"), Damage);
    ApplyDamage(Damage, InstigatedBy);
}

void USTUHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage,
                                          const class UDamageType* DamageType,
                                          class AController* InstigatedBy, AActor* DamageCauser) {
    UE_LOG(LogHealthComponent, Display, TEXT("On any damage: %f"), Damage);
}

void USTUHealthComponent::ApplyDamage(float damage, AController* instigated_by) {
    if (damage <= 0.0f || IsDead() || GetWorld() == nullptr) {
        return;
    }

    SetHealth(health_ - damage);
    if (IsDead()) {
        Killed(instigated_by);
        OnDeath.Broadcast();
    } else if (auto_heal_) {
        GetWorld()->GetTimerManager().SetTimer(heal_time_handle_, this,
                                               &USTUHealthComponent::HealUpdate, heal_update_time_,
                                               true, heal_delay_);
    }

    PlayCameraShake();
    ReportDamageEvent(damage, instigated_by);
}

float USTUHealthComponent::GetPointDamageModifier(AActor* damaged_actor, const FName& bone_name) {
    const auto character = Cast<ACharacter>(damaged_actor);
    if (character == nullptr ||
        character->GetMesh() == nullptr ||
        character->GetMesh()->GetBodyInstance(bone_name) == nullptr) {
        return 1.0f;
    }

    const auto phys_material =
        character->GetMesh()->GetBodyInstance(bone_name)->GetSimplePhysicalMaterial();
    if (!damage_modifiers_.Contains(phys_material)) {
        return 1.0f;
    }

    return damage_modifiers_[phys_material];
}

void USTUHealthComponent::ReportDamageEvent(float damage, AController* instigated_by) {
    if (GetWorld() == nullptr || GetOwner() == nullptr || instigated_by == nullptr ||
        instigated_by->GetPawn() == nullptr) {
        return;
    }

    UAISense_Damage::ReportDamageEvent(GetWorld(), GetOwner(), instigated_by->GetPawn(), damage,
                                       instigated_by->GetPawn()->GetActorLocation(),
                                       GetOwner()->GetActorLocation());
}