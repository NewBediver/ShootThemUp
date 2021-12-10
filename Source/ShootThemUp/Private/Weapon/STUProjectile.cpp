// Shoot Them Up Game. All Right Reserved.

#include "Weapon/STUProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

ASTUProjectile::ASTUProjectile() {
    PrimaryActorTick.bCanEverTick = false;

    CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    CollisionComponent->InitSphereRadius(5.0f);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
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

    check(CollisionComponent);
    check(MovementComponent);

    MovementComponent->Velocity = direction_ * MovementComponent->InitialSpeed;

    CollisionComponent->IgnoreActorWhenMoving(GetOwner(), true);
    CollisionComponent->OnComponentHit.AddDynamic(this, &ASTUProjectile::OnProjectileHit);

    SetLifeSpan(life_seconds_);
}

void ASTUProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                                     UPrimitiveComponent* OtherComp, FVector NormalImpulse,
                                     const FHitResult& Hit) {
    if (GetWorld() == nullptr) {
        return;
    }

    MovementComponent->StopMovementImmediately();

    UGameplayStatics::ApplyRadialDamage(GetWorld(), damage_amount_, GetActorLocation(),
                                        damage_radius_, UDamageType::StaticClass(), {GetOwner()},
                                        this, GetController(), do_full_damage_);
    DrawDebugSphere(GetWorld(), GetActorLocation(), damage_radius_, 24, FColor::Blue, false, 5.0f);

    Destroy();
}

AController* ASTUProjectile::GetController() const {
    const auto pawn = Cast<APawn>(GetOwner());
    return pawn != nullptr ? pawn->GetController() : nullptr;
}