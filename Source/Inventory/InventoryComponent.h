// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "FItemDetails.h"
#include "FGridCoord.h"
#include "Components/ActorComponent.h"

#include "InventoryComponent.generated.h"

/**
 * Inventory system
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class INVENTORY_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInventoryComponent();

	/**
	 * Items
	 */
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category= "Inventory")
	TArray<FItemDetails> Items;

	/**
	 * Number of rows in an inventory grid 
	 */
	UPROPERTY(EditAnywhere, Category= "Inventory")
	int32 NumRows;

	/**
	 * Number of columns in an inventory grid
	 */
	UPROPERTY(EditAnywhere, Category= "Inventory")
	int32 NumColumns;
	/**
	 * Add item to the inventory
	 * @param Item item details to add in the inventory
	 * @return Count added items 
	 */
	UFUNCTION(BlueprintCallable, Category="Inventory")
	int32 AddItem(const FItemDetails& Item);

	/**
	 * Use item from inventory
	 * @param Item 
	 */
	UFUNCTION(BlueprintCallable, Category="Inventory")
	void UseItem(const FItemDetails& Item);

	/**
	 * Drop item 
	 * @param Item 
	 */
	UFUNCTION(BlueprintCallable, Category="Inventory")
	void DropItem(const FItemDetails& Item);

private:
	/**
	 * Set item to a cell the inventory by coordinate   
	 * @param Coord grid coordinate
	 * @param Item 
	 */
	void SetItemToCell(const FGridCoord& Coord, const FItemDetails& Item);
	
	/**
	 * Convert grid coordinate to a linear index
	 * @param Coord grid coordinate 
	 * @return linear index 
	 */
	int32 GetLinearIndex(const FGridCoord& Coord) const;
	
	/**
	 * Convert a linear index to a grid coordinate  
	 * @param Index linear index 
	 * @return grid coordinate
	 */
	FGridCoord GetCoord(int32 Index) const;

	/**
	 * Check is empty cell by a grid coordinate 
	 * @param Coord a grid coordinate
	 * @return true - empty, false - non-empty 
	 */
	bool IsEmptyCell(const FGridCoord& Coord) const;
	
	/**
	* Check is empty cell by a linear index 
	* @param Index a linear index
	* @return true - empty, false - non-empty 
	*/
	bool IsEmptyCell(int32 Index) const;
	
	/**
	 * Find an empty cell from the grid  
	 * @return Grid coordinate of cell
	 */
	FGridCoord FindEmptyCell() const;

	/**
	 * Get a item from grid by coordinate
	 * @param Coord a grid coordinate
	 * @return Pointer to item 
	 */
	FItemDetails* GetItem(const FGridCoord& Coord);

	/**
	 * Add a item to empty cell
	 * @param Item a object to add in the grid 
	 * @return Grid coordinate of cell
	 */
	FGridCoord AddToEmptyCell(const FItemDetails& Item);

	/**
	 * Add stackable item
	 * @param Item a stackable object to add
	 * @return Count added items 
	 */
	int32 AddStackableItem(const FItemDetails& Item);


	/**
	 * Find a stackable item by name. Quick the finding 
	 * @param Name title of item
	 * @return Found item 
	 */
	FItemDetails* FindNotFullStackableItemByName(const FString& Name);

	
};
