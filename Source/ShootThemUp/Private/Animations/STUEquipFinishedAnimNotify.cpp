// Shoot Them Up Game. All Right Reserved.

#include "Animations/STUEquipFinishedAnimNotify.h"

void USTUEquipFinishedAnimNotify::Notify(USkeletalMeshComponent* MeshComp,
                                         UAnimSequenceBase* Animation) {
    OnNotified.Broadcast(MeshComp);
    Super::Notify(MeshComp, Animation);
}