// Shoot Them Up Game. All Right Reserved.

#include "AI/STUAIController.h"
#include "AI/STUAICharacter.h"
#include "Components/STUAIPerceptionComponent.h"

ASTUAIController::ASTUAIController() {
    stu_ai_perception_component_ =
        CreateDefaultSubobject<USTUAIPerceptionComponent>("STUPerceptionComponent");
    SetPerceptionComponent(*stu_ai_perception_component_);
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
    const auto aim_actor = stu_ai_perception_component_->GetClosestEnemy();
    SetFocus(aim_actor);
}