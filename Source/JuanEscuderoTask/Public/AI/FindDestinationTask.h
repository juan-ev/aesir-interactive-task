#pragma once

#include "CoreMinimal.h"
#include "StateTreeTaskBase.h"
#include "FindDestinationTask.generated.h"

USTRUCT()
struct JUANESCUDEROTASK_API FFindDestinationTaskInstanceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Output")
	TObjectPtr<AActor> Destination;
};

USTRUCT(meta = (DisplayName = "Find Destination"))
struct JUANESCUDEROTASK_API FFindDestinationTask : public FStateTreeTaskCommonBase
{
	GENERATED_BODY()

	using FInstanceDataType = FFindDestinationTaskInstanceData;

	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }
	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;
};
