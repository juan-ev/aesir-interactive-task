#include "Gameplay/InteractionComponent.h"
#include "Gameplay/Interactable.h"

UInteractionComponent::UInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	SetGenerateOverlapEvents(true);
	BodyInstance.SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BodyInstance.SetCollisionProfileName(TEXT("Interactor"));

	OnComponentBeginOverlap.AddDynamic(this, &ThisClass::HandleBeginOverlap);
	OnComponentEndOverlap.AddDynamic(this, &ThisClass::HandleEndOverlap);
}

void UInteractionComponent::TryInteract()
{
	if (CurrentInteractable.IsValid())
	{
		IInteractable::Execute_Interact(CurrentInteractable.Get(), GetOwner());
	}
}

void UInteractionComponent::HandleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor || !OtherActor->Implements<UInteractable>())
	{
		return;
	}

	NearbyInteractables.AddUnique(OtherActor);
	RefreshCurrentInteractable();
}

void UInteractionComponent::HandleEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	NearbyInteractables.RemoveAll([OtherActor](const TWeakObjectPtr<AActor>& Interactable)
	{
		return Interactable.Get() == OtherActor;
	});

	RefreshCurrentInteractable();
}

void UInteractionComponent::RefreshCurrentInteractable()
{
	NearbyInteractables.RemoveAll([](const TWeakObjectPtr<AActor>& Interactable)
	{
		return !Interactable.IsValid();
	});

	FVector OwnerLocation = GetOwner()->GetActorLocation();
	AActor* Closest = nullptr;
	float ClosestDistSqr = MAX_flt;

	for (const TWeakObjectPtr<AActor>& Candidate : NearbyInteractables)
	{
		if (Candidate.IsValid())
		{
			const float DistSqr = FVector::DistSquared(OwnerLocation, Candidate.Get()->GetActorLocation());
			if (DistSqr < ClosestDistSqr)
			{
				ClosestDistSqr = DistSqr;
				Closest = Candidate.Get();
			}
		}
	}

	CurrentInteractable = Closest;
	OnInteractableChanged.Broadcast(Closest);
}
