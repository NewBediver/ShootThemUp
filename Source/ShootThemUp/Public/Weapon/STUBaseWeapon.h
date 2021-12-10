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

    virtual void StartFire();
    virtual void StopFire();

  protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USkeletalMeshComponent* WeaponMesh = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    FName muzzle_socket_name_ = "MuzzleSocket";

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    float trace_max_distance_ = 1500.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    float damage_amount_ = 10.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    float time_between_shots_ = 0.1f;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    float bullet_spread_ = 1.5f;

    virtual void BeginPlay() override;

    void MakeShot();
    void MakeDamage(const FHitResult& hit_result);

  private:
    APlayerController* GetPlayerController() const;
    bool GetPlayerViewPoint(FVector& view_location, FRotator& view_rotation) const;
    FVector GetMuzzleWorldLocation();
    bool GetTraceData(FVector& trace_start, FVector& trace_end) const;
    void MakeHit(FHitResult& hit_result, const FVector& trace_start,
                 const FVector& trace_end) const;

    FTimerHandle shot_timer_handle_;
};
