// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "VehiclePhysics/VehicleMovementComponent.h"
#include "Engine/EngineTypes.h"
#include "Wheel.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VEHICLEPHYSICS_API UWheel : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWheel();

	UVehicleMovementComponent* VehicleMovementComp;

	float SuspensionHeight;

	float SpringCompressionDelta;

	float PreviousCompressionDelta = 0;

	float SpringCoefficient;

	float DampingCoefficient;

	float SpringCompressionRatio;

	UPROPERTY(BlueprintReadWrite, Category = "HitResult")
	FHitResult Hit;

	FVector TraceEndLocation;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void Suspension();
};
