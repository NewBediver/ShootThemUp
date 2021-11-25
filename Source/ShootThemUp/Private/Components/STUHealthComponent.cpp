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
    UE_LOG(LogHealthComponent, Display, TEXT("Damage: %f"), Damage);

    if (DamageType != nullptr) {
        if (DamageType->IsA<USTUFireDamageType>()) {
            UE_LOG(LogHealthComponent, Display, TEXT("So hoooooooot!!!"));
        } else if (DamageType->IsA<USTUIceDamageType>()) {
            UE_LOG(LogHealthComponent, Display, TEXT("So cooooooold!!!"));
        }
    }
}