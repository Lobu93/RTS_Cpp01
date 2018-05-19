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

