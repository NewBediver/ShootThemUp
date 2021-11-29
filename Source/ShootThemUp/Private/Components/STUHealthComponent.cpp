// Shoot Them Up Game. All Right Reserved.

#include "Components/STUHealthComponent.h"
#include "Dev/STUFireDamageType.h"
#include "Dev/STUIceDamageType.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All)

// Sets default values for this component's properties
USTUHealthComponent::USTUHealthComponent() {
    PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void USTUHealthComponent::BeginPlay() {
    Super::BeginPlay();

    health_ = max_health_;
    OnHealthChanged.Broadcast(health_);

    auto owner = GetOwner();
    if (owner != nullptr) {
        owner->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::OnTakeAnyDamage);
    }
}

float USTUHealthComponent::GetHealth() const {
    return health_;
}

bool USTUHealthComponent::IsDead() const {
    return GetHealth() <= 0.0f;
}

void USTUHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage,
                                          const class UDamageType* DamageType,
                                          class AController* InstigatedBy, AActor* DamageCauser) {
    if (Damage <= 0.0f ||
        IsDead()) {
        return;
    }
    health_ = FMath::Clamp(health_ - Damage, 0.0f, max_health_);
    OnHealthChanged.Broadcast(health_);
    if (IsDead()) {
        OnDeath.Broadcast();
    }
}