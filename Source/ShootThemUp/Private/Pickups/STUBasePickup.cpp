// Shoot Them Up Game. All Right Reserved.

#include "Pickups/STUBasePickup.h"
#include "Components/sphereComponent.h"

ASTUBasePickup::ASTUBasePickup() {
    PrimaryActorTick.bCanEverTick = true;

    CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    CollisionComponent->InitSphereRadius(50.0f);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    SetRootComponent(CollisionComponent);
}

void ASTUBasePickup::BeginPlay() {
    Super::BeginPlay();

    check(CollisionComponent);
}

void ASTUBasePickup::NotifyActorBeginOverlap(AActor* OtherActor) {
    Super::NotifyActorBeginOverlap(OtherActor);

    const auto pawn = Cast<APawn>(OtherActor);
    if (GivePickupTo(pawn)) {
        PickupWasTaken();
    }
}

void ASTUBasePickup::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
}

bool ASTUBasePickup::GivePickupTo(APawn* PlayerPawn) {
    return false;
}

void ASTUBasePickup::PickupWasTaken() {
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    if (GetRootComponent() != nullptr) {
        GetRootComponent()->SetVisibility(false, true);
    }

    FTimerHandle respawn_timer_handle;
    GetWorldTimerManager().SetTimer(respawn_timer_handle, this, &ASTUBasePickup::Respawn,
                                    respawn_time_);
}

void ASTUBasePickup::Respawn() {
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    if (GetRootComponent() != nullptr) {
        GetRootComponent()->SetVisibility(true, true);
    }
}