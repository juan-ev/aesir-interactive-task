#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FHealthChangedDelegate, float, Delta, float, Current, float, Max);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHealthDepletedDelegate);

UCLASS(BlueprintType, meta = (BlueprintSpawnableComponent))
class JUANESCUDEROTASK_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FHealthChangedDelegate OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FHealthDepletedDelegate OnHealthDepleted;

public:
	UHealthComponent();

	virtual void BeginPlay() override;

	/** Apply a health delta (negative = damage, positive = heal). */
	void ApplyHealthChange(float Delta);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Health", meta = (ClampMin = "1", UIMin = "1", AllowPrivateAccess = "true"))
	float MaxHealth = 100.f;

	float CurrentHealth = 0.f;
};
