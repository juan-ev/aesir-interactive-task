#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "PickupEffect.generated.h"

UCLASS(Abstract, EditInlineNew, DefaultToInstanced, Blueprintable)
class JUANESCUDEROTASK_API UPickupEffect : public UObject
{
	GENERATED_BODY()

public:
	/** Apply this effect, given the picker. Subclasses define the concrete behavior. */
	UFUNCTION(BlueprintNativeEvent)
	void Apply(AActor* Picker);

	virtual void Apply_Implementation(AActor* Picker) {}
};
