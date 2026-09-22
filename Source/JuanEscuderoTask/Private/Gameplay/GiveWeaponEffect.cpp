#include "Gameplay/GiveWeaponEffect.h"

#include "Gameplay/Weapon.h"
#include "Gameplay/WeaponComponent.h"

void UGiveWeaponEffect::Apply_Implementation(AActor* Picker)
{
	if (!ensure(Picker) || !ensureAlways(WeaponClass))
	{
		return;
	}

	if (UWeaponComponent* WeaponComponent = Picker->FindComponentByClass<UWeaponComponent>())
	{
		WeaponComponent->Equip(WeaponClass);
	}
}
