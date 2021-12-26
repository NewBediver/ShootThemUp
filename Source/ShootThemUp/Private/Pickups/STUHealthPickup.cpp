// Shoot Them Up Game. All Right Reserved.


#include "Pickups/STUHealthPickup.h"
#include "Components/STUHealthComponent.h"
#include "STUUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthPickup, All, All);

bool ASTUHealthPickup::GivePickupTo(APawn* PlayerPawn) {
    const auto health_component = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(PlayerPawn);
    if (health_component == nullptr) {
        return false;
    }

    UE_LOG(LogHealthPickup, Display, TEXT("Health was taken!!!"));
    return health_component->TryToAddHealth(health_amount_);
}