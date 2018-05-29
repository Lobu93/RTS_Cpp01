// Fill out your copyright notice in the Description page of Project Settings.

#include "MasterCommander.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Engine/StaticMesh.h"
#include "Engine.h"

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
		// APlayerController* PlayerController = Cast<APlayerController>(*Iterator);

		PlayerController = Cast<APlayerController>(*Iterator);

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
	PlayerInputComponent->BindAxis("MoveForward", this, &AMasterCommander::ROS_MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMasterCommander::ROS_MoveRight);
	
	PlayerInputComponent->BindKey(EKeys::MouseScrollUp, IE_Pressed, this, &AMasterCommander::Camera_ZoomIn);
	PlayerInputComponent->BindKey(EKeys::MouseScrollDown, IE_Pressed, this, &AMasterCommander::Camera_ZoomOut);

	// Camera Pan and Rotate
	PlayerInputComponent->BindKey(EKeys::LeftShift, IE_Pressed, this, &AMasterCommander::Camera_TPanFRotateEnable);
	PlayerInputComponent->BindKey(EKeys::LeftShift, IE_Released, this, &AMasterCommander::Camera_TPanFRotateDisable);
	PlayerInputComponent->BindKey(EKeys::MiddleMouseButton, IE_Released, this, &AMasterCommander::Camera_SetHitEnable);
	PlayerInputComponent->BindKey(EKeys::MiddleMouseButton, IE_Pressed, this, &AMasterCommander::Camera_SetHitDisable);
	PlayerInputComponent->BindAxis("PanX", this, &AMasterCommander::Camera_RotateAndPanX);
	PlayerInputComponent->BindAxis("PanY", this, &AMasterCommander::Camera_RotateAndPanY);

	// Camera Screen Edge Hit
	if (Camera_ScreenEdgeHitEnable)
	{
		PlayerInputComponent->BindAxis("PanX", this, &AMasterCommander::ROS_ScreenEdgeHitRight);
		PlayerInputComponent->BindAxis("PanY", this, &AMasterCommander::ROS_ScreenEdgeHitForward);
	}
}

void AMasterCommander::ROS_MoveForward_Implementation(float InAxisValue)
{
	MC_MoveForward(InAxisValue);
}

bool AMasterCommander::ROS_MoveForward_Validate(float InAxisValue)
{
	return true;
}

void AMasterCommander::MC_MoveForward_Implementation(float InAxisValue)
{
	Camera_MoveForwardAndBack(InAxisValue);
}

bool AMasterCommander::MC_MoveForward_Validate(float InAxisValue)
{
	return true;
}

void AMasterCommander::Camera_MoveForwardAndBack(float InAxisValueForward)
{
	if (InAxisValueForward != 0.0f)
	{
		float ScalarForward = InAxisValueForward * Camera_MoveSpeed;
		AddActorLocalOffset(FVector(ScalarForward, 0.0f, 0.0f), true);
	}
}

// Camera Directional Movements - Left and Right
void AMasterCommander::ROS_MoveRight_Implementation(float InAxisValue)
{
	MC_MoveRight(InAxisValue);
}

bool AMasterCommander::ROS_MoveRight_Validate(float InAxisValue)
{
	return true;
}

void AMasterCommander::MC_MoveRight_Implementation(float InAxisValue)
{
	Camera_MoveLeftAndRight(InAxisValue);
}

bool AMasterCommander::MC_MoveRight_Validate(float InAxisValue)
{
	return true;
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
	if (Camera_TPanFRotate && Camera_ScreenEdgeHitEnable == false)
	{
		ROS_PanRight(InMouseX);
	}
	else if (!Camera_TPanFRotate && Camera_ScreenEdgeHitEnable == false)
	{
		auto DeltaRotationX = Camera_RotateSpeed * InMouseX;
		AddActorLocalRotation(FRotator(0.0f, DeltaRotationX, 0.0f));
	}
}

void AMasterCommander::Camera_RotateAndPanY(float InMouseY)
{
	if (Camera_TPanFRotate && PlayerController->IsInputKeyDown(EKeys::MiddleMouseButton))
	{
		ROS_PanForward(InMouseY);
	}
	else if (!Camera_TPanFRotate && PlayerController->IsInputKeyDown(EKeys::MiddleMouseButton))
	{
		auto DeltaRotationY = ((Camera_RotateSpeed * InMouseY) + Camera->GetComponentRotation().Pitch);
		auto ClampedRotationY = FMath::Clamp<float>(DeltaRotationY, -88.0f, -37.0f);
		Camera->SetWorldRotation(FRotator(ClampedRotationY, Camera->GetComponentRotation().Yaw, Camera->GetComponentRotation().Roll));
		UE_LOG(LogTemp, Warning, TEXT("AMasterCommander::ROS_PanForward: %f"), ClampedRotationY)
	}
}

