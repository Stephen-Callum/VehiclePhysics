// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseVehicle.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ABaseVehicle::ABaseVehicle()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	SetRootComponent(BoxCollider);
	VehicleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VehicleMesh"));
	VehicleMesh->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::KeepWorld, false));
	VehicleMesh->SetSimulatePhysics(true);
	//VehicleMesh->SetCenterOfMass(FVector(0, 0, -40));

	// Create spring arm and camera, attach spring arm to root and camera to spring arm
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->AttachToComponent(SpringArm, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, EAttachmentRule::KeepWorld, false));

	// Create point of acceleration for vehicle
	AccelerationPoint = CreateDefaultSubobject<USceneComponent>(TEXT("AccelerationPoint"));
	AccelerationPoint->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));

	// Add vehicle movement component
	VehicleMoveComponent = CreateDefaultSubobject<UVehicleMovementComponent>(TEXT("VehicleMovementComponent"));
	VehicleMoveComponent->SetVehicleMesh(VehicleMesh);

	// Create and add Wheels to mesh
	Wheel1 = CreateDefaultSubobject<UWheel>(TEXT("Wheel1"));
	Wheel2 = CreateDefaultSubobject<UWheel>(TEXT("Wheel2"));
	Wheel3 = CreateDefaultSubobject<UWheel>(TEXT("Wheel3"));
	Wheel4 = CreateDefaultSubobject<UWheel>(TEXT("Wheel4"));

	Wheel1->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
	Wheel2->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
	Wheel3->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
	Wheel4->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));

	Wheel1->VehicleMovementComp = VehicleMoveComponent;
	Wheel2->VehicleMovementComp = VehicleMoveComponent;
	Wheel3->VehicleMovementComp = VehicleMoveComponent;
	Wheel4->VehicleMovementComp = VehicleMoveComponent;

	// Create wheel array
	VehicleWheelArr.Emplace(Wheel1);
	VehicleWheelArr.Emplace(Wheel2);
	VehicleWheelArr.Emplace(Wheel3);
	VehicleWheelArr.Emplace(Wheel4);

	// Give reference for wheels to VehicleMovementComponent
	VehicleMoveComponent->SetVehicleWheels(VehicleWheelArr);
	VehicleMoveComponent->AccelerationPoint = AccelerationPoint;
}

// Called when the game starts or when spawned
void ABaseVehicle::BeginPlay()
{
	Super::BeginPlay();

	// Set suspension properties
	SetWheelProperties();
	/*VehicleMesh->SetLinearDamping(LinearDamping);
	VehicleMesh->SetAngularDamping(AngularDamping);*/
	VehicleMesh->SetMassOverrideInKg("NAME_None", 1500.0f, true);

	// Set Vehicle Engine/Steering Properties
	VehicleMoveComponent->HorsePower = HorsePower;
	VehicleMoveComponent->SteeringPower = SteeringPower;
	VehicleMoveComponent->SetDampingForces(LinearDamping, AngularDamping);
}

// Called every frame
void ABaseVehicle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseVehicle::SetWheelProperties()
{
	for (auto w : VehicleWheelArr)
	{
		w->SuspensionHeight = SuspensionHeight;
		w->SpringCoefficient = SpringCoefficient;
		w->DampingCoefficient = DampingCoefficient;
	}
}

// Called to bind functionality to input
void ABaseVehicle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("ForceUp", IE_Pressed, this, &ABaseVehicle::ApplyUpwardImpulse);

	PlayerInputComponent->BindAxis("AccelerateBrake", this, &ABaseVehicle::AccelerateBrake);
	PlayerInputComponent->BindAxis("TurnRight", this, &ABaseVehicle::TurnRight);
}

void ABaseVehicle::AccelerateBrake(float Value)
{
	if (VehicleMoveComponent->WheelsGrounded() == 4)
	{
		//UKismetSystemLibrary::PrintString(this, "Vehicle is Grounded", true, true, FLinearColor(0.0f, 0.6f, 1.0f, 1.0f));
		VehicleMoveComponent->Accelerate(Value);
	}
}

void ABaseVehicle::TurnRight(float Value)
{
	//UKismetSystemLibrary::PrintString(this, "Turning Button pressed", true, true, FLinearColor(0.0f, 0.6f, 1.0f, 1.0f));
	VehicleMoveComponent->Turn(Value);
}

void ABaseVehicle::ApplyUpwardImpulse()
{
	if (VehicleMoveComponent)
	{
		VehicleMoveComponent->AddUpwardImpulse();
	}
	else
	{
		UKismetSystemLibrary::PrintString(this, "Base Vehicle cannot access function", true, true, FLinearColor(0.0f, 0.6f, 1.0f, 1.0f));
	}
}