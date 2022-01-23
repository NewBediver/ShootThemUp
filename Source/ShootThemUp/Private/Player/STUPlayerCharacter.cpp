// Shoot Them Up Game. All Right Reserved.

#include "Player/STUPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/STUWeaponComponent.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"

ASTUPlayerCharacter::ASTUPlayerCharacter(const FObjectInitializer& ObjInit)
    : Super(ObjInit) {
    PrimaryActorTick.bCanEverTick = true;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->bUsePawnControlRotation = true;
    SpringArmComponent->SocketOffset = FVector(0.0f, 100.0f, 80.0f);

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);

    CameraCollisionComponent = CreateDefaultSubobject<USphereComponent>("CameraCollisionComponent");
    CameraCollisionComponent->SetupAttachment(CameraComponent);
    CameraCollisionComponent->SetSphereRadius(10.0f);
    CameraCollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
}

void ASTUPlayerCharacter::BeginPlay() {
    Super::BeginPlay();

    check(CameraCollisionComponent);

    CameraCollisionComponent->OnComponentBeginOverlap.AddDynamic(
        this, &ASTUPlayerCharacter::OnCameraCollisionBeginOverlap);
    CameraCollisionComponent->OnComponentEndOverlap.AddDynamic(
        this, &ASTUPlayerCharacter::OnCameraCollisionEndOverlap);
}

void ASTUPlayerCharacter::CheckCameraOverlap() {
    const auto hide_mesh = CameraCollisionComponent->IsOverlappingComponent(GetCapsuleComponent());
    GetMesh()->SetOwnerNoSee(hide_mesh);

    TArray<USceneComponent*> mesh_children;
    GetMesh()->GetChildrenComponents(true, mesh_children);

    for (auto mesh_child : mesh_children) {
        const auto mesh_child_geometry = Cast<UPrimitiveComponent>(mesh_child);
        if (mesh_child_geometry != nullptr) {
            mesh_child_geometry->SetOwnerNoSee(hide_mesh);
        }
    }
}

void ASTUPlayerCharacter::OnCameraCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent,
                                                        AActor* OtherActor,
                                                        UPrimitiveComponent* OtherComp,
                                                        int32 OtherBodyIndex, bool bFromSweep,
                                                        const FHitResult& SweepResult) {
    CheckCameraOverlap();
}

void ASTUPlayerCharacter::OnCameraCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent,
                                                      AActor* OtherActor,
                                                      UPrimitiveComponent* OtherComp,
                                                      int32 OtherBodyIndex) {
    CheckCameraOverlap();
}

void ASTUPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    check(PlayerInputComponent);
    check(WeaponComponent);
    check(GetCharacterMovement());
    check(GetMesh());

    PlayerInputComponent->BindAxis("MoveForward", this, &ASTUPlayerCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ASTUPlayerCharacter::MoveRight);
    PlayerInputComponent->BindAxis("LookUp", this, &ASTUPlayerCharacter::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("TurnAround", this, &ASTUPlayerCharacter::AddControllerYawInput);

    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASTUPlayerCharacter::Jump);
    PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ASTUPlayerCharacter::OnStartRunnig);
    PlayerInputComponent->BindAction("Run", IE_Released, this, &ASTUPlayerCharacter::OnStopRunning);
    PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent,
                                     &USTUWeaponComponent::StartFire);
    PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent,
                                     &USTUWeaponComponent::StopFire);
    PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, WeaponComponent,
                                     &USTUWeaponComponent::NextWeapon);
    PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent,
                                     &USTUWeaponComponent::Reload);
}

bool ASTUPlayerCharacter::IsRunning() const {
    return want_to_run_ && is_moving_forward_ && !GetVelocity().IsNearlyZero(0.5f);
}

void ASTUPlayerCharacter::MoveForward(float Amount) {
    is_moving_forward_ = Amount > 0.0f;
    if (Amount == 0.0f) {
        return;
    }
    AddMovementInput(GetActorForwardVector(), Amount);
}

void ASTUPlayerCharacter::MoveRight(float Amount) {
    if (Amount == 0.0f) {
        return;
    }
    AddMovementInput(GetActorRightVector(), Amount);
}

void ASTUPlayerCharacter::OnStartRunnig() {
    want_to_run_ = true;
}

void ASTUPlayerCharacter::OnStopRunning() {
    want_to_run_ = false;
}

void ASTUPlayerCharacter::OnDeath() {
    Super::OnDeath();

    if (Controller != nullptr) {
        Controller->ChangeState(NAME_Spectating);
    }
}