#include "AI/FindDestinationTask.h"

#include "StateTreeExecutionContext.h"
#include "Core/DefenseGameState.h"

EStateTreeRunStatus FFindDestinationTask::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const
{
	FInstanceDataType& Data = Context.GetInstanceData(*this);

	const ADefenseGameState* GameState = Context.GetWorld()->GetGameState<ADefenseGameState>();
	Data.Destination = GameState->GetDestination();

	return Data.Destination ? EStateTreeRunStatus::Succeeded : EStateTreeRunStatus::Failed;
}
