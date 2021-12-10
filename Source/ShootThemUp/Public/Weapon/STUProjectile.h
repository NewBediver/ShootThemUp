// Shoot Them Up Game. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUProjectile : public AActor {
    GENERATED_BODY()

  public:
    ASTUProjectile();

    void SetShotDirection(FVector direction);

  protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
    USphereComponent* CollisionComponent = nullptr;

    UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
    UProjectileMovementComponent* MovementComponent = nullptr;

  private:
    FVector direction_;
};
