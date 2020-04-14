// Fill out your copyright notice in the Description page of Project Settings.


#include "VehicleMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DrawDebugHelpers.h"

UVehicleMovementComponent::UVehicleMovementComponent()
{

}

void UVehicleMovementComponent::AddUpwardImpulse()
{
	if (VehicleMesh)
	{
		UKismetSystemLibrary::PrintString(this, "Adding upward Impulse", true, true, FLinearColor(0.0f, 0.6f, 1.0f, 1.0f));
		VehicleMesh->AddImpulseAtLocation(FVector(0, 0, 500 * VehicleMesh->GetMass()), FVector(0, 0, -70) + VehicleMesh->GetComponentLocation());
	}
	else
	{
		UKismetSystemLibrary::PrintString(this, "VehicleMovementComponent::VehicleMesh NOT VALID", true, true, FLinearColor(0.0f, 0.6f, 1.0f, 1.0f));
	}
}

void UVehicleMovementComponent::SetVehicleMesh(UStaticMeshComponent* VehicleMeshRef)
{
	if (VehicleMeshRef)
	{
		VehicleMesh = VehicleMeshRef;
	}
}

UStaticMeshComponent* UVehicleMovementComponent::GetVehicleMesh()
{
	return VehicleMesh;
}
