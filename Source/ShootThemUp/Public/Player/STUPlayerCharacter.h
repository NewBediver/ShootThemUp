// Shoot Them Up Game. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Player/STUBaseCharacter.h"
#include "STUPlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USphereComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUPlayerCharacter : public ASTUBaseCharacter {
    GENERATED_BODY()

  public:
    ASTUPlayerCharacter(const FObjectInitializer& ObjInit);

    void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    bool IsRunning() const override;

  protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USpringArmComponent* SpringArmComponent = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UCameraComponent* CameraComponent = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USphereComponent* CameraCollisionComponent = nullptr;

    void BeginPlay() override;
    void OnDeath() override;

  private:
    void MoveForward(float Amount);
    void MoveRight(float Amount);

    void OnStartRunnig();
    void OnStopRunning();
    void CheckCameraOverlap();

    UFUNCTION()
    void OnCameraCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                       UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                                       bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void OnCameraCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                     UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    bool want_to_run_ = false;
    bool is_moving_forward_ = false;
};
