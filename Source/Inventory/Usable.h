// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Usable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UUsable : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for an object that can be used
 */
class INVENTORY_API IUsable
{
	GENERATED_BODY()

public:
	/**Use object. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Use")
	void Use(const AController* Controller);
};
