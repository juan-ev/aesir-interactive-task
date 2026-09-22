#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Enemy.generated.h"

class UFloatingPawnMovement;
class USphereComponent;
class UHealthComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDiedDelegate);

UCLASS(Blueprintable)
class JUANESCUDEROTASK_API AEnemy : public APawn
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FDiedDelegate OnDied;

public:
	AEnemy();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> Collision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UFloatingPawnMovement> MovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UHealthComponent> HealthComponent;

	UFUNCTION()
	void HandleHealthDepleted();
};
