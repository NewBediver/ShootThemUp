// Shoot Them Up Game. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUHealthComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTTHEMUP_API USTUHealthComponent : public UActorComponent {
    GENERATED_BODY()

  public:
    // Sets default values for this component's properties
    USTUHealthComponent();

    float GetHealth() const;

  protected:
    // Called when the game starts
    virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health",
              meta = (ClampMin = "0.0", ClampMax = "1000.0"))
    float max_health_ = 100.0f;

  private:
    UFUNCTION()
    void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
                         class AController* InstigatedBy, AActor* DamageCauser);

    float health_ = 0.0f;
};
