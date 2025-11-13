// Copyright Epic Games, Inc. All Rights Reserved.

#include "DragNDropController.h"

#include "DropTarget.h"
#include "GameFramework/Pawn.h"
#include "Engine/World.h"
#include "Engine/LocalPlayer.h"
#include "PlayerController/DragNDrop/UDraggable.h"

ADragNDropController::ADragNDropController()
{
}

FHitResult ADragNDropController::GetCursorWorldProjection(ECollisionChannel channel) const
{
	FHitResult Hit;
	// Fill Hit via engine helper; if nothing was hit, Hit.bBlockingHit will be false
	GetHitResultUnderCursor(channel, true, Hit);
	return Hit;
}

UActorComponent* ADragNDropController::CheckActorUnderPointerImplementsInterface(TSubclassOf<UInterface> InterfaceClass,
	AActor*& OutActor) const
{
	TArray<UActorComponent*> DraggableComps = OutActor->GetComponentsByInterface(InterfaceClass);
	if (DraggableComps.Num() > 0)
	{
		return DraggableComps[0];
	}
	
	return  nullptr;
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
	// compute hit in a single expression to avoid reassignment warnings
	bool bHitSuccessful = bIsTouch
		? GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_Visibility, true, Hit)
		: GetHitResultUnderCursor(ECC_Visibility, true, Hit);

	if (!bHitSuccessful)
		return;
	
	AActor* HitActor = Hit.GetActor();
	///UE_LOG( LogKumu, Warning, TEXT("Hit actor : %s"), *HitActor->GetClass()->GetName())
	if (HitActor)
	{
		if (UActorComponent* ActorComponent = CheckActorUnderPointerImplementsInterface(UDraggable::StaticClass(), HitActor))
		{
			DraggedActor = ActorComponent;
			bIsDragging = true;
			IDraggable::Execute_BeginDrag(DraggedActor.Get(), Hit);
		}
	}
}

void ADragNDropController::OnPointerHold()
{
	if (!bIsDragging || !DraggedActor.IsValid()) return;

	// Get the current cursor world projection as an FHitResult
	FHitResult eventData = GetCursorWorldProjection();
	if (eventData.bBlockingHit)
	{
		IDraggable::Execute_Drag(DraggedActor.Get(), eventData);
	}
}

void ADragNDropController::OnPointerUp()
{
	//UE_LOG(LogKumu, Warning, TEXT("Input Released"));
	if (!bIsDragging || !DraggedActor.IsValid()) return;

	// Get the hit using the camera collision channel
	FHitResult Hit = GetCursorWorldProjection(ECC_Camera);
	if (Hit.bBlockingHit)
	{
		if (AActor* HitActor = Hit.GetActor())
		{
			if (UActorComponent* ActorComponent = CheckActorUnderPointerImplementsInterface(UDropTarget::StaticClass(), HitActor))
			{
				IDropTarget::Execute_Drop(ActorComponent, Hit.ImpactPoint);
				UE_LOG(LogTemp, Warning, TEXT("Dropping in Actor: %s"), *HitActor->GetActorLabel());
			}
		}
	}
	
	IDraggable::Execute_EndDrag(DraggedActor.Get(), Hit);
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