// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"
#include "GameFramework/Pawn.h"
#include "MasterCommander.h"


void UMyGameInstance::SetDefaultPawn()
{
	if (FactionName == "Humans")
	{
		DefaultPawn = HumanPawn;
	}
	else if (FactionName == "Aliens")
	{
		DefaultPawn = AlienPawn;
	}
}

TSubclassOf<APawn> UMyGameInstance::GetDefaultPawn() const
{
	return DefaultPawn;
}
