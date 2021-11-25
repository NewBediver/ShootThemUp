// Shoot Them Up Game. All Right Reserved.

#include "Dev/STUDevDamageActor.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASTUDevDamageActor::ASTUDevDamageActor() {
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if
    // you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    scene_component_ = CreateDefaultSubobject<USceneComponent>("SceneComponent");
    SetRootComponent(scene_component_);
}

// Called when the game starts or when spawned
void ASTUDevDamageActor::BeginPlay() {
    Super::BeginPlay();
}

// Called every frame
void ASTUDevDamageActor::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);

    DrawDebugSphere(GetWorld(), GetActorLocation(), radius_, 24, sphere_color_);
    UGameplayStatics::ApplyRadialDamage(GetWorld(), damage_, GetActorLocation(), radius_, nullptr,
                                        {}, this, nullptr, do_full_damage_);
}
