// Shoot Them Up Game. All Right Reserved.


#include "UI/STUPlayerHUDWidget.h"
#include "Components/STUHealthComponent.h"
#include "Components/STUWeaponComponent.h"
#include "STuUtils.h"
#include "Components/ProgressBar.h"
#include "Player/STUPlayerState.h"

float USTUPlayerHUDWidget::GetHealthPercent() const {
    const auto health_component =
        STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(GetOwningPlayerPawn());
    if (health_component == nullptr) {
        return 0.0f;
    }

    return health_component->GetHealthPercent();
}

bool USTUPlayerHUDWidget::GetCurrentWeaponUIData(FWeaponUIData& ui_data) const {
    const auto weapon_component =
        STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(GetOwningPlayerPawn());
    return weapon_component != nullptr &&
           weapon_component->GetWeaponUIData(ui_data);
}

bool USTUPlayerHUDWidget::GetCurrentAmmoData(FAmmoData& ammo_data) const {
    const auto weapon_component =
        STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(GetOwningPlayerPawn());
    return weapon_component != nullptr &&
           weapon_component->GetAmmoData(ammo_data);
}

bool USTUPlayerHUDWidget::IsPlayerAlive() const {
    const auto health_component =
        STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(GetOwningPlayerPawn());
    return health_component != nullptr &&
           !health_component->IsDead();
}

bool USTUPlayerHUDWidget::IsPlayerSpectating() const {
    const auto controller = GetOwningPlayer();
    return controller != nullptr &&
           controller->GetStateName() == NAME_Spectating;
}

int32 USTUPlayerHUDWidget::GetKillsNum() const {
    const auto controller = GetOwningPlayer();
    if (controller == nullptr) {
        return 0;
    }

    const auto player_state = Cast<ASTUPlayerState>(controller->PlayerState);
    return player_state != nullptr ? player_state->GetKillNum() : 0;
}

void USTUPlayerHUDWidget::NativeOnInitialized() {
    Super::NativeOnInitialized();

    if (GetOwningPlayer() != nullptr) {
        GetOwningPlayer()->GetOnNewPawnNotifier().AddUObject(this, &USTUPlayerHUDWidget::OnNewPawn);
        OnNewPawn(GetOwningPlayerPawn());
    }
}

void USTUPlayerHUDWidget::OnHealthChanged(float health, float health_delta) {
    if (health_delta < 0.0f) {
        OnTakeDamage();
        if (!IsAnimationPlaying(DamageAnimation)) {
            PlayAnimation(DamageAnimation);
        }
    }
    UpdateHealthBar();
}

void USTUPlayerHUDWidget::OnNewPawn(APawn* new_pawn) {
  const auto health_component =
        STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(new_pawn);
    if (health_component != nullptr
            && !health_component->OnHealthChanged.IsBoundToObject(this)) {
        health_component->OnHealthChanged.AddUObject(this, &USTUPlayerHUDWidget::OnHealthChanged);
    }
    UpdateHealthBar();
    Show();
}

void USTUPlayerHUDWidget::UpdateHealthBar() {
    if (HealthProgressBar == nullptr) {
        return;
    }

    HealthProgressBar->SetFillColorAndOpacity(
        GetHealthPercent() > PercentColorThreshold ? GoodColor : BadColor);
}