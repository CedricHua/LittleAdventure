// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BlueprintUIInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UBlueprintUIInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GAME2D_API IBlueprintUIInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, Category="CPPToBlueprint") 
	void PlayUIAnimation(bool bIsEnterLevel);
	

};
