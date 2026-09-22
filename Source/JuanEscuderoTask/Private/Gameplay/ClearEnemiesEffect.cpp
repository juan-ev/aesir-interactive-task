#include "Gameplay/ClearEnemiesEffect.h"
#include "EngineUtils.h"
#include "Gameplay/Enemy.h"
#include "Gameplay/HealthComponent.h"

void UClearEnemiesEffect::Apply_Implementation(AActor* Picker)
{
	if (!ensure(Picker))
	{
		return;
	}

	for (TActorIterator<AEnemy> It(Picker->GetWorld()); It; ++It)
	{
		if (UHealthComponent* HealthComponent = It->FindComponentByClass<UHealthComponent>())
		{
			HealthComponent->ApplyHealthChange(-MAX_flt);
		}
	}
}
