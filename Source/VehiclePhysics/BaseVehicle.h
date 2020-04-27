// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "VehiclePhysics/VehicleMovementComponent.h"
#include "VehiclePhysics/Wheel.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "BaseVehicle.generated.h"

UCLASS()
class VEHICLEPHYSICS_API ABaseVehicle : public APawn
{
	GENERATED_BODY()
public:
	// Sets default values for this pawn's properties
	ABaseVehicle();
	UActorComponent* Actor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* VehicleMesh;

	UPROPERTY(EditAnywhere, Category = "VehicleCamera")
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, Category = "VehicleCamera")
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VehicleWheel")
	UWheel* Wheel1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VehicleWheel")
	UWheel* Wheel2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VehicleWheel")
	UWheel* Wheel3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VehicleWheel")
	UWheel* Wheel4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WheelSuspension")
	float SuspensionHeight;

	UPROPERTY(EditAnywhere, Category = "WheelSuspension")
	float SpringCoefficient;
	
	UPROPERTY(EditAnywhere, Category = "WheelSuspension")
	float DampingCoefficient;

	UPROPERTY(BlueprintReadOnly)
	TArray<UWheel*> VehicleWheelArr;

	UPROPERTY(EditAnywhere, Category = "Steering")
	float LinearDamping;
	
	UPROPERTY(EditAnywhere, Category = "Steering")
	float AngularDamping;

	UPROPERTY(EditAnywhere, Category = "CarEngine")
	float HorsePower;

	UPROPERTY(EditAnywhere, Category = "Steering")
	float SteeringPower;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UVehicleMovementComponent* VehicleMoveComp;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	void SetWheelProperties();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void ApplyUpwardImpulse();

	UFUNCTION()
	void AccelerateBrake(float Value);

	UFUNCTION()
	void TurnRight(float Value);
};
