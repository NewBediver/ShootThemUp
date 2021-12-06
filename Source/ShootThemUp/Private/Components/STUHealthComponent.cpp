// Shoot Them Up Game. All Right Reserved.

#include "Components/STUHealthComponent.h"
#include "Dev/STUFireDamageType.h"
#include "Dev/STUIceDamageType.h"
#include "Engine/World.h"
#include "TimerManager.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All)

// Sets default values for this component's properties
USTUHealthComponent::USTUHealthComponent() {
    PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void USTUHealthComponent::BeginPlay() {
    Super::BeginPlay();

    SetHealth(max_health_);

    auto owner = GetOwner();
    if (owner != nullptr) {
        owner->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::OnTakeAnyDamage);
    }
}

float USTUHealthComponent::GetHealth() const {
    return health_;
}

bool USTUHealthComponent::IsDead() const {
    return FMath::IsNearlyZero(health_);
}

void USTUHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage,
                                          const class UDamageType* DamageType,
                                          class AController* InstigatedBy, AActor* DamageCauser) {
    if (Damage <= 0.0f ||
        IsDead() ||
        GetWorld() == nullptr) {
        return;
    }
    SetHealth(health_ - Damage);
    if (IsDead()) {
        OnDeath.Broadcast();
    } else if (auto_heal_) {
        GetWorld()->GetTimerManager().SetTimer(heal_time_handle_, this,
                                               &USTUHealthComponent::HealUpdate, heal_update_time_,
                                               true, heal_delay_);
    }
}

void USTUHealthComponent::HealUpdate() {
    SetHealth(health_ + heal_modifier_);

    if (FMath::IsNearlyEqual(health_, max_health_) &&
        GetWorld() != nullptr) {
        GetWorld()->GetTimerManager().ClearTimer(heal_time_handle_);
    }
}

void USTUHealthComponent::SetHealth(float NewHealth) {
    health_ = FMath::Clamp(NewHealth, 0.0f, max_health_);
    OnHealthChanged.Broadcast(health_);
}