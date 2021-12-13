// Shoot Them Up Game. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUBaseWeapon.generated.h"

class USkeletalMeshComponent;

USTRUCT(BlueprintType)
struct FAmmoData {
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    int32 Bullets = 0;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon",
              meta = (EditCondition = "!IsInfinite"))
    int32 Clips = 0;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    bool IsInfinite = false;
};

UCLASS()
class SHOOTTHEMUP_API ASTUBaseWeapon : public AActor {
    GENERATED_BODY()

  public:
    ASTUBaseWeapon();

    virtual void StartFire();
    virtual void StopFire();

  protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
    USkeletalMeshComponent* WeaponMesh = nullptr;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    FName muzzle_socket_name_ = "MuzzleSocket";

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float trace_max_distance_ = 1500.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    FAmmoData default_ammo_{15, 10, false};

    virtual void BeginPlay() override;
    virtual void MakeShot();
    virtual bool GetTraceData(FVector& trace_start, FVector& trace_end) const;

    APlayerController* GetPlayerController() const;
    bool GetPlayerViewPoint(FVector& view_location, FRotator& view_rotation) const;
    FVector GetMuzzleWorldLocation();
    void MakeHit(FHitResult& hit_result, const FVector& trace_start,
                 const FVector& trace_end) const;

    void DecreaseAmmo();
    bool IsAmmoEmpty() const;
    bool IsClipEmpty() const;
    void ChangeClip();
    void LogAmmo();

  private:
    FAmmoData current_ammo_;
};
