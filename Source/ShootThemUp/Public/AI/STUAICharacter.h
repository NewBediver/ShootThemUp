// Shoot Them Up Game. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Player/STUBaseCharacter.h"
#include "STUAICharacter.generated.h"

class UBehaviorTree;
class UWidgetComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUAICharacter : public ASTUBaseCharacter {
    GENERATED_BODY()

  public:
    ASTUAICharacter(const FObjectInitializer& ObjInit);

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
    UBehaviorTree* behavior_tree_asset_ = nullptr;

    void Tick(float DeltaTime) override;

  protected:
    void BeginPlay() override;
    void OnDeath() override;
    void OnHealthChanged(float health, float health_delta) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UWidgetComponent* HealthWidgetComponent = nullptr;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
    float HealthVisibilityDistance = 1000.0f;

  private:
    void UpdateHealthWidgetVisibility();
};
