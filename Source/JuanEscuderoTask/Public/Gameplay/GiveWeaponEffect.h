#pragma once

#include "CoreMinimal.h"
#include "PickupEffect.h"
#include "GiveWeaponEffect.generated.h"

class AWeapon;

UCLASS()
class JUANESCUDEROTASK_API UGiveWeaponEffect : public UPickupEffect
{
	GENERATED_BODY()

public:
	virtual void Apply_Implementation(AActor* Picker) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AWeapon> WeaponClass;
};
