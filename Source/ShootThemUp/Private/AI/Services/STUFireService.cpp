// Shoot Them Up Game. All Right Reserved.

#include "AI/Services/STUFireService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "STUUtils.h"
#include "Components/STUWeaponComponent.h"

USTUFireService::USTUFireService() {
    NodeName = "Fire";
}

void USTUFireService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
                               float DeltaSeconds) {
    const auto controller = OwnerComp.GetAIOwner();
    const auto blackboard = OwnerComp.GetBlackboardComponent();

    const auto has_aim =
        blackboard != nullptr &&
        blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName);

    if (controller != nullptr) {
        const auto weapon_component =
            STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(controller->GetPawn());
        if (weapon_component != nullptr) {
            has_aim ?
                weapon_component->StartFire() :
                weapon_component->StopFire();
        }
    }

    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}