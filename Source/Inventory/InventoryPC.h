// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/PlayerController.h"
#include "InventoryPC.generated.h"

/**
 * A player controller that has an inventory system
 */
UCLASS()
class INVENTORY_API AInventoryPC : public APlayerController
{
	GENERATED_BODY()

public:
	AInventoryPC();
	
	/**
	 * Inventory system
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Inventory")
	class UInventoryComponent* Inventory;
	
public:
	/**
	 * Interact with object 
	 */
	UFUNCTION(BlueprintCallable, Category="Interaction")
	void Interact() const;

private:
	/**
	 * Get an actor to interact
	 * @return Actor to interact
	 */
	AActor* GetActorToInteract() const;
};
