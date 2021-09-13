// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interacting.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteracting : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for an object that it can interact with
 */
class INVENTORY_API IInteracting
{
	GENERATED_BODY()

public:
	/**Interact with object. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Interaction")
	void Interact(const AController* Controller);
};
