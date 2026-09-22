#include "Gameplay/Pickup.h"

#include "Components/SphereComponent.h"
#include "Gameplay/PickupEffect.h"

APickup::APickup()
{
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	SphereCollision->SetCollisionProfileName(TEXT("Interactable"));
	SphereCollision->SetupAttachment(RootComponent);
}

void APickup::Interact_Implementation(AActor* Interactor)
{
	if (!ensureAlways(Effect))
	{
		return;
	}

	Effect->Apply(Interactor);

	if (bDestroyAfterPickedUp)
	{
		Destroy();
	}
}

FText APickup::GetInteractionText_Implementation() const
{
	return FText::FromString(TEXT("Interact"));
}
