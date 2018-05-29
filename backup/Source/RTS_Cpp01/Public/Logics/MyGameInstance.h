// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

class APawn;
class AMasterCommander;

/**
 * 
 */
UCLASS()
class RTS_CPP01_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetDefaultPawn();

	UFUNCTION(BlueprintCallable, Category = "Setup")
	TSubclassOf<class APawn> GetDefaultPawn() const;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Commanders")
	TSubclassOf<class APawn> HumanPawn = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Commanders")
	TSubclassOf<class APawn> AlienPawn = nullptr;

private:
	TSubclassOf<class APawn> DefaultPawn = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Commanders")
	FName FactionName = "Humans";	

};
