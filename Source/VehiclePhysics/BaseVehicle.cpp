// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseVehicle.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ABaseVehicle::ABaseVehicle()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VehicleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VehicleMesh"));
	VehicleMesh->SetSimulatePhysics(true);
	RootComponent = VehicleMesh;

	// Create spring arm and camera, attach spring arm to root and camera to spring arm
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->AttachToComponent(SpringArm, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false));

	// Add vehicle movement component
	VehicleMovementComponent = CreateDefaultSubobject<UVehicleMovementComponent>(TEXT("VehicleMovementComponent"));
	VehicleMovementComponent->SetVehicleMesh(VehicleMesh);

	// Create and add WheelPoint to mesh
	Wheel01 = CreateDefaultSubobject<UWheel>(TEXT("Wheel1"));
	Wheel02 = CreateDefaultSubobject<UWheel>(TEXT("Wheel2"));
	Wheel03 = CreateDefaultSubobject<UWheel>(TEXT("Wheel3"));
	Wheel04 = CreateDefaultSubobject<UWheel>(TEXT("Wheel4"));

	Wheel01->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
	Wheel02->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
	Wheel03->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
	Wheel04->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));

}

// Called when the game starts or when spawned
void ABaseVehicle::BeginPlay()
{
	Super::BeginPlay();
	
	

}

// Called every frame
void ABaseVehicle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Wheel01 && Wheel02 && Wheel03 && Wheel04)
	{
		SetSuspensionHeight();

	}
}

void ABaseVehicle::SetSuspensionHeight()
{
	// Set Wheel Suspension
	Wheel01->SuspensionHeight = SuspensionHeight;
	Wheel02->SuspensionHeight = SuspensionHeight;
	Wheel03->SuspensionHeight = SuspensionHeight;
	Wheel04->SuspensionHeight = SuspensionHeight;
}

// Called to bind functionality to input
void ABaseVehicle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("ForceUp", IE_Pressed, this, &ABaseVehicle::ApplyUpwardImpulse);
}

void ABaseVehicle::ApplyUpwardImpulse()
{
	if (VehicleMovementComponent)
	{
		VehicleMovementComponent->AddUpwardImpulse();
	}
	else
	{
		UKismetSystemLibrary::PrintString(this, "Base Vehicle cannot access function", true, true, FLinearColor(0.0f, 0.6f, 1.0f, 1.0f));
	}
}