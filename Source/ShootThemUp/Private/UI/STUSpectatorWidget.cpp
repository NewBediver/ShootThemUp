// Shoot Them Up Game. All Right Reserved.

#include "UI/STUSpectatorWidget.h"
#include "STUUtils.h"
#include "Components/STURespawnComponent.h"

bool USTUSpectatorWidget::GetRespawnTime(int32& count_down_time) const {
    const auto respawn_component =
        STUUtils::GetSTUPlayerComponent<USTURespawnComponent>(GetOwningPlayer());
    if (respawn_component == nullptr
            || !respawn_component->IsRespawnInProgress()) {
        return false;
    }

    count_down_time = respawn_component->GetRespawnCountDown();
    return true;
}