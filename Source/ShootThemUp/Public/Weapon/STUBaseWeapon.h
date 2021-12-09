// Shoot Them Up Game. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUBaseWeapon.generated.h"

class USkeletalMeshComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUBaseWeapon : public AActor {
    GENERATED_BODY()

  public:
    ASTUBaseWeapon();

    virtual void Fire();

  protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USkeletalMeshComponent* WeaponMesh = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    FName muzzle_socket_name_ = "MuzzleSocket";

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    float trace_max_distance_ = 1500.0f;

    virtual void BeginPlay() override;

    void MakeShot();
};
