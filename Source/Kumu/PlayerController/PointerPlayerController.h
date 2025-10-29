// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PointerPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

/**
 * 
 */
UCLASS(Abstract)
class KUMU_API APointerPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	APointerPlayerController();

protected:

	/** Time Threshold to know if it was a short press */
	UPROPERTY(EditAnywhere, Category="Input")
	float ShortPressThreshold;

	/** MappingContext */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputMappingContext* DefaultMappingContext;
	
	/** Jump Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* SetDestinationClickAction;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* SetDestinationTouchAction;

	/** Set to true if we're using touch input */
	uint32 bIsTouch : 1;

protected:
	virtual void SetupInputComponent() override;

	/** Input handlers */
	virtual void OnInputStarted() PURE_VIRTUAL(APointerPlayerController::OnInputStarted, );
	virtual void OnSetDestinationTriggered() PURE_VIRTUAL(APointerPlayerController::OnSetDestinationTriggered, );
	virtual void OnSetDestinationReleased() PURE_VIRTUAL(APointerPlayerController::OnSetDestinationReleased, );
	virtual void OnTouchTriggered() PURE_VIRTUAL(APointerPlayerController::OnTouchTriggered, );
	virtual void OnTouchReleased() PURE_VIRTUAL(APointerPlayerController::OnTouchReleased, );
};