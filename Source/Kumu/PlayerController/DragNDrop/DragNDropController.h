// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "PlayerController/PointerPlayerController.h"
#include "DragNDropController.generated.h"

class UInputMappingContext;
class UInputAction;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

/**
 *  Player controller for a top-down perspective game.
 *  Implements point and click based controls
 */
UCLASS(abstract)
class ADragNDropController : public APointerPlayerController
{
	GENERATED_BODY()

public:

	/** Constructor */
	ADragNDropController();
private:
	UActorComponent* DraggedActor;
	// FVector DragPlaneOrigin;
	// FVector DragPlaneNormal;
	// FVector LastDragWorldLocation;
	bool bIsDragging;
	bool GetCursorWorldProjection(FHitResult& pointerEventData) const;

protected:

	/** Initialize input bindings */
	virtual void SetupInputComponent() override;
	
	/** Input handlers */
	virtual void OnPointerDown() override;
	virtual void OnPointerHold() override;
	virtual void OnPointerUp() override;
	virtual void OnTouchTriggered() override;
	virtual void OnTouchReleased() override;

};