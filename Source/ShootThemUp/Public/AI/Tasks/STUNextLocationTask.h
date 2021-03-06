// Shoot Them Up Game. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "STUNextLocationTask.generated.h"

UCLASS()
class SHOOTTHEMUP_API USTUNextLocationTask : public UBTTaskNode {
    GENERATED_BODY()

  public:
    USTUNextLocationTask();

    EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

  protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    float radius_ = 1000.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FBlackboardKeySelector aim_location_key_;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    bool self_center_ = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI",
              meta = (Editcondition = "!self_center_"))
    FBlackboardKeySelector center_actor_key_;
};
