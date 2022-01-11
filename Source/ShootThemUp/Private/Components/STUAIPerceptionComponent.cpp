// Shoot Them Up Game. All Right Reserved.

#include "Components/STUAIPerceptionComponent.h"
#include "AIController.h"
#include "STUUtils.h"
#include "Components/STUHealthComponent.h"
#include "Perception/AISense_Sight.h"

AActor* USTUAIPerceptionComponent::GetClosestEnemy() const {
    TArray<AActor*> percieve_actors;
    GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), percieve_actors);
    if (percieve_actors.Num() == 0) {
        return nullptr;
    }

    const auto controller = Cast<AAIController>(GetOwner());
    if (controller == nullptr) {
        return nullptr;
    }

    const auto pawn = controller->GetPawn();
    if (pawn == nullptr) {
        return nullptr;
    }

    float best_distance = MAX_FLT;
    AActor* best_pawn = nullptr;
    for (const auto percieve_actor: percieve_actors) {
        const auto health_component =
            STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(percieve_actor);
        if (health_component != nullptr && // TODO: check if actor is enemy
            !health_component->IsDead()) {
            const auto current_distance =
                (percieve_actor->GetActorLocation() - pawn->GetActorLocation()).Size();
            if (current_distance < best_distance) {
                best_distance = current_distance;
                best_pawn = percieve_actor;
            }
        }
    }

    return best_pawn;
}