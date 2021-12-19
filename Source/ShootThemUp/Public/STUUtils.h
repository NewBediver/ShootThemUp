#pragma once

class STUUtils {
  public:
    template <typename T>
    static T* GetSTUPlayerComponent(APawn* player_pawn) {
        if (player_pawn == nullptr) {
            return nullptr;
        }

        const auto component = player_pawn->GetComponentByClass(T::StaticClass());
        return Cast<T>(component);
    }
};