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
#if PLATFORM_WINDOWS || PLATFORM_MAC || PLATFORM_LINUX
	GetHitResultUnderCursor(channel, true, Hit);
#endif
	
#if PLATFORM_ANDROID || PLATFORM_IOS
	GetHitResultUnderFinger(ETouchIndex::Touch1, channel, true, Hit);
#endif
	
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
	FHitResult PointerEventData = GetCursorWorldProjection();
	if (!PointerEventData.bBlockingHit)
		return;
	
	if (AActor* HitActor = PointerEventData.GetActor())
	{
		if (UActorComponent* ActorComponent = CheckActorUnderPointerImplementsInterface(UDraggable::StaticClass(), HitActor))
		{
			DraggedActor = ActorComponent;
			bIsDragging = true;
			IDraggable::Execute_BeginDrag(DraggedActor.Get(), PointerEventData);
		}
	}
}

void ADragNDropController::OnPointerHold()
{
	if (!bIsDragging || !DraggedActor.IsValid()) return;

	// Get the current cursor world projection as an FHitResult
	FHitResult PointerEventData = GetCursorWorldProjection();
	if (PointerEventData.bBlockingHit)
	{
		IDraggable::Execute_Drag(DraggedActor.Get(), PointerEventData);
	}
}

void ADragNDropController::OnPointerUp()
{
	//UE_LOG(LogKumu, Warning, TEXT("Input Released"));
	if (!bIsDragging || !DraggedActor.IsValid()) return;

	// Get the hit using the camera collision channel
	FHitResult PointerEventData = GetCursorWorldProjection(ECC_Camera);
	if (PointerEventData.bBlockingHit)
	{
		if (AActor* HitActor = PointerEventData.GetActor())
		{
			if (UActorComponent* ActorComponent = CheckActorUnderPointerImplementsInterface(UDropTarget::StaticClass(), HitActor))
			{
				IDropTarget::Execute_Drop(ActorComponent, PointerEventData);
				UE_LOG(LogTemp, Warning, TEXT("Dropping in Actor: %s"), *HitActor->GetActorLabel());
			}
		}
	}
	
	IDraggable::Execute_EndDrag(DraggedActor.Get(), PointerEventData);
	DraggedActor = nullptr;
	bIsDragging = false;
}