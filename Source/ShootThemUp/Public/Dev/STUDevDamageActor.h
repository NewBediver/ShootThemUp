// Shoot Them Up Game. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUDevDamageActor.generated.h"

UCLASS()
class SHOOTTHEMUP_API ASTUDevDamageActor : public AActor {
    GENERATED_BODY()

  public:
    // Sets default values for this actor's properties
    ASTUDevDamageActor();

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    USceneComponent* scene_component_ = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float radius_ = 300.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FColor sphere_color_ = FColor::Red;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float damage_ = 10.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool do_full_damage_ = false;

  protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

  public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;
};
