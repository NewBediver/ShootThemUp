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

    virtual void StartFire();
    void StopFire();
    virtual void NextWeapon();
    void Reload();

    bool GetWeaponUIData(FWeaponUIData& ui_data) const;
    bool GetAmmoData(FAmmoData& ammo_data) const;

    bool TryToAddAmmo(TSubclassOf<ASTUBaseWeapon> weapon_type, int32 clips_amount);

  protected:
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    bool CanFire() const;
    bool CanEquip() const;
    void EquipWeapon(int32 weapon_index);

    UPROPERTY();
    ASTUBaseWeapon* current_weapon_ = nullptr;

    UPROPERTY();
    TArray<ASTUBaseWeapon*> weapons_;

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    TArray<FWeaponData> WeaponData;

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponEquipSocketName = "WeaponSocket";

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponArmorySocketName = "ArmorySocket";

    UPROPERTY(EditDefaultsOnly, Category = "Animation")
    UAnimMontage* EquipAnimMontage = nullptr;

    int32 current_weapon_index_ = 0;

  private:
    void SpawnWeapons();
    void AttachWeaponToSocket(ASTUBaseWeapon* weapon, USceneComponent* scene_component,
                              const FName& socket_name);

    void PlayAnimMontage(UAnimMontage* animation);
    void InitAnimations();

    void OnEquipFinished(USkeletalMeshComponent* mesh);
    void OnReloadFinished(USkeletalMeshComponent* mesh);

    bool CanReload() const;

    void OnEmptyClip(ASTUBaseWeapon* ammo_empty_weapon);
    void ChangeClip();

    UPROPERTY();
    UAnimMontage* current_reload_anim_montage_ = nullptr;

    bool equip_anim_in_progress_ = false;
    bool reload_anim_in_progress_ = false;
};