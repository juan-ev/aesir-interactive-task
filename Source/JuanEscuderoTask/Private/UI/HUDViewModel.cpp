#include "UI/HUDViewModel.h"
#include "Core/DefenseGameState.h"
#include "Gameplay/Interactable.h"
#include "Gameplay/InteractionComponent.h"
#include "Gameplay/Weapon.h"
#include "Gameplay/WeaponComponent.h"

void UHUDViewModel::BindGameState(ADefenseGameState* GameState)
{
	BoundGameState = GameState;
	if (!BoundGameState.IsValid())
	{
		return;
	}

	GameState->OnMatchEnded.AddDynamic(this, &ThisClass::HandleMatchEnded);
	GameState->OnRemainingTimeChanged.AddDynamic(this, &ThisClass::HandleRemainingTimeChanged);
	GameState->OnBreachCountChanged.AddDynamic(this, &ThisClass::HandleBreachCountChanged);

	HandleRemainingTimeChanged(GameState->GetRemainingTime());
	HandleBreachCountChanged(GameState->GetBreachCount());
}

void UHUDViewModel::BindInteractionComponent(UInteractionComponent* InteractionComponent)
{
	BoundInteractionComponent = InteractionComponent;
	if (!BoundInteractionComponent.IsValid())
	{
		return;
	}

	InteractionComponent->OnInteractableChanged.AddDynamic(this, &ThisClass::HandleInteractableChanged);
	HandleInteractableChanged(InteractionComponent->GetCurrentInteractable());
}

void UHUDViewModel::BindWeaponComponent(UWeaponComponent* WeaponComponent)
{
	BoundWeaponComponent = WeaponComponent;
	if (!BoundWeaponComponent.IsValid())
	{
		return;
	}

	WeaponComponent->OnWeaponEquipped.AddDynamic(this, &ThisClass::HandleWeaponEquipped);
	HandleWeaponEquipped(WeaponComponent->GetCurrentWeapon());
}

void UHUDViewModel::Unbind()
{
	if (BoundGameState.IsValid())
	{
		BoundGameState->OnMatchEnded.RemoveAll(this);
		BoundGameState->OnRemainingTimeChanged.RemoveAll(this);
		BoundGameState->OnBreachCountChanged.RemoveAll(this);
	}

	if (BoundInteractionComponent.IsValid())
	{
		BoundInteractionComponent->OnInteractableChanged.RemoveAll(this);
	}

	if (BoundWeaponComponent.IsValid())
	{
		BoundWeaponComponent->OnWeaponEquipped.RemoveAll(this);
	}

	UnbindWeapon();
}

void UHUDViewModel::HandleMatchEnded(EMatchResult MatchResult)
{
	const FText Text = MatchResult == EMatchResult::Won
		? FText::FromString(TEXT("YOU WIN"))
		: FText::FromString(TEXT("YOU LOSE"));

	UE_MVVM_SET_PROPERTY_VALUE(MatchResultText, Text);
	UE_MVVM_SET_PROPERTY_VALUE(bMatchEnded, true);
}

void UHUDViewModel::HandleRemainingTimeChanged(float Remaining)
{
	const int32 Total = FMath::CeilToInt(Remaining);
	const FString Str = FString::Printf(TEXT("%02d:%02d"), Total / 60, Total % 60);
	UE_MVVM_SET_PROPERTY_VALUE(RemainingTime, FText::FromString(Str));
}

void UHUDViewModel::HandleBreachCountChanged(int32 Count)
{
	UE_MVVM_SET_PROPERTY_VALUE(BreachCount, Count);
}

void UHUDViewModel::HandleInteractableChanged(const AActor* Interactable)
{
	UE_MVVM_SET_PROPERTY_VALUE(bCanInteract, Interactable != nullptr);
	UE_MVVM_SET_PROPERTY_VALUE(InteractionText, Interactable ? IInteractable::Execute_GetInteractionText(Interactable) : FText::GetEmpty());
}

void UHUDViewModel::HandleWeaponEquipped(AWeapon* Weapon)
{
	UnbindWeapon();

	BoundWeapon = Weapon;
	UE_MVVM_SET_PROPERTY_VALUE(bHasWeapon, Weapon != nullptr);

	if (!bHasWeapon)
	{
		return;
	}

	UE_MVVM_SET_PROPERTY_VALUE(WeaponIcon, Weapon->GetIcon());

	Weapon->OnAmmoChanged.AddDynamic(this, &ThisClass::HandleAmmoChanged);
	Weapon->OnReloadStarted.AddDynamic(this, &ThisClass::HandleReloadStarted);
	Weapon->OnReloadFinished.AddDynamic(this, &ThisClass::HandleReloadFinished);

	HandleAmmoChanged(Weapon->GetCurrentAmmo(), Weapon->GetMaxAmmo());
}

void UHUDViewModel::HandleAmmoChanged(int32 Current, int32 Max)
{
	UE_MVVM_SET_PROPERTY_VALUE(CurrentAmmo, Current);
	UE_MVVM_SET_PROPERTY_VALUE(MaxAmmo, Max);
}

void UHUDViewModel::HandleReloadStarted()
{
	UE_MVVM_SET_PROPERTY_VALUE(bIsReloading, true);
}

void UHUDViewModel::HandleReloadFinished()
{
	UE_MVVM_SET_PROPERTY_VALUE(bIsReloading, false);
}

void UHUDViewModel::UnbindWeapon()
{
	if (BoundWeapon.IsValid())
	{
		BoundWeapon->OnAmmoChanged.RemoveAll(this);
		BoundWeapon->OnReloadStarted.RemoveAll(this);
		BoundWeapon->OnReloadFinished.RemoveAll(this);
	}
}
