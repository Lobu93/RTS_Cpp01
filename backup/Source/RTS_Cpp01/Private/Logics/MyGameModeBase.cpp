// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameModeBase.h"
#include "Engine/World.h"
#include "GameFramework/Pawn.h"

AMyGameModeBase::AMyGameModeBase()
{
	bUseSeamlessTravel = true;
}

void AMyGameModeBase::SpawnPlayerCharacter_Implementation(TSubclassOf<APawn> InPawn, FTransform InSpawnTransform, APlayerController * InController)
{	
	if (InPawn)
	{
		// TSubclassOf<class APawn> Pawn;

		auto Pawn = GetWorld()->SpawnActor<APawn>(InPawn, InSpawnTransform);

		InController->Possess(Pawn);
	}
}
