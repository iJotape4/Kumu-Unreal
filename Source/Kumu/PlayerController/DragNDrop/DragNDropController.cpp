// Copyright Epic Games, Inc. All Rights Reserved.

#include "DragNDropController.h"

#include "DropTarget.h"
#include "GameFramework/Pawn.h"
#include "Engine/World.h"
#include "Engine/LocalPlayer.h"
#include "Kumu.h"
#include "PlayerController/DragNDrop/UDraggable.h"

ADragNDropController::ADragNDropController()
{
}

bool ADragNDropController::GetCursorWorldProjection(FVector& OutWorldLocation) const
{
	FHitResult Hit;
	if ( !GetHitResultUnderCursor(ECC_Visibility, true, Hit))
		return false;
	
	OutWorldLocation = Hit.ImpactPoint;
	return true;
}

void ADragNDropController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();
}

void ADragNDropController::OnPointerDown()
{
	//UE_LOG(LogKumu, Warning, TEXT("Input Started"));
	FHitResult Hit;
	bool bHitSuccessful = false;
	
	if (bIsTouch)
		bHitSuccessful = GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_Visibility, true, Hit);
	else
		bHitSuccessful = GetHitResultUnderCursor(ECC_Visibility, true, Hit);
	

	if (!bHitSuccessful)
		return;
	
	AActor* HitActor = Hit.GetActor();
	///UE_LOG( LogKumu, Warning, TEXT("Hit actor : %s"), *HitActor->GetClass()->GetName())
	if (HitActor)
	{
		TArray<UActorComponent*> DraggableComps = HitActor->GetComponentsByInterface(UDraggable::StaticClass());
		if (DraggableComps.Num() > 0)
		{
			DraggedActor = DraggableComps[0];
			bIsDragging = true;
			IDraggable::Execute_BeginDrag(DraggedActor, Hit.ImpactPoint);
		}
	}
}

void ADragNDropController::OnPointerHold()
{
	if (!bIsDragging || !DraggedActor) return;

	FVector WorldPos;
	
	if (GetCursorWorldProjection(WorldPos))
	{
		IDraggable::Execute_Drag(DraggedActor, WorldPos);
	}
}

void ADragNDropController::OnPointerUp()
{
	//UE_LOG(LogKumu, Warning, TEXT("Input Released"));
	if (!bIsDragging || !DraggedActor) return;


	FHitResult Hit;
	if ( GetHitResultUnderCursor(ECC_Camera, true, Hit))
	{
		if (AActor* HitActor = Hit.GetActor())
		{
			TArray<UActorComponent*> DropTargets = HitActor->GetComponentsByInterface(UDropTarget::StaticClass());
			if (DropTargets.Num() > 0)
			{
				IDropTarget::Execute_Drop(DropTargets[0], Hit.ImpactPoint);	
			}
			
			UE_LOG(LogTemp, Warning, TEXT("Dropping in Actor: %s"), *HitActor->GetActorLabel());
		}
	}
	
	IDraggable::Execute_EndDrag(DraggedActor);
	DraggedActor = nullptr;
	bIsDragging = false;
}

// Triggered every frame when the input is held down
void ADragNDropController::OnTouchTriggered()
{
	bIsTouch = true;
	OnPointerHold();
}

void ADragNDropController::OnTouchReleased()
{
	bIsTouch = false;
	OnPointerUp();
}