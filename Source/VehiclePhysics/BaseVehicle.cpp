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
	VehicleMesh->SetMassOverrideInKg("NAME_None", 1000.0f, true);
	VehicleMesh->SetCenterOfMass(FVector(0, 0, -40));
	RootComponent = VehicleMesh;

	// Create spring arm and camera, attach spring arm to root and camera to spring arm
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->AttachToComponent(SpringArm, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false));

	// Add vehicle movement component
	VehicleMovement = CreateDefaultSubobject<UVehicleMovementComponent>(TEXT("VehicleMovementComponent"));
	VehicleMovement->SetVehicleMesh(VehicleMesh);

	// Create and add WheelPoint to mesh
	Wheel1 = CreateDefaultSubobject<UWheel>(TEXT("Wheel1"));
	Wheel2 = CreateDefaultSubobject<UWheel>(TEXT("Wheel2"));
	Wheel3 = CreateDefaultSubobject<UWheel>(TEXT("Wheel3"));
	Wheel4 = CreateDefaultSubobject<UWheel>(TEXT("Wheel4"));

	Wheel1->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
	Wheel2->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
	Wheel3->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
	Wheel4->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));

	Wheel1->VehicleMovementRef = VehicleMovement;
	Wheel2->VehicleMovementRef = VehicleMovement;
	Wheel3->VehicleMovementRef = VehicleMovement;
	Wheel4->VehicleMovementRef = VehicleMovement;

	// Create wheel array
	VehicleWheelArray.Emplace(Wheel1);
	VehicleWheelArray.Emplace(Wheel2);
	VehicleWheelArray.Emplace(Wheel3);
	VehicleWheelArray.Emplace(Wheel4);

	// Give reference for wheels to VehicleMovementComponent
	VehicleMovement->SetVehicleWheels(VehicleWheelArray);
}

// Called when the game starts or when spawned
void ABaseVehicle::BeginPlay()
{
	Super::BeginPlay();

	if (Wheel1 && Wheel2 && Wheel3 && Wheel4)
	{
		SetWheelProperties();
	}
}

// Called every frame
void ABaseVehicle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AccelerateBrake(Throttle);
}

// REFACTOR
void ABaseVehicle::SetWheelProperties()
{
	// Set Wheel Suspension
	Wheel1->SuspensionHeight = SuspensionHeight;
	Wheel2->SuspensionHeight = SuspensionHeight;
	Wheel3->SuspensionHeight = SuspensionHeight;
	Wheel4->SuspensionHeight = SuspensionHeight;

	// Set Suspension Spring Coefficient
	Wheel1->SpringCoefficient = SpringCoefficient;
	Wheel2->SpringCoefficient = SpringCoefficient;
	Wheel3->SpringCoefficient = SpringCoefficient;
	Wheel4->SpringCoefficient = SpringCoefficient;

	// Set Dampening Coefficient
	Wheel1->DampeningCoefficient = DampeningCoefficient;
	Wheel2->DampeningCoefficient = DampeningCoefficient;
	Wheel3->DampeningCoefficient = DampeningCoefficient;
	Wheel4->DampeningCoefficient = DampeningCoefficient;
}

// Called to bind functionality to input
void ABaseVehicle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("ForceUp", IE_Pressed, this, &ABaseVehicle::ApplyUpwardImpulse);

	PlayerInputComponent->BindAxis("AccelerateBrake", this, &ABaseVehicle::AccelerateBrake);
}

void ABaseVehicle::AccelerateBrake(float Value)
{
	Throttle = Value;
	if (Value != 0 && VehicleMovement)
	{
		UKismetSystemLibrary::PrintString(this, "Base Vehicle Throttle pressed", true, true, FLinearColor(0.0f, 0.6f, 1.0f, 1.0f));

		VehicleMovement->Accelerate(Value);
	}
}

void ABaseVehicle::ApplyUpwardImpulse()
{
	if (VehicleMovement)
	{
		VehicleMovement->AddUpwardImpulse();
	}
	else
	{
		UKismetSystemLibrary::PrintString(this, "Base Vehicle cannot access function", true, true, FLinearColor(0.0f, 0.6f, 1.0f, 1.0f));
	}
}