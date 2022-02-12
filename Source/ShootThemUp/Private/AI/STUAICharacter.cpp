// Shoot Them Up Game. All Right Reserved.

#include "AI/STUAICharacter.h"
#include "AI/STUAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/STUAIWeaponComponent.h"
#include "BrainComponent.h"
#include "Components/WidgetComponent.h"
#include "UI/STUHealthBarWidget.h"
#include "Components/STUHealthComponent.h"

ASTUAICharacter::ASTUAICharacter(const FObjectInitializer& ObjInit)
    : Super(ObjInit.SetDefaultSubobjectClass<USTUAIWeaponComponent>("WeaponComponent")) {
    AutoPossessAI = EAutoPossessAI::Disabled;
    AIControllerClass = ASTUAIController::StaticClass();

    bUseControllerRotationYaw = false;
    if (GetCharacterMovement() != nullptr) {
        GetCharacterMovement()->bUseControllerDesiredRotation = true;
        GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
    }

    HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("HealthWidgetComponent");
    HealthWidgetComponent->SetupAttachment(GetRootComponent());
    HealthWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
    HealthWidgetComponent->SetDrawAtDesiredSize(true);
}

void ASTUAICharacter::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
    UpdateHealthWidgetVisibility();
}

void ASTUAICharacter::BeginPlay() {
    Super::BeginPlay();

    check(HealthWidgetComponent);
}

void ASTUAICharacter::OnDeath() {
    Super::OnDeath();

    const auto stu_controller = Cast<AAIController>(Controller);
    if (stu_controller != nullptr &&
        stu_controller->BrainComponent != nullptr) {
        stu_controller->BrainComponent->Cleanup();
    }
}

void ASTUAICharacter::OnHealthChanged(float health, float health_delta) {
    Super::OnHealthChanged(health, health_delta);

    const auto health_bar_widget =
        Cast<USTUHealthBarWidget>(HealthWidgetComponent->GetUserWidgetObject());
    if (health_bar_widget == nullptr) {
        return;
    }

    health_bar_widget->SetHealthPercent(HealthComponent->GetHealthPercent());
}

void ASTUAICharacter::UpdateHealthWidgetVisibility() {
    if (GetWorld() == nullptr ||
        GetWorld()->GetFirstPlayerController() == nullptr ||
        GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator() == nullptr) {
        return;
    }
    const auto player_location =
        GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator()->GetActorLocation();
    const auto distance = FVector::Distance(player_location, GetActorLocation());
    HealthWidgetComponent->SetVisibility(distance < HealthVisibilityDistance, true);
}