// Shoot Them Up Game. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUBasePickup.generated.h"

class USphereComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUBasePickup : public AActor {
    GENERATED_BODY()

  public:
    ASTUBasePickup();

  protected:
    virtual void BeginPlay() override;
    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

    UPROPERTY(VisibleAnywhere, Category = "Pickup")
    USphereComponent* CollisionComponent = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
    float respawn_time_ = 5.0f;

  public:
    virtual void Tick(float DeltaTime) override;

  private:
    virtual bool GivePickupTo(APawn* PlayerPawn);

    void PickupWasTaken();
    void Respawn();
};
