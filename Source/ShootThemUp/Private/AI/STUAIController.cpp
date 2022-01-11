// Shoot Them Up Game. All Right Reserved.

#include "AI/STUAIController.h"
#include "AI/STUAICharacter.h"

void ASTUAIController::OnPossess(APawn* in_pawn) {
    Super::OnPossess(in_pawn);
    const auto stu_character = Cast<ASTUAICharacter>(in_pawn);
    if (stu_character != nullptr) {
        RunBehaviorTree(stu_character->behavior_tree_asset_);
    }
}