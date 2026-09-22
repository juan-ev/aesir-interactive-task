#include "Gameplay/HealthComponent.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
}

void UHealthComponent::ApplyHealthChange(float Delta)
{
	if (CurrentHealth <= 0)
	{
		return;
	}

	CurrentHealth = FMath::Clamp(CurrentHealth + Delta, 0.f, MaxHealth);
	OnHealthChanged.Broadcast(Delta, CurrentHealth, MaxHealth);

	if (CurrentHealth <= 0)
	{
		OnHealthDepleted.Broadcast();
	}
}
