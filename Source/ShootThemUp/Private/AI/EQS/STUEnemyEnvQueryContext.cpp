// Shoot Them Up Game. All Right Reserved.

#include "AI/EQS/STUEnemyEnvQueryContext.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

void USTUEnemyEnvQueryContext::ProvideContext(FEnvQueryInstance& QueryInstance,
                                              FEnvQueryContextData& ContextData) const {
    const auto query_owner = Cast<AActor>(QueryInstance.Owner.Get());

    const auto blackboard = UAIBlueprintHelperLibrary::GetBlackboard(query_owner);
    if (blackboard == nullptr) {
        return;
    }

    const auto context_actor = blackboard->GetValueAsObject(EnemyActorKeyName);
    UEnvQueryItemType_Actor::SetContextHelper(ContextData, Cast<AActor>(context_actor));
}