#pragma once

#include "CoreMinimal.h"
#include "CustomTypes.h"
#include "GameFramework/GameModeBase.h"
#include "DefenseGameMode.generated.h"

UCLASS(Blueprintable)
class JUANESCUDEROTASK_API ADefenseGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DefenseGameMode", meta = (AllowPrivateAccess = "true"))
	float MatchDuration = 60.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DefenseGameMode", meta = (AllowPrivateAccess = "true"))
	int32 MaxBreachesAllowed = 3;

	/** Fired every second to update the HUD countdown.  */
	FTimerHandle TickTimer;

	/** One-shot timer that ends the match. */
	FTimerHandle MatchTimer;

	void TickTime() const;
	void FinishMatchTime();

	UFUNCTION()
	void HandleBreachCountChanged(int32 Count);

	void EndMatch(EMatchResult Result);
};
