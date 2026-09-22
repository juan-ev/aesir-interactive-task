#include "Core/DefensePlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "MVVMSubsystem.h"
#include "Blueprint/UserWidget.h"
#include "Core/DefenseGameState.h"
#include "Gameplay/InteractionComponent.h"
#include "Gameplay/WeaponComponent.h"
#include "UI/HUDViewModel.h"
#include "View/MVVMView.h"

void ADefensePlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetInputMode(FInputModeGameOnly());
	SetShowMouseCursor(false);
}

void ADefensePlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (!HUDViewModel)
	{
		CreateHUD();
	}

	BindHUDToPawn(InPawn);

	if (ADefenseGameState* GameState = GetWorld()->GetGameState<ADefenseGameState>())
	{
		GameState->OnMatchEnded.AddDynamic(this, &ThisClass::HandleMatchEnded);
	}
}

void ADefensePlayerController::OnUnPossess()
{
	if (HUDViewModel)
	{
		HUDViewModel->Unbind();
	}

	Super::OnUnPossess();
}

void ADefensePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (!IsLocalPlayerController() || !ensureAlways(InputMappingContext))
	{
		return;
	}

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
}

void ADefensePlayerController::CreateHUD()
{
	if (!ensureAlways(HUDWidgetClass))
	{
		return;
	}

	HUDViewModel = NewObject<UHUDViewModel>(this);
	UUserWidget* Widget = CreateWidget(this, HUDWidgetClass);

	if (UMVVMView* View = UMVVMSubsystem::GetViewFromUserWidget(Widget))
	{
		View->SetViewModel(TEXT("HUDViewModel"), HUDViewModel);
	}

	Widget->AddToViewport();
}

void ADefensePlayerController::BindHUDToPawn(const APawn* InPawn) const
{
	if (ADefenseGameState* GameState = GetWorld()->GetGameState<ADefenseGameState>())
	{
		HUDViewModel->BindGameState(GameState);
	}

	if (UInteractionComponent* InteractionComponent = InPawn->FindComponentByClass<UInteractionComponent>())
	{
		HUDViewModel->BindInteractionComponent(InteractionComponent);
	}

	if (UWeaponComponent* WeaponComponent = InPawn->FindComponentByClass<UWeaponComponent>())
	{
		HUDViewModel->BindWeaponComponent(WeaponComponent);
	}
}

void ADefensePlayerController::HandleMatchEnded(EMatchResult MatchResult)
{
	SetInputMode(FInputModeUIOnly());
	SetShowMouseCursor(true);
}
