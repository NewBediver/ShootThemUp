// Shoot Them Up Game. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUBaseWeapon.h"
#include "STURifleWeapon.generated.h"

/**
 *
 */
UCLASS()
class SHOOTTHEMUP_API ASTURifleWeapon : public ASTUBaseWeapon {
    GENERATED_BODY()

  public:
    void StartFire() override;
    void StopFire() override;

  protected:
    void MakeShot() override;
    bool GetTraceData(FVector& trace_start, FVector& trace_end) const override;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    float time_between_shots_ = 0.1f;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    float bullet_spread_ = 1.5f;

  private:
    FTimerHandle shot_timer_handle_;
};
