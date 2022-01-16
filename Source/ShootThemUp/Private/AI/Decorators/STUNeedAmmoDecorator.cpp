// Shoot Them Up Game. All Right Reserved.

#include "AI/Decorators/STUNeedAmmoDecorator.h"
#include "AIController.h"
#include "STUUtils.h"
#include "Components/STUWeaponComponent.h"

USTUNeedAmmoDecorator::USTUNeedAmmoDecorator() {
    NodeName = "Need ammo";
}

bool USTUNeedAmmoDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
                                                       uint8* NodeMemory) const {
    const auto controller = OwnerComp.GetAIOwner();
    if (controller == nullptr) {
        return false;
    }

    const auto weaponh_component =
        STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(controller->GetPawn());
    if (weaponh_component == nullptr) {
        return false;
    }

    return weaponh_component->NeedAmmo(WeaponType);
}