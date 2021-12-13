// Shoot Them Up Game. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUWeaponComponent.generated.h"

class ASTUBaseWeapon;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTTHEMUP_API USTUWeaponComponent : public UActorComponent {
    GENERATED_BODY()

  public:
    USTUWeaponComponent();

    void StartFire();
    void StopFire();
    void NextWeapon();

  protected:
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    TArray<TSubclassOf<ASTUBaseWeapon>> WeaponClasses;

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponEquipSocketName = "WeaponSocket";

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponArmorySocketName = "ArmorySocket";

  private:
    void SpawnWeapons();
    void AttachWeaponToSocket(ASTUBaseWeapon* weapon,
                              USceneComponent* scene_component,
                              const FName& socket_name);
    void EquipWeapon(int32 weapon_index);

    UPROPERTY();
    ASTUBaseWeapon* current_weapon_ = nullptr;

    UPROPERTY();
    TArray<ASTUBaseWeapon*> weapons_;

    int32 current_weapon_index_ = 0;
};
