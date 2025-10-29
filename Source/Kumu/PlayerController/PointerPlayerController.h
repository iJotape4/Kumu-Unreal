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
	UInputAction* PrimaryPointerAction;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* PrimaryTouchAction;

	/** Set to true if we're using touch input */
	uint32 bIsTouch : 1;

protected:
	virtual void SetupInputComponent() override;

	/** Input handlers */
	virtual void OnPointerDown() PURE_VIRTUAL(APointerPlayerController::OnPointerDown, );
	virtual void OnPointerHold() PURE_VIRTUAL(APointerPlayerController::OnPointerHold, );
	virtual void OnPointerUp() PURE_VIRTUAL(APointerPlayerController::OnPointerUp, );
	virtual void OnTouchTriggered() PURE_VIRTUAL(APointerPlayerController::OnTouchTriggered, );
	virtual void OnTouchReleased() PURE_VIRTUAL(APointerPlayerController::OnTouchReleased, );
};