// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUpActor.h"

#include "InventoryComponent.h"
#include "Components/SphereComponent.h"

APickUpActor::APickUpActor()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->SetupAttachment(RootComponent);
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	Mesh->SetupAttachment(RootComponent);

	Item.Title = TEXT("Default value");
	Item.Icon = nullptr;
	Item.Count = 1;
}

void APickUpActor::Interact_Implementation(const AController* Controller)
{
	UE_LOG(LogTemp, Display, TEXT("Interaction with actor"));

	PickUp(Controller);
}

void APickUpActor::PickUp(const AController* Controller)
{
	UE_LOG(LogTemp, Display, TEXT("Pick up item: %s"), *Item.Title);

	const auto Component = Controller->GetComponentByClass(UInventoryComponent::StaticClass());
	const auto Inventory = Cast<UInventoryComponent>(Component);

	if (!Inventory)
	{
		UE_LOG(LogTemp, Warning, TEXT("Inventory component isn't exist in class %s"),
		       *Controller->GetClass()->GetName());
	}

	const auto AddedItemCount = Inventory->AddItem(this->Item);
	UE_LOG(LogTemp, Display, TEXT("Added %i %s items to the inventory"), AddedItemCount, *this->Item.Title);
	
	if (AddedItemCount == Item.Count)
	{
		Destroy();
		return;
	}

	Item.Count -= AddedItemCount;
}


