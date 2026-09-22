#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "PickupEffect.generated.h"

UCLASS(Abstract, EditInlineNew, DefaultToInstanced, Blueprintable)
class JUANESCUDEROTASK_API UPickupEffect : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	void Apply(AActor* Picker);

	virtual void Apply_Implementation(AActor* Picker) {}
};
