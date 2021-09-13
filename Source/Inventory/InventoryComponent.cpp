// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

#include "InventoryPC.h"
#include "PickUpActor.h"
#include "Usable.h"

UInventoryComponent::UInventoryComponent()
{
	NumRows = 6;
	NumColumns = 5;

	const auto GridSize = GetLinearIndex(FGridCoord(NumRows - 1, NumColumns - 1));
	Items.Init(FItemDetails(), GridSize + 1);
}

int32 UInventoryComponent::AddItem(const FItemDetails& Item) 
{
	UE_LOG(LogTemp, Display, TEXT("Added item %s to inventory"), *Item.Title);

	if (!Item.bStackable)
	{
		const FGridCoord Coord = AddToEmptyCell(Item);
		return Coord.IsValid() ? Item.Count : 0;
	}

	return AddStackableItem(Item);
}

void UInventoryComponent::UseItem(const FItemDetails& Item)
{
	check(Item.bIsUsable);
	
	auto* UseItem  = NewObject<UObject>(this,Item.ItemType); 
	check(UseItem->GetClass()->ImplementsInterface(UUsable::StaticClass()))

	const auto Player = Cast<APlayerController>(GetOwner());
	check(Player != nullptr);
	
	IUsable::Execute_Use(UseItem, Player);

	UE_LOG(LogTemp, Display, TEXT("Use item: %s"), *Item.Title);
}

void UInventoryComponent::DropItem(const FItemDetails& Item)
{
	check(Item.ItemType != nullptr);

	const auto Player = Cast<APlayerController>(GetOwner());
	check(Player != nullptr);

	int constexpr Offset = 100;
	const FVector SpawnLocation = Player->GetPawn()->GetActorLocation() + Player->GetPawn()->GetActorForwardVector() * Offset;
	
	const auto PickUp = GetWorld()->SpawnActor<APickUpActor>(Item.ItemType,SpawnLocation, FRotator());
	PickUp->Item = Item;
	
	UE_LOG(LogTemp, Display, TEXT("Drop item: %s"), *Item.Title);
}

int32 UInventoryComponent::AddStackableItem(const FItemDetails& Item)
{
	// Fill don't full item
	//
	const auto NotFullItem = FindNotFullStackableItemByName(Item.Title);

	int32 ItemCount = Item.Count;
	if (NotFullItem != nullptr)
	{
		const int32 FreeStackCount =  NotFullItem->MaxStackSize - NotFullItem->Count;
		if (FreeStackCount > 0)
		{
			const auto CountToAdd = FreeStackCount - ItemCount >= 0 ? ItemCount : FreeStackCount;  
			NotFullItem->Count += CountToAdd;

			ItemCount -= CountToAdd;
			
			if (ItemCount == 0)
			{
				return Item.Count - ItemCount;  
			}
		}
	}

	// Fill empty cell by max size the stack 
	//
	const auto ItemCountStack = ItemCount / Item.MaxStackSize;
	
	for (auto i = 0; i < ItemCountStack; i++)
	{
		auto ItemToAdd = Item;
		ItemToAdd.Count = ItemToAdd.MaxStackSize;
		const FGridCoord Coord = AddToEmptyCell(ItemToAdd);
		if (!Coord.IsValid())
		{
			return Item.Count - ItemCount; 
		}
		ItemCount -= ItemToAdd.MaxStackSize;
	}

	// Added to empty cell remaining items 
	//
	if (ItemCount > 0)
	{
		auto ItemToAdd = Item;
		ItemToAdd.Count = ItemCount;

		const FGridCoord Coord = AddToEmptyCell(ItemToAdd);
		if (!Coord.IsValid())
		{
			return Item.Count - ItemCount; 
		}
		ItemCount = 0;
	}
	
	return Item.Count - ItemCount;
}

void UInventoryComponent::SetItemToCell(const FGridCoord& Coord, const FItemDetails& Item)
{
	check(Coord.X >= 0 && Coord.X < NumColumns);
	check(Coord.Y >= 0 && Coord.Y < NumRows);

	const int32 LinearIndex = GetLinearIndex(Coord);
	check(LinearIndex >= 0 && LinearIndex < Items.Num());
	Items[LinearIndex] = Item;
}

int32 UInventoryComponent::GetLinearIndex(const FGridCoord& Coord) const
{
	return Coord.Y * NumColumns + Coord.X;
}

FGridCoord UInventoryComponent::GetCoord(const int32 Index) const
{
	return FGridCoord(Index / NumColumns, Index % NumColumns);
}

bool UInventoryComponent::IsEmptyCell(const FGridCoord& Coord) const
{
	const auto Index = GetLinearIndex(Coord);
	return IsEmptyCell(Index);
}

bool UInventoryComponent::IsEmptyCell(const int32 Index) const
{
	const auto Item = Items[Index];
	return Item.Title == TEXT("");
}

FItemDetails* UInventoryComponent::GetItem(const FGridCoord& Coord)
{
	const int32 LinearIndex = GetLinearIndex(Coord);
	return &Items[LinearIndex];
}

FGridCoord UInventoryComponent::FindEmptyCell() const
{
	for (int32 i = 0; i < Items.Num(); ++i)
	{
		if (IsEmptyCell(i))
		{
			return GetCoord(i);
		}
	}
	UE_LOG(LogTemp, Display, TEXT("Invetory is full"));
	return FGridCoord::CreateInvalid();
}

FItemDetails* UInventoryComponent::FindNotFullStackableItemByName(const FString& Name)
{
	const auto Result = Items.FindByPredicate([Name](const FItemDetails& Item)
	{
		return Item.bStackable && Item.Title == Name && Item.Count < Item.MaxStackSize;
	});
	return Result;
}

FGridCoord UInventoryComponent::AddToEmptyCell(const FItemDetails& Item)
{
	const auto Coord = FindEmptyCell();

	if (!Coord.IsValid())
	{
		return Coord;
	}

	SetItemToCell(Coord, Item);

	return Coord;
}
