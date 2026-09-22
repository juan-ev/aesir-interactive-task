#include "Core/DefenseGameState.h"

ADefenseGameState::ADefenseGameState()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ADefenseGameState::SetMatchResult(EMatchResult Result)
{
	if (MatchResult != EMatchResult::None)
	{
		return;
	}

	MatchResult = Result;
	OnMatchEnded.Broadcast(MatchResult);
}

void ADefenseGameState::SetRemainingTime(float Time)
{
	RemainingTime = Time;
	OnRemainingTimeChanged.Broadcast(RemainingTime);
}

void ADefenseGameState::IncrementBreachCount()
{
	++BreachCount;
	OnBreachCountChanged.Broadcast(BreachCount);
}
