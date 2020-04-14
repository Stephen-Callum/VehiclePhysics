// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/MovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "VehicleMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class VEHICLEPHYSICS_API UVehicleMovementComponent : public UMovementComponent
{
	GENERATED_BODY()

		UVehicleMovementComponent();
public:
	UStaticMeshComponent* VehicleMesh;

public:

	UFUNCTION()
	void SetVehicleMesh(UStaticMeshComponent * VehicleMeshRef);

	UFUNCTION()
	UStaticMeshComponent* GetVehicleMesh();

	UFUNCTION()
	void AddUpwardImpulse();
};
