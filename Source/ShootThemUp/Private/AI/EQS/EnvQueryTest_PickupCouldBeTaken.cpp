// Shoot Them Up Game. All Right Reserved.

#include "AI/EQS/EnvQueryTest_PickupCouldBeTaken.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_ActorBase.h"
#include "Pickups/STUBasePickup.h"

UEnvQueryTest_PickupCouldBeTaken::UEnvQueryTest_PickupCouldBeTaken(const FObjectInitializer& ObjInit)
    : Super(ObjInit) {
    Cost = EEnvTestCost::Low;
    ValidItemType = UEnvQueryItemType_ActorBase::StaticClass();
    SetWorkOnFloatValues(false);
}

void UEnvQueryTest_PickupCouldBeTaken::RunTest(FEnvQueryInstance& QueryInstance) const {
    const auto data_owner = QueryInstance.Owner.Get();
    BoolValue.BindData(data_owner, QueryInstance.QueryID);
    const auto wants_be_takable = BoolValue.GetValue();

    for (FEnvQueryInstance::ItemIterator it(this, QueryInstance); it; ++it) {
        const auto item_actor = GetItemActor(QueryInstance, it.GetIndex());
        const auto pickup_actor = Cast<ASTUBasePickup>(item_actor);
        if (pickup_actor == nullptr) {
            continue;
        }

        const auto could_be_taken = pickup_actor->CouldBeTaken();
        it.SetScore(TestPurpose, FilterType, could_be_taken, wants_be_takable);
    }
}