// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Interacting.h"
#include "GameFramework/Actor.h"
#include "FItemDetails.h"

#include "PickUpActor.generated.h"

UCLASS()
class INVENTORY_API APickUpActor : public AActor, public IInteracting
{
	GENERATED_BODY()

public:
	APickUpActor();
	
	/**
	 * Mesh
	 */
	UPROPERTY(EditAnywhere, Category= "PickUp")
	class UStaticMeshComponent* Mesh;

	/**
	 * Collision
	 */
	UPROPERTY(EditAnywhere, Category= "PickUp")
	class USphereComponent* Collision;

	/**
	 * Item details 
	 */
	UPROPERTY(EditAnywhere, Category= "Item")
	FItemDetails Item;

public:
	/**
	* Implementation to interact with this object 
	* @param Controller someone who will interact with the item
	*/
	virtual void Interact_Implementation(const AController* Controller) override;
	
private:

	/**
	 * Pick up this object  
	 * @param Controller someone who will pick up the item
	 */
	void PickUp(const AController* Controller);
};
