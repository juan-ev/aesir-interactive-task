#include "Gameplay/Enemy.h"

#include "Components/SphereComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Gameplay/HealthComponent.h"

AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = false;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->SetCollisionProfileName(TEXT("Enemy"));
	SetRootComponent(Collision);

	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	HealthComponent->OnHealthDepleted.AddDynamic(this, &ThisClass::HandleHealthDepleted);

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

float AEnemy::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	HealthComponent->ApplyHealthChange(-ActualDamage);
	return ActualDamage;
}

void AEnemy::HandleHealthDepleted()
{
	OnDied.Broadcast();
}
