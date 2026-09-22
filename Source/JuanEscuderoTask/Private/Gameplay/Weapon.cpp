#include "Gameplay/Weapon.h"

#include "Engine/DamageEvents.h"

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	CurrentAmmo = MagazineSize;
	OnAmmoChanged.Broadcast(CurrentAmmo, MagazineSize);
}

void AWeapon::Fire()
{
	AController* Controller = GetInstigatorController();
	if (!Controller)
	{
		return;
	}

	if (CurrentAmmo <= 0)
	{
		StartReload();
		return;
	}

	OnFired.Broadcast();
	--CurrentAmmo;
	OnAmmoChanged.Broadcast(CurrentAmmo, MagazineSize);

	FVector Start;
	FRotator ViewRotation;
	Controller->GetPlayerViewPoint(Start, ViewRotation);

	const FVector Forward = ViewRotation.Vector();
	const FVector End = Start + Forward * MaxRange;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	QueryParams.AddIgnoredActor(GetInstigator());

	FHitResult Hit;
	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, TraceChannel, QueryParams))
	{
		if (AActor* HitActor = Hit.GetActor())
		{
			FPointDamageEvent DamageEvent(Damage, Hit, Forward, nullptr);
			HitActor->TakeDamage(Damage, DamageEvent, Controller, this);
		}
	}
}

void AWeapon::StartReload()
{
	FTimerManager& TimerManager = GetWorldTimerManager();
	if (TimerManager.IsTimerActive(ReloadTimer))
	{
		return;
	}

	OnReloadStarted.Broadcast();
	GetWorldTimerManager().SetTimer(ReloadTimer, this, &ThisClass::FinishReload, ReloadDuration);
}

void AWeapon::FinishReload()
{
	CurrentAmmo = MagazineSize;
	OnAmmoChanged.Broadcast(CurrentAmmo, MagazineSize);
	OnReloadFinished.Broadcast();
}
