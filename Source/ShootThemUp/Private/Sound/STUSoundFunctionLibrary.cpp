// Shoot Them Up Game. All Right Reserved.

#include "Sound/STUSoundFunctionLibrary.h"
#include "Sound/SoundClass.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUSoundFunctionLib, All, All);

void USTUSoundFunctionLibrary::SetSoundClassVolume(USoundClass* sound_class, float volume) {
    if (sound_class == nullptr) {
        return;
    }

    sound_class->Properties.Volume = FMath::Clamp(volume, 0.0f, 1.0f);
    UE_LOG(LogSTUSoundFunctionLib, Display, TEXT("Sound class volume has been changed: %s = %f"),
           *sound_class->GetName(), sound_class->Properties.Volume);
}

void USTUSoundFunctionLibrary::ToggleSoundClassVolume(USoundClass* sound_class) {
    if (sound_class == nullptr) {
        return;
    }

    const auto next_volume = sound_class->Properties.Volume > 0.0f ? 0.0f : 1.0f;
    SetSoundClassVolume(sound_class, next_volume);
}