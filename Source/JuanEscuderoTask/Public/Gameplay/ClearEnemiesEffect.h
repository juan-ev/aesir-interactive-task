#pragma once

#include "CoreMinimal.h"
#include "PickupEffect.h"
#include "ClearEnemiesEffect.generated.h"

UCLASS()
class JUANESCUDEROTASK_API UClearEnemiesEffect : public UPickupEffect
{
	GENERATED_BODY()

public:
	virtual void Apply_Implementation(AActor* Picker) override;
};
