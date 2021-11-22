// Shoot Them Up Game. All Right Reserved.


#include "Components/STUCharacterMovementComponent.h"
#include "Player/STUBaseCharacter.h"


float USTUCharacterMovementComponent::GetMaxSpeed() const {
    const auto max_speed = Super::GetMaxSpeed();
    const auto player = Cast<ASTUBaseCharacter>(GetPawnOwner());
    return player != nullptr && player->IsRunning() ?
           max_speed * run_modifier :
           max_speed;
}
