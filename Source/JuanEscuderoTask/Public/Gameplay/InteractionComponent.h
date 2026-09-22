#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "InteractionComponent.generated.h"

class UCapsuleComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInteractableChangedDelegate, const AActor*, Interactable);

UCLASS(BlueprintType, meta = (BlueprintSpawnableComponent))
class JUANESCUDEROTASK_API UInteractionComponent : public UCapsuleComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FInteractableChangedDelegate OnInteractableChanged;

public:
	UInteractionComponent();

	AActor* GetCurrentInteractable() const { return CurrentInteractable.Get(); }

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void TryInteract();

private:
	TArray<TWeakObjectPtr<AActor>> NearbyInteractables;
	TWeakObjectPtr<AActor> CurrentInteractable;

	UFUNCTION()
	void HandleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void HandleEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void RefreshCurrentInteractable();
};
