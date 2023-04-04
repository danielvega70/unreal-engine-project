#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.h"
#include "MyCharacter.h"

AMyCharacter::AMyCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    // Create a default weapon for the character
    DefaultWeapon = CreateDefaultSubobject<UWeapon>(TEXT("DefaultWeapon"));
}

void AMyCharacter::BeginPlay()
{
    Super::BeginPlay();

    // Attach the default weapon to the character's hand socket
    if (DefaultWeapon != nullptr)
    {
        DefaultWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("hand_r"));
    }
}

void AMyCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AMyCharacter::EquipWeapon(UWeapon* NewWeapon)
{
    // Detach the current weapon, if any
    if (CurrentWeapon != nullptr)
    {
        CurrentWeapon->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
    }

    // Attach the new weapon to the character's hand socket
    if (NewWeapon != nullptr)
    {
        NewWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("hand_r"));
    }

    // Set the new weapon as the current weapon
    CurrentWeapon = NewWeapon;
}

void AMyCharacter::FireWeapon()
{
    if (CurrentWeapon != nullptr)
    {
        CurrentWeapon->Fire();
    }
}
