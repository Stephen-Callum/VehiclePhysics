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
	VehicleMovementComp = CreateDefaultSubobject<UVehicleMovementComponent>(TEXT("VehicleMovementComponent"));
	VehicleMovementComp->SetVehicleMesh(VehicleMesh);

	// Create and add WheelPoint to mesh
	Wheel1 = CreateDefaultSubobject<UWheel>(TEXT("Wheel1"));
	Wheel2 = CreateDefaultSubobject<UWheel>(TEXT("Wheel2"));
	Wheel3 = CreateDefaultSubobject<UWheel>(TEXT("Wheel3"));
	Wheel4 = CreateDefaultSubobject<UWheel>(TEXT("Wheel4"));

	Wheel1->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
	Wheel2->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
	Wheel3->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
	Wheel4->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));

	// Set Wheel Suspension
	Wheel1->SuspensionHeight = SuspensionHeight;
	Wheel2->SuspensionHeight = SuspensionHeight;
	Wheel3->SuspensionHeight = SuspensionHeight;
	Wheel4->SuspensionHeight = SuspensionHeight;
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

}

// Called to bind functionality to input
void ABaseVehicle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("ForceUp", IE_Pressed, this, &ABaseVehicle::ApplyUpwardImpulse);
}

void ABaseVehicle::ApplyUpwardImpulse()
{
	if (VehicleMovementComp)
	{
		VehicleMovementComp->AddUpwardImpulse();
	}
	else
	{
		UKismetSystemLibrary::PrintString(this, "Base Vehicle cannot access function", true, true, FLinearColor(0.0f, 0.6f, 1.0f, 1.0f));
	}
}