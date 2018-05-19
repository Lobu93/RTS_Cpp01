// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class APawn;

/**
 * 
 */
UCLASS()
class RTS_CPP01_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	//UFUNCTION(BlueprintNativeEvent, Category = "RunOnServer Event")
	//void ROS_SetPlayerToSpawn(TSubclassOf<APawn> InPawn, FTransform InSpawnTransform, APlayerController* InController);
	//virtual void ROS_SetPlayerToSpawn_Implementation(TSubclassOf<APawn> InPawn, FTransform InSpawnTransform, APlayerController* InController);

	//UFUNCTION(Server, Reliable, WithValidation)
	//void ROS_SetPlayerToSpawnNetwork(TSubclassOf<APawn> InPawn, FTransform InSpawnTransform, APlayerController* InController);

	UFUNCTION(Server, UnReliable, BlueprintCallable, WithValidation, Category = "RunOnServer Event")
	void SetPlayerToSpawn(TSubclassOf<APawn> InPawn, FTransform InSpawnTransform, APlayerController* InController);
	virtual void SetPlayerToSpawn_Implementation(TSubclassOf<APawn> InPawn, FTransform InSpawnTransform, APlayerController* InController);

	/*
	UFUNCTION(Server, Reliable, WithValidation)
	void ROS_SetPlayerToSpawnNetwork();*/
};