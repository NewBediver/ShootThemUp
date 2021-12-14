// Shoot Them Up Game. All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUCoreTypes.h"
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
    void Reload();

  protected:
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    TArray<FWeaponData> WeaponData;

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponEquipSocketName = "WeaponSocket";

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponArmorySocketName = "ArmorySocket";

    UPROPERTY(EditDefaultsOnly, Category = "Animation")
    UAnimMontage* EquipAnimMontage = nullptr;

  private:
    void SpawnWeapons();
    void AttachWeaponToSocket(ASTUBaseWeapon* weapon, USceneComponent* scene_component,
                              const FName& socket_name);
    void EquipWeapon(int32 weapon_index);

    void PlayAnimMontage(UAnimMontage* animation);
    void InitAnimations();

    void OnEquipFinished(USkeletalMeshComponent* mesh);
    void OnReloadFinished(USkeletalMeshComponent* mesh);

    bool CanFire() const;
    bool CanEquip() const;
    bool CanReload() const;

    void OnEmptyClip();
    void ChangeClip();

    UPROPERTY();
    ASTUBaseWeapon* current_weapon_ = nullptr;

    UPROPERTY();
    TArray<ASTUBaseWeapon*> weapons_;

    UPROPERTY();
    UAnimMontage* current_reload_anim_montage_ = nullptr;

    int32 current_weapon_index_ = 0;

    bool equip_anim_in_progress_ = false;
    bool reload_anim_in_progress_ = false;
};
