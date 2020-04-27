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

	TArray<UWheel*> VehicleWheelArr;

	float HorsePower;

	float SteeringPower;

	UPROPERTY(EditAnywhere, Category = "Turning Forces")
	float LinearDamping;

	UPROPERTY(EditAnywhere, Category = "Turning Forces")
	float AngularDamping;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UFUNCTION()
	void SetVehicleMesh(UStaticMeshComponent * VehicleMeshRef);

	UFUNCTION()
	UStaticMeshComponent* GetVehicleMesh();

	UFUNCTION()
	void AddUpwardImpulse();

	UFUNCTION(BlueprintCallable)
	void Accelerate(float Throttle);

	UFUNCTION()
	void Turn(float SteeringDirection);

	UFUNCTION()
	void SetVehicleWheels(TArray<UWheel*> Wheels);

	UFUNCTION(BlueprintCallable)
	int WheelsGrounded();

	UFUNCTION()
	void SetDampingForces(float _LinearDamping, float _AngularDamping);

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
