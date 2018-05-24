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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Our root component
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Character")
	UStaticMeshComponent* InvisibleObject = nullptr;

private:
	UFUNCTION(BlueprintCallable, Category = "Input")
	void Camera_MoveForwardAndBack(float InAxisValueForward);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void Camera_MoveLeftAndRight(float InAxisValueRight);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void Camera_ZoomIn();

	UFUNCTION(BlueprintCallable, Category = "Input")
	void Camera_ZoomOut();

	// Camera Rotate and Pan
	UFUNCTION(BlueprintCallable, Category = "Input")
	void Camera_SetHitEnable();

	UFUNCTION(BlueprintCallable, Category = "Input")
	void Camera_SetHitDisable();

	UFUNCTION(BlueprintCallable, Category = "Input")
	void Camera_TPanFRotateEnable();

	UFUNCTION(BlueprintCallable, Category = "Input")
	void Camera_TPanFRotateDisable();

	// Camera Rotate
	void Camera_RotateAndPanX(float InMouseX);
	void Camera_RotateAndPanY(float InMouseY);

	// Camera Pan X
	UFUNCTION(Server, UnReliable, WithValidation)
		void ROS_PanRight(float InValueX);
	void ROS_PanRight_Implementation(float InValueX);

	UFUNCTION(NetMulticast, Unreliable, WithValidation)
		void MC_PanRight(float InValueX);
	void MC_PanRight_Implementation(float InValueX);

	void CameraPanX(float InValueX);

	// Camera Pan Y
	UFUNCTION(Server, UnReliable, WithValidation)
		void ROS_PanForward(float InValueY);
	void ROS_PanForward_Implementation(float InValueY);

	UFUNCTION(NetMulticast, Unreliable, WithValidation)
		void MC_PanForward(float InValueY);
	void MC_PanForward_Implementation(float InValueY);

	void CameraPanY(float InValueY);

	// Camera Screen Edge Hit
	// Camera ROS Screen Edge Hit X
	UFUNCTION(Server, UnReliable, WithValidation)
		void ROS_ScreenEdgeHitRight(float InValueX);
	void ROS_ScreenEdgeHitRight_Implementation(float InValueX);

	UFUNCTION(NetMulticast, Unreliable, WithValidation)
		void MC_ScreenEdgeHitRight(float InValueX);
	void MC_ScreenEdgeHitRight_Implementation(float InValueX);

	// Camera ROS Screen Edge Hit Y
	UFUNCTION(Server, UnReliable, WithValidation)
		void ROS_ScreenEdgeHitForward(float InValueY);
	void ROS_ScreenEdgeHitForward_Implementation(float InValueY);

	UFUNCTION(NetMulticast, Unreliable, WithValidation)
		void MC_ScreenEdgeHitForward(float InValueY);
	void MC_ScreenEdgeHitForward_Implementation(float InValueY);

	// Main Function of Edge Hit
	void Camera_ScreenEdgeHit();

	USpringArmComponent* SpringArm = nullptr;

	UCameraComponent* Camera = nullptr;

	APlayerController* PlayerController;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	float Camera_MoveSpeed = 20.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	float Camera_ZoomSpeed = 100.0f;

	bool Camera_ScreenEdgeHitEnable = true;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	float Camera_RotateSpeed = 2.5f;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	float Camera_PanSpeed = 30.0f;

	bool Camera_TPanFRotate = false;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	float Camera_ScreenEdgeHitSpeed = 20.0f;
};
