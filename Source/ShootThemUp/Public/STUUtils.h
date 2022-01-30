#pragma once
#include "Player/STUPlayerState.h"

class STUUtils {
  public:
    template <typename T>
    static T* GetSTUPlayerComponent(AActor* player_pawn) {
        if (player_pawn == nullptr) {
            return nullptr;
        }

        const auto component = player_pawn->GetComponentByClass(T::StaticClass());
        return Cast<T>(component);
    }

    static bool AreEnemies(AController* lhv, AController* rhv) {
        if (lhv == nullptr ||
            rhv == nullptr ||
            lhv == rhv) {
            return false;
        }

        const auto lhv_player_state = Cast<ASTUPlayerState>(lhv->PlayerState);
        const auto rhv_player_state = Cast<ASTUPlayerState>(rhv->PlayerState);

        return lhv_player_state != nullptr &&
               rhv_player_state != nullptr &&
               lhv_player_state->GetTeamID() != rhv_player_state->GetTeamID();
    }

    static FText TextFromInt(int32 number) {
        return FText::FromString(FString::FromInt(number));
    }
};