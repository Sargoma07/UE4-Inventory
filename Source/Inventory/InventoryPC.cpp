// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryPC.h"

#include "Interacting.h"
#include "InventoryComponent.h"
#include "Chaos/AABB.h"

AInventoryPC::AInventoryPC()
{
	Inventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
}

void AInventoryPC::Interact() const
{
	const auto ActorToInteracting = GetActorToInteract();

	if (ActorToInteracting != nullptr)
	{
		IInteracting::Execute_Interact(ActorToInteracting, this);
	}
}

AActor* AInventoryPC::GetActorToInteract() const
{
	TArray<AActor*> OverlappingActors;

	GetPawn()->GetOverlappingActors(OverlappingActors, AActor::StaticClass());

	for (const auto Item : OverlappingActors)
	{
		if (Item->GetClass()->ImplementsInterface(UInteracting::StaticClass()))
		{
			return Item;
		}
	}
	return nullptr;
}
