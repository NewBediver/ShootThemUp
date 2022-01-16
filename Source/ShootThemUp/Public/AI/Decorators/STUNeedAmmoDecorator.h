// Shoot Them Up Game. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "STUNeedAmmoDecorator.generated.h"

class ASTUBaseWeapon;

UCLASS()
class SHOOTTHEMUP_API USTUNeedAmmoDecorator : public UBTDecorator {
    GENERATED_BODY()

  public:
    USTUNeedAmmoDecorator();

  protected:
    bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
                                    uint8* NodeMemory) const override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    TSubclassOf<ASTUBaseWeapon> WeaponType;
};
