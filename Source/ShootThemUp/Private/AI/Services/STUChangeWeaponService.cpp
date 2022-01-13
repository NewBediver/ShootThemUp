// Shoot Them Up Game. All Right Reserved.

#include "AI/Services/STUChangeWeaponService.h"
#include "Components/STUWeaponComponent.h"
#include "AIController.h"
#include "STUUtils.h"

USTUChangeWeaponService::USTUChangeWeaponService() {
    NodeName = "Change Weapon";
}

void USTUChangeWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
                                    float DeltaSeconds) {
    const auto controller = OwnerComp.GetAIOwner();
    if (controller != nullptr) {
        const auto weapon_component =
            STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(controller->GetPawn());
        if (weapon_component != nullptr &&
            Probability > 0.0f &&
            FMath::FRand() <= Probability) {
            weapon_component->NextWeapon();
        }
    }

    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}