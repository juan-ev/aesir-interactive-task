#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

class AEnemy;

UCLASS(Blueprintable)
class JUANESCUDEROTASK_API AEnemySpawner : public AActor
{
	GENERATED_BODY()

public:
	AEnemySpawner();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AEnemy> EnemyClass;

	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.1", UIMin = "0.1", AllowPrivateAccess = "true"))
	float SpawnIntervalMin = 2.f;

	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.1", UIMin = "0.1", AllowPrivateAccess = "true"))
	float SpawnIntervalMax = 5.f;

	FTimerHandle SpawnTimer;

	void ScheduleNextSpawn();
	void SpawnEnemy();
};
