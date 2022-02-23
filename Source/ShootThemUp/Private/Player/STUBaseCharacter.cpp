// Shoot Them Up Game. All Right Reserved.

#include "Player/STUBaseCharacter.h"
#include "Components/STUCharacterMovementComponent.h"
#include "Components/STUHealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/STUWeaponComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Controller.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseCharacter, All, All);

// Sets default values
ASTUBaseCharacter::ASTUBaseCharacter(const FObjectInitializer& ObjInit)
    : Super(ObjInit.SetDefaultSubobjectClass<USTUCharacterMovementComponent>(
          ACharacter::CharacterMovementComponentName)) {
    PrimaryActorTick.bCanEverTick = true;

    HealthComponent = CreateDefaultSubobject<USTUHealthComponent>("HealthComponent");
    WeaponComponent = CreateDefaultSubobject<USTUWeaponComponent>("WeaponComponent");
}

// Called when the game starts or when spawned
void ASTUBaseCharacter::BeginPlay() {
    Super::BeginPlay();

    check(HealthComponent);
    check(GetCharacterMovement());

    OnHealthChanged(HealthComponent->GetHealth(), 0.0f);
    HealthComponent->OnDeath.AddUObject(this, &ASTUBaseCharacter::OnDeath);
    HealthComponent->OnHealthChanged.AddUObject(this, &ASTUBaseCharacter::OnHealthChanged);

    LandedDelegate.AddDynamic(this, &ASTUBaseCharacter::OnGroundLanded);
}

// Called every frame
void ASTUBaseCharacter::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
}

bool ASTUBaseCharacter::IsRunning() const {
    return false;
}

float ASTUBaseCharacter::GetMovementDirection() const {
    if (GetVelocity().IsZero()) {
        return 0.0f;
    }
    const auto velocity_normal = GetVelocity().GetSafeNormal();
    const auto angle_between =
        FMath::Acos(FVector::DotProduct(GetActorForwardVector(), velocity_normal));
    const auto cross_product = FVector::CrossProduct(GetActorForwardVector(), velocity_normal);
    const auto degrees = FMath::RadiansToDegrees(angle_between);
    return cross_product.IsZero()
               ? degrees
               : FMath::RadiansToDegrees(angle_between) * FMath::Sign(cross_product.Z);
}

void ASTUBaseCharacter::SetPlayerColor(const FLinearColor& color) {
    const auto material_instance = GetMesh()->CreateAndSetMaterialInstanceDynamic(0);
    if (material_instance == nullptr) {
        return;
    }

    material_instance->SetVectorParameterValue(MaterialColorName, color);
}

void ASTUBaseCharacter::OnDeath() {
    UE_LOG(LogBaseCharacter, Display, TEXT("Player %s is dead"), *GetName());

    // PlayAnimMontage(DeathAnimMontage);
    GetCharacterMovement()->DisableMovement();
    SetLifeSpan(LifeSpanOnDeath);

    GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    WeaponComponent->StopFire();
    WeaponComponent->Zoom(false);

    GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    GetMesh()->SetSimulatePhysics(true);

    UGameplayStatics::PlaySoundAtLocation(GetWorld(), DeathSound, GetActorLocation());
}

void ASTUBaseCharacter::OnHealthChanged(float health, float health_delta) {}

void ASTUBaseCharacter::OnGroundLanded(const FHitResult& Hit) {
    const auto fall_velocity_z = -GetVelocity().Z;
    UE_LOG(LogBaseCharacter, Display, TEXT("On landed: %f"), fall_velocity_z);

    if (fall_velocity_z < LandedDamageVelocity.X) {
        return;
    }
    const auto final_damage =
        FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, fall_velocity_z);
    UE_LOG(LogBaseCharacter, Display, TEXT("Final damage: %f"), final_damage);
    TakeDamage(final_damage, {}, nullptr, nullptr);
}