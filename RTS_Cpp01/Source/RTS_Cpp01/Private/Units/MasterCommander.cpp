// Fill out your copyright notice in the Description page of Project Settings.

#include "MasterCommander.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Engine/StaticMesh.h"

// Sets default values
AMasterCommander::AMasterCommander()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InvisibleObject = CreateDefaultSubobject<UStaticMeshComponent>(FName("Invisible Object"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(FName("Spring Arm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(FName("Camera"));

	RootComponent = InvisibleObject;
	
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->RelativeRotation = FRotator(-80.0f, 0.0f, 0.0f);
	SpringArm->bDoCollisionTest = false;
	SpringArm->TargetArmLength = 2000.0f;

	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	InvisibleObject->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	InvisibleObject->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Block);

}

// Called when the game starts or when spawned
void AMasterCommander::BeginPlay()
{
	Super::BeginPlay();

	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		APlayerController* PlayerController = Cast<APlayerController>(*Iterator);

		if (PlayerController)
		{
			PlayerController->bShowMouseCursor = true;
		}

	}
}

// Called every frame
void AMasterCommander::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMasterCommander::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Assertion check
	check(PlayerInputComponent);

	// Camera movement input
	PlayerInputComponent->BindAxis("MoveForward", this, &AMasterCommander::Camera_MoveForwardAndBack);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMasterCommander::Camera_MoveLeftAndRight);
	
	PlayerInputComponent->BindKey(EKeys::MouseScrollUp, IE_Pressed, this, &AMasterCommander::Camera_ZoomIn);
	PlayerInputComponent->BindKey(EKeys::MouseScrollDown, IE_Pressed, this, &AMasterCommander::Camera_ZoomOut);

	// Camera Pan and Rotate
	PlayerInputComponent->BindKey(EKeys::LeftShift, IE_Pressed, this, &AMasterCommander::Camera_TPanFRotateEnable);
	PlayerInputComponent->BindKey(EKeys::LeftShift, IE_Released, this, &AMasterCommander::Camera_TPanFRotateDisable);
	PlayerInputComponent->BindKey(EKeys::MiddleMouseButton, IE_Released, this, &AMasterCommander::Camera_SetHitEnable);
	PlayerInputComponent->BindKey(EKeys::MiddleMouseButton, IE_Pressed, this, &AMasterCommander::Camera_SetHitDisable);
	PlayerInputComponent->BindAxis("PanX", this, &AMasterCommander::Camera_RotateAndPanX);
	
}

void AMasterCommander::Camera_MoveForwardAndBack(float InAxisValueForward)
{
	if (InAxisValueForward != 0.0f)
	{
		float ScalarForward = InAxisValueForward * Camera_MoveSpeed;
		AddActorLocalOffset(FVector(ScalarForward, 0.0f, 0.0f), true);
	}
}

void AMasterCommander::Camera_MoveLeftAndRight(float InAxisValueRight)
{
	if (InAxisValueRight != 0.0f)
	{
		float ScalarRight = InAxisValueRight * Camera_MoveSpeed;
		AddActorLocalOffset(FVector(0.0f, ScalarRight, 0.0f), true);
	}
}

void AMasterCommander::Camera_ZoomIn()
{
	auto CameraLocation = Camera->GetComponentLocation().Z - InvisibleObject->GetComponentLocation().Z;
	auto ClampedValue = FMath::Clamp<float>(CameraLocation, 1000.0f, 3000.0f);
	if (ClampedValue != 1000)
	{
		Camera->AddLocalOffset(FVector(Camera_ZoomSpeed, 0.0f, 0.0f));
	}
}

void AMasterCommander::Camera_ZoomOut()
{
	auto CameraLocation = Camera->GetComponentLocation().Z - InvisibleObject->GetComponentLocation().Z;
	auto ClampedValue = FMath::Clamp<float>(CameraLocation, 1000.0f, 3000.0f);
	if (ClampedValue != 3000)
	{
		Camera->AddLocalOffset(FVector((-Camera_ZoomSpeed), 0.0f, 0.0f));
	}
}

void AMasterCommander::Camera_SetHitEnable()
{
	Camera_ScreenEdgeHitEnable = true;
}

void AMasterCommander::Camera_SetHitDisable()
{
	Camera_ScreenEdgeHitEnable = false;
}

void AMasterCommander::Camera_TPanFRotateEnable()
{
	Camera_TPanFRotate = true;
}

void AMasterCommander::Camera_TPanFRotateDisable()
{
	Camera_TPanFRotate = false;
}

void AMasterCommander::Camera_RotateAndPanX(float InMouseX)
{
	if (Camera_TPanFRotate)
	{
		UE_LOG(LogTemp, Warning, TEXT("Camera_TPanFRotate = TRUE"))
	}
	else
	{
		Camera_RotateX(InMouseX);
	}
}

void AMasterCommander::Camera_RotateX(float InMouseX)
{
	UE_LOG(LogTemp, Warning, TEXT("AMasterCommander::Camera_RotateX: %f"), InMouseX)
}
