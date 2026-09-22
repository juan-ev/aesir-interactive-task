#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "Core/CustomTypes.h"
#include "HUDViewModel.generated.h"

class ADefenseGameState;
class UInteractionComponent;
class AWeapon;
class UWeaponComponent;
class UTexture2D;

UCLASS()
class JUANESCUDEROTASK_API UHUDViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	void BindGameState(ADefenseGameState* GameState);
	void BindInteractionComponent(UInteractionComponent* InteractionComponent);
	void BindWeaponComponent(UWeaponComponent* WeaponComponent);
	void Unbind();

protected:
	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter = "HasMatchEnded", meta = (AllowPrivateAccess = "true"))
	bool bMatchEnded;

	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter, meta = (AllowPrivateAccess = "true"))
	FText MatchResultText;

	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter, meta = (AllowPrivateAccess = "true"))
	FText RemainingTime;

	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter, meta = (AllowPrivateAccess = "true"))
	int32 BreachCount;

	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter = "CanInteract", meta = (AllowPrivateAccess = "true"))
	bool bCanInteract;

	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter, meta = (AllowPrivateAccess = "true"))
	FText InteractionText;

	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter = "HasWeapon", meta = (AllowPrivateAccess = "true"))
	bool bHasWeapon;

	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTexture2D> WeaponIcon;

	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter, meta = (AllowPrivateAccess = "true"))
	int32 CurrentAmmo;

	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter, meta = (AllowPrivateAccess = "true"))
	int32 MaxAmmo;

	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter = "IsReloading", meta = (AllowPrivateAccess = "true"))
	bool bIsReloading;

public:
	bool HasMatchEnded() const { return bMatchEnded; }
	FText GetMatchResultText() const { return MatchResultText; }
	FText GetRemainingTime() const { return RemainingTime; }
	int32 GetBreachCount() const { return BreachCount; }

	bool CanInteract() const { return bCanInteract; }
	FText GetInteractionText() const { return InteractionText; }

	bool HasWeapon() const { return bHasWeapon; }
	UTexture2D* GetWeaponIcon() const { return WeaponIcon; }
	int32 GetCurrentAmmo() const { return CurrentAmmo; }
	int32 GetMaxAmmo() const { return MaxAmmo; }
	bool IsReloading() const { return bIsReloading; }

private:
	TWeakObjectPtr<ADefenseGameState> BoundGameState;
	TWeakObjectPtr<UInteractionComponent> BoundInteractionComponent;
	TWeakObjectPtr<UWeaponComponent> BoundWeaponComponent;
	TWeakObjectPtr<AWeapon> BoundWeapon;

	UFUNCTION()
	void HandleMatchEnded(EMatchResult MatchResult);

	UFUNCTION()
	void HandleRemainingTimeChanged(float Remaining);

	UFUNCTION()
	void HandleBreachCountChanged(int32 Count);

	UFUNCTION()
	void HandleInteractableChanged(const AActor* Interactable);

	UFUNCTION()
	void HandleWeaponEquipped(AWeapon* Weapon);

	UFUNCTION()
	void HandleAmmoChanged(int32 Current, int32 Max);

	UFUNCTION()
	void HandleReloadStarted();

	UFUNCTION()
	void HandleReloadFinished();

	void UnbindWeapon();
};
