#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

UINTERFACE(MinimalAPI, BlueprintType)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

class JUANESCUDEROTASK_API IInteractable
{
	GENERATED_BODY()

public:
	/** Called when the interactor triggers this actor. Implementer defines the effect. */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interactable")
	void Interact(AActor* Interactor);

	/** Prompt shown in the HUD while this actor is the focused interactable. */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interactable")
	FText GetInteractionText() const;
};
