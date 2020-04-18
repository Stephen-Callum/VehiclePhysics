// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/MovementComponent.h"
#include "VehicleMovementComponent.generated.h"

/**
 * 
 */
class UWheel;
UCLASS()
class VEHICLEPHYSICS_API UVehicleMovementComponent : public UActorComponent
{
	GENERATED_BODY()

		UVehicleMovementComponent();
public:
	UStaticMeshComponent* VehicleMesh;

	TArray<UWheel*> VehicleWheels;

public:

	UFUNCTION()
	void SetVehicleMesh(UStaticMeshComponent * VehicleMeshRef);

	UFUNCTION()
	UStaticMeshComponent* GetVehicleMesh();

	UFUNCTION()
	void AddUpwardImpulse();

	UFUNCTION()
	void Accelerate(float Throttle);

	UFUNCTION()
	void BrakeReverse();

	UFUNCTION()
	void Turn();

	UFUNCTION()
	void SetVehicleWheels(TArray<UWheel*> Wheels);

	UFUNCTION()
	FVector GetHitNormalSum();

	UFUNCTION()
	FVector GetWheelLineTraceVectorSum();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
