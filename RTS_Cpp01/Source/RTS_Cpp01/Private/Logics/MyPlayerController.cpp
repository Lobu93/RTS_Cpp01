// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerController.h"
#include "Engine/World.h"
#include "MyGameModeBase.h"
#include "GameFramework/Pawn.h"

//void AMyPlayerController::ROS_SetPlayerToSpawn_Implementation(TSubclassOf<APawn> InPawn, FTransform InSpawnTransform, APlayerController * InController)
//{
//	// auto GameMode = (AMyGameModeBase*)GetWorld()->GetAuthGameMode();
//}
//
//void AMyPlayerController::ROS_SetPlayerToSpawnNetwork_Implementation(TSubclassOf<APawn> InPawn, FTransform InSpawnTransform, APlayerController * InController)
//{
//	ROS_SetPlayerToSpawn(InPawn, InSpawnTransform, InController);
//}
//
//bool AMyPlayerController::ROS_SetPlayerToSpawnNetwork_Validate(TSubclassOf<APawn> InPawn, FTransform InSpawnTransform, APlayerController * InController)
//{
//	return true;
//}


void AMyPlayerController::SetPlayerToSpawn_Implementation(TSubclassOf<APawn> InPawn, FTransform InSpawnTransform, APlayerController * InController)
{
	auto GameMode = (AMyGameModeBase*)GetWorld()->GetAuthGameMode();
	if (GameMode)
	{
		GameMode->SpawnPlayerCharacter(InPawn, InSpawnTransform, InController);
		UE_LOG(LogTemp, Warning, TEXT("AMyPlayerController::SetPlayerToSpawn_Implementation"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("GAME MODE BIXADO!"))
	}
}

bool AMyPlayerController::SetPlayerToSpawn_Validate(TSubclassOf<APawn> InPawn, FTransform InSpawnTransform, APlayerController* InController)
{
	return true;
}
