// Copyright Epic Games, Inc. All Rights Reserved.

#include "DragNDropController.h"
#include "GameFramework/Pawn.h"
#include "Engine/World.h"
#include "Engine/LocalPlayer.h"
#include "Kumu.h"
#include "PlayerController/DragNDrop/UDraggable.h"

ADragNDropController::ADragNDropController()
{
}

void ADragNDropController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();
}

void ADragNDropController::OnInputStarted()
{
	UE_LOG(LogKumu, Warning, TEXT("Input Started"));
	StopMovement();
}

void ADragNDropController::OnSetDestinationTriggered()
{
	FHitResult Hit;
	bool bHitSuccessful = false;
	
	if (bIsTouch)
		bHitSuccessful = GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_Visibility, true, Hit);
	else
		bHitSuccessful = GetHitResultUnderCursor(ECC_Visibility, true, Hit);
	

	if (!bHitSuccessful)
		return;
	
	AActor* HitActor = Hit.GetActor();
	UE_LOG( LogKumu, Warning, TEXT("Hit actor : %s"), *HitActor->GetClass()->GetName())
	if (HitActor)
	{
		TArray<UActorComponent*> DraggableComps = HitActor->GetComponentsByInterface(UDraggable::StaticClass());
		if (DraggableComps.Num() > 0)
		{
			IDraggable::Execute_BeginDrag(DraggableComps[0], Hit.ImpactPoint);
		}
	}
}

void ADragNDropController::OnSetDestinationReleased()
{
	UE_LOG(LogKumu, Warning, TEXT("Input Released"));

}

// Triggered every frame when the input is held down
void ADragNDropController::OnTouchTriggered()
{
	bIsTouch = true;
	OnSetDestinationTriggered();
}

void ADragNDropController::OnTouchReleased()
{
	bIsTouch = false;
	OnSetDestinationReleased();
}