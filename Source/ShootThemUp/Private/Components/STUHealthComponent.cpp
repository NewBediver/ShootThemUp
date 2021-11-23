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
}

float USTUHealthComponent::GetHealth() const {
    return health_;
}