// Camera Pan Right
void AMasterCommander::ROS_PanRight_Implementation(float InValueX)
{
	MC_PanRight(InValueX);
}

bool AMasterCommander::ROS_PanRight_Validate(float InValueX)
{
	return true;
}

void AMasterCommander::MC_PanRight_Implementation(float InValueX)
{
	CameraPanX(InValueX);
}

bool AMasterCommander::MC_PanRight_Validate(float InValueX)
{
	return true;
}

void AMasterCommander::CameraPanX(float InValueX)
{
	auto DeltaLocationY = InValueX * Camera_PanSpeed;
	AddActorLocalOffset(FVector(0.0f, -DeltaLocationY, 0.0f), true);
}

// Camera Pan Forward
void AMasterCommander::ROS_PanForward_Implementation(float InValueY)
{
	MC_PanForward(InValueY);
}

bool AMasterCommander::ROS_PanForward_Validate(float InValueY)
{
	return true;
}

void AMasterCommander::MC_PanForward_Implementation(float InValueY)
{
	CameraPanY(InValueY);
}

bool AMasterCommander::MC_PanForward_Validate(float InValueY)
{
	return true;
}

void AMasterCommander::CameraPanY(float InValueY)
{
	auto DeltaLocationX = InValueY * Camera_PanSpeed;
	AddActorLocalOffset(FVector(-DeltaLocationX, 0.0F, 0.0f), true);
}

// Camera ROS Screen Edge Hit Right
void AMasterCommander::ROS_ScreenEdgeHitRight_Implementation(float InValueX)
{
	MC_ScreenEdgeHitRight(InValueX);
}

bool AMasterCommander::ROS_ScreenEdgeHitRight_Validate(float InValueX)
{
	return true;
}

void AMasterCommander::MC_ScreenEdgeHitRight_Implementation(float InValueX)
{
	Camera_ScreenEdgeHit();
}

bool AMasterCommander::MC_ScreenEdgeHitRight_Validate(float InValueX)
{
	return true;
}

// Camera ROS Screen Edge Hit Forward
void AMasterCommander::ROS_ScreenEdgeHitForward_Implementation(float InValueY)
{
	MC_ScreenEdgeHitForward(InValueY);
}

bool AMasterCommander::ROS_ScreenEdgeHitForward_Validate(float InValueX)
{
	return true;
}

void AMasterCommander::MC_ScreenEdgeHitForward_Implementation(float InValueY)
{
	Camera_ScreenEdgeHit();
}

bool AMasterCommander::MC_ScreenEdgeHitForward_Validate(float InValueX)
{
	return true;
}

void AMasterCommander::Camera_ScreenEdgeHit()
{
	if (GEngine->GameViewport != nullptr && PlayerController != nullptr)
	{
		// Viewport Size
		const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());

		float LocationX;
		float LocationY;
		PlayerController->GetMousePosition(LocationX, LocationY);
		float DeltaLocationX = (ViewportSize.X - LocationX) / ViewportSize.X;
		float DeltaLocationY = (ViewportSize.Y - LocationY) / ViewportSize.Y;

		if (DeltaLocationX >= 0.98f)
		{
			AddActorLocalOffset(FVector(0.0f, -Camera_ScreenEdgeHitSpeed, 0.0f), true);
			UE_LOG(LogTemp, Warning, TEXT("Left: %f"), DeltaLocationX)
		}
		else if (DeltaLocationX <= 0.02f)
		{
			AddActorLocalOffset(FVector(0.0f, Camera_ScreenEdgeHitSpeed, 0.0f), true);
			UE_LOG(LogTemp, Warning, TEXT("Right: %f"), DeltaLocationX)
		}
		else if (DeltaLocationY >= 0.98f)
		{
			AddActorLocalOffset(FVector(Camera_ScreenEdgeHitSpeed, 0.0f, 0.0f), true);
			UE_LOG(LogTemp, Warning, TEXT("Top: %f"), DeltaLocationY)
		}
		else if (DeltaLocationY <= 0.02f)
		{
			AddActorLocalOffset(FVector(-Camera_ScreenEdgeHitSpeed, 0.0f, 0.0f), true);
			UE_LOG(LogTemp, Warning, TEXT("Bottom: %f"), DeltaLocationY)
		}
	}

}
