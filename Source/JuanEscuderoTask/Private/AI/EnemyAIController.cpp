#include "AI/EnemyAIController.h"
#include "Components/StateTreeAIComponent.h"
#include "Gameplay/Enemy.h"

AEnemyAIController::AEnemyAIController()
{
	StateTreeAI = CreateDefaultSubobject<UStateTreeAIComponent>(TEXT("StateTreeAI"));
	StateTreeAI->SetStartLogicAutomatically(false);
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (AEnemy* Enemy = Cast<AEnemy>(InPawn))
	{
		Enemy->OnDied.AddDynamic(this, &ThisClass::HandleDied);
	}

	StateTreeAI->StartLogic();
}

void AEnemyAIController::OnUnPossess()
{
	if (AEnemy* Enemy = Cast<AEnemy>(GetPawn()))
	{
		Enemy->OnDied.RemoveDynamic(this, &AEnemyAIController::HandleDied);
	}

	StateTreeAI->StopLogic(TEXT("UnPossess"));
	Super::OnUnPossess();
}

void AEnemyAIController::HandleDied()
{
	StateTreeAI->StopLogic(TEXT("Death"));
}
