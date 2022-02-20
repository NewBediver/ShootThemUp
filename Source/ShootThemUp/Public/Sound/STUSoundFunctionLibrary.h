// Shoot Them Up Game. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "STUSoundFunctionLibrary.generated.h"

class USoundClass;

UCLASS()
class SHOOTTHEMUP_API USTUSoundFunctionLibrary : public UBlueprintFunctionLibrary {
    GENERATED_BODY()

  public:
    UFUNCTION(BlueprintCallable)
    static void SetSoundClassVolume(USoundClass* sound_class, float volume);

    UFUNCTION(BlueprintCallable)
    static void ToggleSoundClassVolume(USoundClass* sound_class);
};
