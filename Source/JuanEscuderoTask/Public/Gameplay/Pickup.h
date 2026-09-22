#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "Pickup.generated.h"

class USphereComponent;
class UPickupEffect;

UCLASS(Blueprintable)
class JUANESCUDEROTASK_API APickup : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	APickup();

	virtual void Interact_Implementation(AActor* Interactor) override;
	virtual FText GetInteractionText_Implementation() const override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Pickup", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> SphereCollision;

	UPROPERTY(EditAnywhere, Instanced, Category = "Pickup", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPickupEffect> Effect;

	UPROPERTY(EditAnywhere, Category = "Pickup")
	bool bDestroyAfterPickedUp = true;
};
