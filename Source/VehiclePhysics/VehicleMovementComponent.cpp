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

// Sum of normals from raycasts of wheels
FVector UVehicleMovementComponent::GetHitNormalSum()
{
	FVector NormalSum;
	// Add vectors together
	for (auto w : VehicleWheels)
	{
		NormalSum += w->Hit.ImpactNormal;
	}
	// Normalise vectors
	NormalSum.Normalize();
	return NormalSum;
}

// Sum of vectors from raycasts of wheels
FVector UVehicleMovementComponent::GetWheelLineTraceVectorSum()
{
	FVector WheelLineTraceVector;
	// Add vectors together
	for (auto w : VehicleWheels)
	{
		WheelLineTraceVector += w->Hit.TraceEnd;
	}
	// Normalise vectors
	WheelLineTraceVector.Normalize();
	return WheelLineTraceVector;

	return WheelLineTraceVector;
}

void UVehicleMovementComponent::Accelerate(float Throttle)
{
	// Use wheel impact details to find vehicle's forward direction
	// Find cross product of line trace vector and normal vector (return vector perpendicular to both)
	auto HitCrossProduct = FVector::CrossProduct(GetHitNormalSum(), GetWheelLineTraceVectorSum());
	// Find cross prod of last cross product and normal vector to get forward vector
	auto TripleCrossProduct = FVector::CrossProduct(GetHitNormalSum(), HitCrossProduct);
	// Add accelerating/braking force to lower position than centre of mass, towards front of vehicle
	VehicleMesh->AddForceAtLocation(TripleCrossProduct * Throttle * 10, VehicleMesh->GetCenterOfMass());
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
