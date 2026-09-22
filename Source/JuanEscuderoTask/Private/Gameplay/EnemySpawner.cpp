#include "Gameplay/EnemySpawner.h"
#include "Gameplay/Enemy.h"

AEnemySpawner::AEnemySpawner()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	ScheduleNextSpawn();
}

void AEnemySpawner::ScheduleNextSpawn()
{
	const float Time = FMath::FRandRange(SpawnIntervalMin, SpawnIntervalMax);
	GetWorldTimerManager().SetTimer(SpawnTimer, this, &ThisClass::SpawnEnemy, Time);
}

void AEnemySpawner::SpawnEnemy()
{
	if (!ensureAlways(EnemyClass))
	{
		return;
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	GetWorld()->SpawnActor<AEnemy>(EnemyClass, GetActorTransform(), SpawnParams);

	ScheduleNextSpawn();
}
