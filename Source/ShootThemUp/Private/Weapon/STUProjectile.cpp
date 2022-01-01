// Shoot Them Up Game. All Right Reserved.

#include "Weapon/STUProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Weapon/Components/STUWeaponFXComponent.h"

ASTUProjectile::ASTUProjectile() {
    PrimaryActorTick.bCanEverTick = false;

    CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    CollisionComponent->InitSphereRadius(5.0f);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
    CollisionComponent->bReturnMaterialOnMove = true;
    SetRootComponent(CollisionComponent);

    MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComponent");
    MovementComponent->InitialSpeed = 2000.0f;
    MovementComponent->ProjectileGravityScale = 0.0f;

    weapon_fx_component_ = CreateDefaultSubobject<USTUWeaponFXComponent>("WeaponFXComponent");
}

void ASTUProjectile::SetShotDirection(FVector direction) {
    direction_ = std::move(direction);
}

void ASTUProjectile::BeginPlay() {
    Super::BeginPlay();

    check(CollisionComponent);
    check(MovementComponent);
    check(weapon_fx_component_);

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
    weapon_fx_component_->PlayImpactFX(Hit);
    Destroy();
}

AController* ASTUProjectile::GetController() const {
    const auto pawn = Cast<APawn>(GetOwner());
    return pawn != nullptr ? pawn->GetController() : nullptr;
}