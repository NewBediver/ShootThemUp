// Shoot Them Up Game. All Right Reserved.

#include "Player/STUBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/STUCharacterMovementComponent.h"
#include "Components/STUHealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/STUWeaponComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Controller.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseCharacter, All, All);

// Sets default values
ASTUBaseCharacter::ASTUBaseCharacter(const FObjectInitializer& ObjInit)
    : Super(ObjInit.SetDefaultSubobjectClass<USTUCharacterMovementComponent>(
          ACharacter::CharacterMovementComponentName)) {
    PrimaryActorTick.bCanEverTick = true;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->bUsePawnControlRotation = true;
    SpringArmComponent->SocketOffset = FVector(0.0f, 100.0f, 80.0f);

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);

    HealthComponent = CreateDefaultSubobject<USTUHealthComponent>("HealthComponent");

    HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent");
    HealthTextComponent->SetupAttachment(GetRootComponent());
    HealthTextComponent->SetOwnerNoSee(true);

    WeaponComponent = CreateDefaultSubobject<USTUWeaponComponent>("WeaponComponent");
}

// Called when the game starts or when spawned
void ASTUBaseCharacter::BeginPlay() {
    Super::BeginPlay();

    check(HealthComponent);
    check(HealthTextComponent);
    check(GetCharacterMovement());

    OnHealthChanged(HealthComponent->GetHealth());
    HealthComponent->OnDeath.AddUObject(this, &ASTUBaseCharacter::OnDeath);
    HealthComponent->OnHealthChanged.AddUObject(this, &ASTUBaseCharacter::OnHealthChanged);

    LandedDelegate.AddDynamic(this, &ASTUBaseCharacter::OnGroundLanded);
}

// Called every frame
void ASTUBaseCharacter::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ASTUBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    check(PlayerInputComponent);
    check(WeaponComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &ASTUBaseCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ASTUBaseCharacter::MoveRight);
    PlayerInputComponent->BindAxis("LookUp", this, &ASTUBaseCharacter::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("TurnAround", this, &ASTUBaseCharacter::AddControllerYawInput);

    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASTUBaseCharacter::Jump);
    PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ASTUBaseCharacter::OnStartRunnig);
    PlayerInputComponent->BindAction("Run", IE_Released, this, &ASTUBaseCharacter::OnStopRunning);
    PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &USTUWeaponComponent::StartFire);
    PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &USTUWeaponComponent::StopFire);
    PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, WeaponComponent, &USTUWeaponComponent::NextWeapon);
}

bool ASTUBaseCharacter::IsRunning() const {
    return want_to_run_ && is_moving_forward_ && !GetVelocity().IsNearlyZero(0.5f);
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

void ASTUBaseCharacter::MoveForward(float Amount) {
    is_moving_forward_ = Amount > 0.0f;
    if (Amount == 0.0f) {
        return;
    }
    AddMovementInput(GetActorForwardVector(), Amount);
}

void ASTUBaseCharacter::MoveRight(float Amount) {
    if (Amount == 0.0f) {
        return;
    }
    AddMovementInput(GetActorRightVector(), Amount);
}

void ASTUBaseCharacter::OnStartRunnig() {
    want_to_run_ = true;
}

void ASTUBaseCharacter::OnStopRunning() {
    want_to_run_ = false;
}

void ASTUBaseCharacter::OnDeath() {
    UE_LOG(LogBaseCharacter, Display, TEXT("Player %s is dead"), *GetName());

    PlayAnimMontage(DeathAnimMontage);
    GetCharacterMovement()->DisableMovement();
    SetLifeSpan(LifeSpanOnDeath);

    if (Controller != nullptr) {
        Controller->ChangeState(NAME_Spectating);
    }

    GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    WeaponComponent->StopFire();
}

void ASTUBaseCharacter::OnHealthChanged(float health) {
    HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), health)));
}

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