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

    GenerateRotationYaw();
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

    AddActorLocalRotation(FRotator(0.0f, rotation_yaw, 0.0f));
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
    GenerateRotationYaw();
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    if (GetRootComponent() != nullptr) {
        GetRootComponent()->SetVisibility(true, true);
    }
}

void ASTUBasePickup::GenerateRotationYaw() {
    const auto direction = FMath::RandBool() ? 1.0f : -1.0f;
    rotation_yaw = FMath::RandRange(1.0f, 2.0f) * direction;
}