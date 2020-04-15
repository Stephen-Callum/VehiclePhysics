// Fill out your copyright notice in the Description page of Project Settings.


#include "Wheel.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
UWheel::UWheel()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	
}


// Called when the game starts
void UWheel::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UWheel::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Suspension();
}

void UWheel::Suspension()
{
	// Raycast to the ground
	// Hit contains information about what the raycast hit
	FHitResult Hit;

	// The length of the ray in units.
	float RayLength = SuspensionHeight;

	// Raycast origin
	FVector StartLocation = GetComponentLocation();

	// Raycast end location
	FVector EndLocation = StartLocation + (GetUpVector() * -1 * RayLength);

	// Collion parameters
	FCollisionQueryParams CollisionParameters;
	CollisionParameters.AddIgnoredActor(GetOwner());

	// Perform line trace
	// EcollisionChannel used in order to determine what we are looking for from the raycast
	GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, EndLocation, ECollisionChannel::ECC_WorldDynamic, CollisionParameters);

	// Draw debug line
	DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Green, true, -1, 0, 1.f);

	// If DistanceToGround <= SuspensionHeight
	float CompressionAmount = SuspensionHeight - Hit.Distance;

	if (!Hit.bBlockingHit)
	{
		CompressionAmount = 0;
	}
	
	float CompressionRatio = CompressionAmount / SuspensionHeight;

	auto VehicleMesh = VehicleMovementComponent->GetVehicleMesh();

	FVector Force = GetUpVector() * -1 * CompressionRatio * VehicleMesh->GetMass() * 100;

	VehicleMesh->AddForceAtLocation(Force, GetComponentLocation());

	UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("DistanceToGround: %f SuspensionHeight: %f"), CompressionAmount, SuspensionHeight), true, true, FLinearColor(0.0f, 0.6f, 1.0f, 1.0f));

		// ApplyForce Upwards (direction of raycast)
}

