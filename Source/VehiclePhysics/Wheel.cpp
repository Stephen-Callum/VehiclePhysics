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

	//Suspension();
}

void UWheel::Suspension()
{
	// Raycast to the ground
	// Hit contains information about what the raycast hit

	// Raycast origin
	FVector StartLocation = GetComponentLocation();

	// Raycast end location (SuspensionHeight = Length of ray)
	TraceEndLocation = StartLocation + (GetUpVector() * -1 * SuspensionHeight);

	// Collion parameters
	FCollisionQueryParams CollisionParameters;
	CollisionParameters.AddIgnoredActor(GetOwner());

	// Perform line trace
	// EcollisionChannel used in order to determine what we are looking for from the raycast
	GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, TraceEndLocation, ECollisionChannel::ECC_WorldDynamic, CollisionParameters);
	
	// Draw debug line
	DrawDebugLine(GetWorld(), StartLocation, TraceEndLocation, FColor::Green, true, -1, 0, 3.f);

	// If line trace hits
	if (Hit.bBlockingHit)
	{
		// Set compression delta
		SpringCompressionDelta = SuspensionHeight - Hit.Distance;
		SpringCompressionRatio = SpringCompressionDelta / SuspensionHeight;
		// Calculate upwards force (F=kx)
		float Force = SpringCoefficient * SpringCompressionDelta;

		// Calculate Dampening d
		float Dampening = ((SpringCompressionDelta - PreviousCompressionDelta) / GetWorld()->DeltaTimeSeconds) * DampingCoefficient;

		float SpringForce = Force + Dampening;

		//UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("WorldDeltaTime: %f Dampening: %f SpringForce: %f"), GetWorld()->DeltaTimeSeconds, Dampening, SpringForce), true, true, FLinearColor(0.0f, 0.6f, 1.0f, 1.0f));
		
		// ApplyForceAtLocation(F+d, componentlocation);
		VehicleMovementRef->VehicleMesh->AddForceAtLocation(GetUpVector() * SpringForce, GetComponentLocation());
	}

	PreviousCompressionDelta = SpringCompressionDelta;
}

