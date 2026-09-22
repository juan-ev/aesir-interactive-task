#include "Gameplay/DefenseDestinationPoint.h"
#include "Components/SphereComponent.h"
#include "Core/DefenseGameState.h"

ADefenseDestinationPoint::ADefenseDestinationPoint()
{
	PrimaryActorTick.bCanEverTick = false;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	SetRootComponent(Collision);

	Collision->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::HandleBeginOverlap);
}

void ADefenseDestinationPoint::BeginPlay()
{
	Super::BeginPlay();

	if (ADefenseGameState* GameState = GetWorld()->GetGameState<ADefenseGameState>())
	{
		GameState->SetDestination(this);
	}
}

void ADefenseDestinationPoint::HandleBeginOverlap(UPrimitiveComponent* OverlappedComponent, ThisClass::Super* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ADefenseGameState* GameState = GetWorld()->GetGameState<ADefenseGameState>())
	{
		GameState->IncrementBreachCount();
	}
}
