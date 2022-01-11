// Shoot Them Up Game. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "STUAIController.generated.h"

class USTUAIPerceptionComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUAIController : public AAIController {
    GENERATED_BODY()

  public:
    ASTUAIController();

  protected:
    void OnPossess(APawn* in_pawn) override;
    void Tick(float delta_time) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USTUAIPerceptionComponent* stu_ai_perception_component_ = nullptr;
};
