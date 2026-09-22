#include "Gameplay/WeaponComponent.h"

#include "Gameplay/Weapon.h"

void UWeaponComponent::Equip(TSubclassOf<AWeapon> WeaponClass)
{
	if (!ensureAlways(WeaponClass))
	{
		return;
	}

	if (CurrentWeapon)
	{
		CurrentWeapon->Destroy();
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = GetOwner();
	SpawnParams.Instigator = Cast<APawn>(GetOwner());

	CurrentWeapon = GetWorld()->SpawnActor<AWeapon>(WeaponClass, GetComponentTransform(), SpawnParams);
	if (CurrentWeapon)
	{
		CurrentWeapon->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		OnWeaponEquipped.Broadcast(CurrentWeapon);
	}
}

void UWeaponComponent::Use() const
{
	if (CurrentWeapon)
	{
		CurrentWeapon->Fire();
	}
}
