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
	UFUNCTION(Server, UnReliable, BlueprintCallable, WithValidation, Category = "RunOnServer Event")
	void SetPlayerToSpawn(TSubclassOf<APawn> InPawn, FTransform InSpawnTransform, APlayerController* InController);
	virtual void SetPlayerToSpawn_Implementation(TSubclassOf<APawn> InPawn, FTransform InSpawnTransform, APlayerController* InController);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void LockMouse();
	void ReleaseMouse();
};