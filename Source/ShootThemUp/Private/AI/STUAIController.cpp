// Shoot Them Up Game. All Right Reserved.

#include "AI/STUAIController.h"
#include "AI/STUAICharacter.h"
#include "Components/STUAIPerceptionComponent.h"
#include "Components/STURespawnComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

ASTUAIController::ASTUAIController() {
    stu_ai_perception_component_ =
        CreateDefaultSubobject<USTUAIPerceptionComponent>("STUPerceptionComponent");
    SetPerceptionComponent(*stu_ai_perception_component_);

    RespawnComponent =
        CreateDefaultSubobject<USTURespawnComponent>("STURespawnComponent");

    bWantsPlayerState = true;
}

void ASTUAIController::OnPossess(APawn* in_pawn) {
    Super::OnPossess(in_pawn);
    const auto stu_character = Cast<ASTUAICharacter>(in_pawn);
    if (stu_character != nullptr) {
        RunBehaviorTree(stu_character->behavior_tree_asset_);
    }
}

void ASTUAIController::Tick(float delta_time) {
    Super::Tick(delta_time);
    const auto aim_actor = GetFocusOnActor();
    SetFocus(aim_actor);
}

AActor* ASTUAIController::GetFocusOnActor() const {
    if (GetBlackboardComponent() == nullptr) {
        return nullptr;
    }
    return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}