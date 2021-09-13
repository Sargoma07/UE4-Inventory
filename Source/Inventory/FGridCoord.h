#pragma once

#include "FGridCoord.generated.h"


/**
 * Coordinate to grid 
 */
USTRUCT(BlueprintType)
struct INVENTORY_API FGridCoord
{
	FGridCoord(): Y(0), X(0)
	{
	}

	GENERATED_USTRUCT_BODY()

	FGridCoord(const int32 Y, const int32 X) : Y(Y), X(X)
	{
	}

	/**
	 * Row
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GridCoord)
	int32 Y;

	/**
	 * Column
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GridCoord)
	int32 X;

	/**
	 * @brief Check the valid grid coord 
	 * @return true - valid, false - invalid 
	 */
	bool IsValid() const { return Y >= 0 && X >= 0; }


	/**
	 * @brief Create an invalid coord
	 * @return Invalid coord
	 */
	static FGridCoord CreateInvalid() { return FGridCoord(-1, -1); }
};
