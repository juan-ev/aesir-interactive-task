#pragma once

#include "CoreMinimal.h"
#include "CustomTypes.h"
#include "GameFramework/PlayerController.h"
#include "DefensePlayerController.generated.h"

class UUserWidget;
class UHUDViewModel;
class UInputMappingContext;

UCLASS()
class JUANESCUDEROTASK_API ADefensePlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> InputMappingContext;

	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(Transient)
	TObjectPtr<UHUDViewModel> HUDViewModel;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> HUDWidgetClass;

	void CreateHUD();
	void BindHUDToPawn(const APawn* InPawn) const;

	UFUNCTION()
	void HandleMatchEnded(EMatchResult MatchResult);
};
