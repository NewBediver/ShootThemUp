// Shoot Them Up Game. All Right Reserved.

#include "Weapon/STUProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

ASTUProjectile::ASTUProjectile() {
    PrimaryActorTick.bCanEverTick = false;

    CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    CollisionComponent->InitSphereRadius(5.0f);
    SetRootComponent(CollisionComponent);

    MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComponent");
    MovementComponent->InitialSpeed = 2000.0f;
    MovementComponent->ProjectileGravityScale = 0.0f;
}

void ASTUProjectile::SetShotDirection(FVector direction) {
    direction_ = std::move(direction);
}

void ASTUProjectile::BeginPlay() {
    Super::BeginPlay();

    check(MovementComponent);

    MovementComponent->Velocity = direction_ * MovementComponent->InitialSpeed;

    SetLifeSpan(5.0f);
}