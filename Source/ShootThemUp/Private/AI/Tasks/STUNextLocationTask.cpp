// Shoot Them Up Game. All Right Reserved.

#include "AI/Tasks/STUNextLocationTask.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"

USTUNextLocationTask::USTUNextLocationTask() {
    NodeName = "Next Location";
}

EBTNodeResult::Type USTUNextLocationTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp,
                                                      uint8* NodeMemory) {
    const auto controller = OwnerComp.GetAIOwner();
    const auto blackboard = OwnerComp.GetBlackboardComponent();
    if (controller == nullptr ||
        blackboard == nullptr) {
        return EBTNodeResult::Failed;
    }

    const auto pawn = controller->GetPawn();
    if (pawn == nullptr) {
        return EBTNodeResult::Failed;
    }

    const auto nav_sys = UNavigationSystemV1::GetCurrent(pawn);
    if (nav_sys == nullptr) {
        return EBTNodeResult::Failed;
    }

    FNavLocation nav_location;
    auto location = pawn->GetActorLocation();
    if (!self_center_) {
        auto center_actor =
            Cast<AActor>(blackboard->GetValueAsObject(center_actor_key_.SelectedKeyName));
        if (center_actor == nullptr) {
            return EBTNodeResult::Failed;
        }
        location = center_actor->GetActorLocation();
    }

    const auto found = nav_sys->GetRandomReachablePointInRadius(location, radius_, nav_location);
    if (!found) {
        return EBTNodeResult::Failed;
    }

    blackboard->SetValueAsVector(aim_location_key_.SelectedKeyName, nav_location.Location);
    return EBTNodeResult::Succeeded;
}