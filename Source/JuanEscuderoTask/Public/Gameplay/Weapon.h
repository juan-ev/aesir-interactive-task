#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAmmoChangedDelegate, int32, Current, int32, Max);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFiredDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FReloadDelegate);

UCLASS(Blueprintable)
class JUANESCUDEROTASK_API AWeapon : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FAmmoChangedDelegate OnAmmoChanged;

	UPROPERTY(BlueprintAssignable)
	FFiredDelegate OnFired;

	UPROPERTY(BlueprintAssignable)
	FReloadDelegate OnReloadStarted;

	UPROPERTY(BlueprintAssignable)
	FReloadDelegate OnReloadFinished;

public:
	AWeapon();

protected:
	virtual void BeginPlay() override;

public:
	void Fire();

	UTexture2D* GetIcon() const { return Icon; }
	int32 GetMaxAmmo() const { return MagazineSize; }
	int32 GetCurrentAmmo() const { return CurrentAmmo; }

private:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTexture2D> Icon;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon", meta = (ClampMin = 1, UIMin = 1, AllowPrivateAccess = "true"))
	int32 MagazineSize = 20;

	UPROPERTY(Transient, VisibleAnywhere, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	int32 CurrentAmmo = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon", meta = (ClampMin = 0, UIMin = 0, AllowPrivateAccess = "true"))
	float ReloadDuration = 1.f;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon", meta = (ClampMin = 1, UIMin = 1, ClampMax = 100000, UIMax = 100000, Units = "cm", AllowPrivateAccess = "true"))
	float MaxRange = 1000.f;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	float Damage = 25.f;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<ECollisionChannel> TraceChannel;

	FTimerHandle ReloadTimer;

	void StartReload();
	void FinishReload();
};
