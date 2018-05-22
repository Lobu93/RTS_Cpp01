// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerController.h"
#include "Engine/World.h"
#include "MyGameModeBase.h"
#include "GameFramework/Pawn.h"


void AMyPlayerController::SetPlayerToSpawn_Implementation(TSubclassOf<APawn> InPawn, FTransform InSpawnTransform, APlayerController * InController)
{
	auto GameMode = (AMyGameModeBase*)GetWorld()->GetAuthGameMode();
	if (GameMode)
	{
		GameMode->SpawnPlayerCharacter(InPawn, InSpawnTransform, InController);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AMyPlayerController::SetPlayerToSpawn_Implementation GAME MODE BIXADO!"))
	}
}

bool AMyPlayerController::SetPlayerToSpawn_Validate(TSubclassOf<APawn> InPawn, FTransform InSpawnTransform, APlayerController* InController)
{
	return true;
}
