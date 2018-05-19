// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameModeBase.generated.h"

class APawn;

/**
 * 
 */
UCLASS()
class RTS_CPP01_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMyGameModeBase();	
	
	UFUNCTION(BlueprintNativeEvent, Category = "Custom Event")
	void SpawnPlayerCharacter(TSubclassOf<APawn> InPawn, FTransform InSpawnTransform, APlayerController* InController);
	virtual void SpawnPlayerCharacter_Implementation(TSubclassOf<APawn> InPawn, FTransform InSpawnTransform, APlayerController* InController);

};
