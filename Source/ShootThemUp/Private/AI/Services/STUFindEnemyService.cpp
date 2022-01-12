// Shoot Them Up Game. All Right Reserved.

#include "AI/Services/STUFindEnemyService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "STUUtils.h"
#include "Components/STUAIPerceptionComponent.h"

USTUFindEnemyService::USTUFindEnemyService() {
    NodeName = "Find Enemy";
}

void USTUFindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
                                    float DeltaSeconds) {
    const auto blackboard = OwnerComp.GetBlackboardComponent();
    if (blackboard != nullptr) {
        const auto controller = OwnerComp.GetAIOwner();
        const auto perception_component =
            STUUtils::GetSTUPlayerComponent<USTUAIPerceptionComponent>(controller);
        if (perception_component != nullptr) {
            blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName,
                                         perception_component->GetClosestEnemy());
        }
    }
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}