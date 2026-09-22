#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "WeaponComponent.generated.h"

class AWeapon;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWeaponEquippedDelegate, AWeapon*, Weapon);

UCLASS(BlueprintType, meta = (BlueprintSpawnableComponent))
class JUANESCUDEROTASK_API UWeaponComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FWeaponEquippedDelegate OnWeaponEquipped;

public:
	AWeapon* GetCurrentWeapon() const { return CurrentWeapon; }
	void Equip(TSubclassOf<AWeapon> WeaponClass);
	void Use() const;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> AttachTarget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AWeapon> CurrentWeapon;
};
