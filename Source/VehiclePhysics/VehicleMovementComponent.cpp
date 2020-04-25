// Fill out your copyright notice in the Description page of Project Settings.


#include "VehicleMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "VehiclePhysics/Wheel.h"
#include "Math/Vector.h"
#include "DrawDebugHelpers.h"

UVehicleMovementComponent::UVehicleMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	HorsePower = 10;
}

void UVehicleMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	for (UWheel* w : VehicleWheels)
	{
		w->Suspension();
	}
}
// Apply upward force from below vehicle mesh
void UVehicleMovementComponent::AddUpwardImpulse()
{
	if (VehicleMesh)
	{
		UKismetSystemLibrary::PrintString(this, "Adding upward Impulse", true, true, FLinearColor(0.0f, 0.6f, 1.0f, 1.0f));
		VehicleMesh->AddImpulseAtLocation(FVector(0, 0, 500000), FVector(0, 0, -70) + VehicleMesh->GetComponentLocation());
	}
	else
	{
		UKismetSystemLibrary::PrintString(this, "VehicleMovementComponent::VehicleMesh NOT VALID", true, true, FLinearColor(0.0f, 0.6f, 1.0f, 1.0f));
	}
}

// Avg of normals from raycasts of wheels
FVector UVehicleMovementComponent::GetAvgSurfaceNormal()
{
	FVector NormalAvg;
	// Add vectors together
	for (auto w : VehicleWheels)
	{
		NormalAvg += w->Hit.ImpactNormal;
	}
	// Normalise vectors
	NormalAvg = NormalAvg / 4;
	NormalAvg.Normalize();
	return NormalAvg;
}

// Avg of Surface impact points of wheels
FVector UVehicleMovementComponent::GetSurfaceImpactPointAvg()
{
	FVector ImpactPointAvg;
	// Add vectors together
	for (auto w : VehicleWheels)
	{
		ImpactPointAvg += w->Hit.ImpactPoint;
	}
	// Normalise vectors
	ImpactPointAvg = ImpactPointAvg / 4;
	return ImpactPointAvg;
}

int UVehicleMovementComponent::WheelsGrounded()
{
	int WheelCount = 0;
	for (auto w : VehicleWheels)
	{
		WheelCount += w->Hit.bBlockingHit;
	}

	return WheelCount;
}

void UVehicleMovementComponent::Accelerate(float Throttle)
{
	auto AcceleratingPower = VehicleMesh->GetMass() * Throttle * HorsePower;
	auto FowardForce = VehicleMesh->GetForwardVector() * AcceleratingPower;
	UKismetSystemLibrary::PrintString(this, "Accelerating", true, true, FLinearColor(0.0f, 0.6f, 1.0f, 1.0f));

	VehicleMesh->AddForce(FowardForce, "NAME_None", true);
}

void UVehicleMovementComponent::BrakeReverse()
{
}

void UVehicleMovementComponent::Turn()
{
	// Apply torque on Z axis of vehicle
}

// Set VehicleWheels array (called from BaseVehicle)
void UVehicleMovementComponent::SetVehicleWheels(TArray<UWheel*> Wheels)
{
	VehicleWheels = Wheels;
}

// Set the reference to the BaseVehicle mesh
void UVehicleMovementComponent::SetVehicleMesh(UStaticMeshComponent* VehicleMeshRef)
{
	if (VehicleMeshRef)
	{
		VehicleMesh = VehicleMeshRef;
	}
}

// Get reference to base vehicle
UStaticMeshComponent* UVehicleMovementComponent::GetVehicleMesh()
{
	return VehicleMesh;
}
