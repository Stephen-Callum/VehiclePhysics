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

void UVehicleMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void UVehicleMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	for (UWheel* w : VehicleWheelArr)
	{
		w->Suspension();
	}
	VehicleMesh->SetLinearDamping(LinearDamping);
	VehicleMesh->SetAngularDamping(AngularDamping);
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

void UVehicleMovementComponent::SetDampingForces(float _LinearDamping, float _AngularDamping)
{
	LinearDamping = _LinearDamping;
	AngularDamping = _AngularDamping;
}

int UVehicleMovementComponent::WheelsGrounded()
{
	int WheelCount = 0;
	for (UWheel* w : VehicleWheelArr)
	{
		WheelCount += w->Hit.bBlockingHit;
	}

	return WheelCount;
}

// Acceleration/Braking and reversing
void UVehicleMovementComponent::Accelerate(float _Throttle)
{
	Throttle = _Throttle;
	auto AcceleratingPower = VehicleMesh->GetMass() * Throttle * HorsePower;
	ForwardForce = VehicleMesh->GetRightVector() * AcceleratingPower;

	VehicleMesh->AddForceAtLocation(ForwardForce, AccelerationPoint->GetComponentLocation(),"NAME_None");
	//VehicleMesh->SetPhysicsLinearVelocity(ForwardForce, true);
}

void UVehicleMovementComponent::Turn(float SteeringDirection)
{
	//SteeringPower += ForwardForce.X;
	
	VehicleMesh->AddTorqueInDegrees(VehicleMesh->GetUpVector() * SteeringPower * SteeringDirection, "NAME_None", true);
}

// Set VehicleWheels array (called from BaseVehicle)
void UVehicleMovementComponent::SetVehicleWheels(TArray<UWheel*> Wheels)
{
	VehicleWheelArr = Wheels;
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
