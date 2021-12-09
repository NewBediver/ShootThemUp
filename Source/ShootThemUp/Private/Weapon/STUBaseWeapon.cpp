// Shoot Them Up Game. All Right Reserved.

#include "Weapon/STUBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All);

ASTUBaseWeapon::ASTUBaseWeapon() {
    PrimaryActorTick.bCanEverTick = false;

    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
    SetRootComponent(WeaponMesh);
}

void ASTUBaseWeapon::Fire() {
    UE_LOG(LogBaseWeapon, Display, TEXT("Fire!"));
    MakeShot();
}

void ASTUBaseWeapon::BeginPlay() {
    Super::BeginPlay();

    check(WeaponMesh);
}

void ASTUBaseWeapon::MakeShot() {
    if (GetWorld() == nullptr) {
        return;
    }

    const auto player = Cast<ACharacter>(GetOwner());
    if (player == nullptr) {
        return;
    }

    const auto controller = player->GetController<APlayerController>();
    if (controller == nullptr) {
        return;
    }

    FVector view_location;
    FRotator view_rotation;
    controller->GetPlayerViewPoint(view_location, view_rotation);

    const auto socket_transform = WeaponMesh->GetSocketTransform(muzzle_socket_name_);
    const auto trace_start = view_location;
    const auto shoot_direction = view_rotation.Vector();
    const auto trace_end = trace_start + shoot_direction * trace_max_distance_;
    

    FCollisionQueryParams collision_params;
    collision_params.AddIgnoredActor(player);

    FHitResult hit_result;
    GetWorld()->LineTraceSingleByChannel(hit_result, trace_start, trace_end,
                                         ECollisionChannel::ECC_Visibility, collision_params);

    if (hit_result.bBlockingHit &&
        FVector::DotProduct(hit_result.ImpactPoint - socket_transform.GetLocation(), trace_end - socket_transform.GetLocation()) > 0.0f) {
        DrawDebugLine(GetWorld(), socket_transform.GetLocation(), hit_result.ImpactPoint, FColor::Red, false, 3.0f, 0, 3.0f);
        DrawDebugSphere(GetWorld(), hit_result.ImpactPoint, 10.0f, 24, FColor::Yellow, false, 5.0f);

        UE_LOG(LogBaseWeapon, Display, TEXT("Bone: %s"), *hit_result.BoneName.ToString());
    } else {
        DrawDebugLine(GetWorld(), socket_transform.GetLocation(), trace_end, FColor::Red, false, 3.0f, 0, 3.0f);
    }
}