// Shoot Them Up Game. All Right Reserved.

#include "STUGameInstance.h"
#include "Sound/STUSoundFunctionLibrary.h"

FLevelData USTUGameInstance::GetStartupLevel() const {
    return StartupLevel;
}

void USTUGameInstance::SetStartupLevel(const FLevelData& data) {
    StartupLevel = data;
}

TArray<FLevelData> USTUGameInstance::GetLevelsData() const {
    return LevelsData;
}

FName USTUGameInstance::GetMenuLevelName() const {
    return MenuLevelName;
}

void USTUGameInstance::ToggleVolume() {
    USTUSoundFunctionLibrary::ToggleSoundClassVolume(MasterSoundClass);
}