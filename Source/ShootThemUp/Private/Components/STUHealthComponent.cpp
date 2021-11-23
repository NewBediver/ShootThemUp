// Shoot Them Up Game. All Right Reserved.

#include "Components/STUHealthComponent.h"

// Sets default values for this component's properties
USTUHealthComponent::USTUHealthComponent() {
    PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void USTUHealthComponent::BeginPlay() {
    Super::BeginPlay();

    health_ = max_health_;

    auto owner = GetOwner();
    if (owner != nullptr) {
        owner->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::OnTakeAnyDamage);
    }
}

float USTUHealthComponent::GetHealth() const {
    return health_;
}

void USTUHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage,
                                          const class UDamageType* DamageType,
                                          class AController* InstigatedBy, AActor* DamageCauser) {
    health_ -= Damage;
}