#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DefenseDestinationPoint.generated.h"

class USphereComponent;

UCLASS(Blueprintable)
class JUANESCUDEROTASK_API ADefenseDestinationPoint : public AActor
{
	GENERATED_BODY()

public:
	ADefenseDestinationPoint();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> Collision;

	UFUNCTION()
	void HandleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
