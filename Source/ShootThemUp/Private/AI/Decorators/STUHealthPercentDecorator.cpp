// Shoot Them Up Game. All Right Reserved.

#include "AI/Decorators/STUHealthPercentDecorator.h"
#include "AIController.h"
#include "STUUtils.h"
#include "Components/STUHealthComponent.h"

USTUHealthPercentDecorator::USTUHealthPercentDecorator() {
    NodeName = "Helth Percent";
}

bool USTUHealthPercentDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
                                                            uint8* NodeMemory) const {
    const auto controller = OwnerComp.GetAIOwner();
    if (controller == nullptr) {
        return false;
    }

    const auto health_component =
        STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(controller->GetPawn());
    if (health_component == nullptr || health_component->IsDead()) {
        return false;
    }

    return health_component->GetHealthPercent() <= HealthPercent;
}