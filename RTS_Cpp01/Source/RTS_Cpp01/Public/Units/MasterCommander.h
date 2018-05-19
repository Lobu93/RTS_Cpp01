// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MasterCommander.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class RTS_CPP01_API AMasterCommander : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMasterCommander();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Input")
	void Camera_MoveForwardAndBack(float InAxisValueForward);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void Camera_MoveLeftAndRight(float InAxisValueRight);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Our root component
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Character")
	UStaticMeshComponent* InvisibleObject = nullptr;

private:
	USpringArmComponent* SpringArm = nullptr;

	UCameraComponent* Camera = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	float Camera_MoveSpeed = 20.0f;
};
