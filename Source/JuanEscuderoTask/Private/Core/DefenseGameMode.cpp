#include "Core/DefenseGameMode.h"
#include "Core/DefenseGameState.h"
#include "Kismet/GameplayStatics.h"

void ADefenseGameMode::BeginPlay()
{
	Super::BeginPlay();

	ADefenseGameState* GS = GetGameState<ADefenseGameState>();
	if (!GS)
	{
		return;
	}

	GS->SetRemainingTime(MatchDuration);
	GS->OnBreachCountChanged.AddDynamic(this, &ThisClass::HandleBreachCountChanged);

	GetWorldTimerManager().SetTimer(TickTimer, this, &ThisClass::TickTime, 1.f, true);
	GetWorldTimerManager().SetTimer(MatchTimer, this, &ThisClass::FinishMatchTime, MatchDuration);
}

void ADefenseGameMode::TickTime() const
{
	if (ADefenseGameState* GS = GetGameState<ADefenseGameState>())
	{
		GS->SetRemainingTime(GS->GetRemainingTime() - 1.f);
	}
}

void ADefenseGameMode::FinishMatchTime()
{
	EndMatch(EMatchResult::Won);
}

void ADefenseGameMode::HandleBreachCountChanged(int32 Count)
{
	if (Count >= MaxBreachesAllowed)
	{
		EndMatch(EMatchResult::Lost);
	}
}

void ADefenseGameMode::EndMatch(EMatchResult Result)
{
	GetWorldTimerManager().ClearTimer(TickTimer);
	GetWorldTimerManager().ClearTimer(MatchTimer);

	if (ADefenseGameState* GS = GetGameState<ADefenseGameState>())
	{
		GS->SetMatchResult(Result);
	}

	UGameplayStatics::SetGamePaused(GetWorld(), true);
}
