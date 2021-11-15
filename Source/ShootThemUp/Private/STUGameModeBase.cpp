// Shoot Them Up Game. All Right Reserved.

#include "STUGameModeBase.h"

void ASTUGameModeBase::BeginPlay() {
    int32 variable = 0;
    if (variable < 10) {
        for (int32 i = 0; i < 10; ++i) {
            UE_LOG(LogTemp, Display, TEXT("index: %i"), i);
        }
    }
}