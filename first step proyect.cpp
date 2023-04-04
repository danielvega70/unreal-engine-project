#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "BatteryMan.generated.h"

UCLASS()
class BATTERYCOLLECTOR_API ABatteryMan : public ACharacter
{
    GENERATED_BODY()

public:
    ABatteryMan();

    // Declare camera components
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
    USpringArmComponent* SpringArm;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
    UCameraComponent* FollowCamera;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
    UStaticMeshComponent* Mesh1P;

    // Declare sphere component for collecting batteries
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Battery)
    USphereComponent* CollectionSphere;

protected:
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
    // Declare turn rates for input
    float BaseTurnRate;
    float BaseLookUpRate;
};
