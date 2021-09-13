#pragma once

#include "FItemDetails.generated.h"


USTRUCT(BlueprintType)
struct FItemDetails
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item Details")
	FString Title;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item Details")
	UTexture2D* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item Details")
	int32 Count;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item Details")
	bool bStackable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item Details")
	int32 MaxStackSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item Details")
	bool bIsUsable;

	UPROPERTY(EditDefaultsOnly, Category="Item Details")
	TSubclassOf<AActor> ItemType;

	FItemDetails() :
		Icon(nullptr),
		Count(0),
		bStackable(false),
		MaxStackSize(1),
		bIsUsable(false)
	{
	}

	/**Hash function*/
	friend uint32 GetTypeHash(const FItemDetails& Item)
	{
		const uint32 HashCode = GetTypeHash(Item.Title);
		return HashCode;
	}

	/**Override operator equals*/
	friend bool operator==(const FItemDetails& LHS, const FItemDetails& RHS)
	{
		return GetTypeHash(LHS) == GetTypeHash(RHS);
	}
};
