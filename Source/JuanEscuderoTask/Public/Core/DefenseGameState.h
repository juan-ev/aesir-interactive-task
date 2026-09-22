#pragma once

#include "CoreMinimal.h"
#include "CustomTypes.h"
#include "GameFramework/GameStateBase.h"
#include "DefenseGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMatchEndedDelegate, EMatchResult, MatchResult);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRemainingTimeChangedDelegate, float, Remaining);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBreachCountChangedDelegate, int32, Count);

UCLASS(Blueprintable)
class JUANESCUDEROTASK_API ADefenseGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FMatchEndedDelegate OnMatchEnded;

	UPROPERTY(BlueprintAssignable)
	FRemainingTimeChangedDelegate OnRemainingTimeChanged;

	UPROPERTY(BlueprintAssignable)
	FBreachCountChangedDelegate OnBreachCountChanged;

public:
	ADefenseGameState();

	EMatchResult GetMatchResult() const { return MatchResult; }
	void SetMatchResult(EMatchResult Result);

	float GetRemainingTime() const { return RemainingTime; }
	void SetRemainingTime(float Time);

	AActor* GetDestination() const { return Destination; }
	void SetDestination(AActor* InDestination) { Destination = InDestination; }

	int32 GetBreachCount() const { return BreachCount; }
	void IncrementBreachCount();

private:
	EMatchResult MatchResult = EMatchResult::None;
	float RemainingTime = 0.f;

	UPROPERTY(Transient)
	TObjectPtr<AActor> Destination;

	int32 BreachCount = 0;
};
