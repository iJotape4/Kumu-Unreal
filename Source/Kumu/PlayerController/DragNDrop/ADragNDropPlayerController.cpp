// Fill out your copyright notice in the Description page of Project Settings.


#include "ADragNDropPlayerController.h"

#include "UDraggable.h"

void AADragNDropPlayerController::BeginPlay()
{
	Super::BeginPlay();
	DraggedActor = nullptr;
	bIsDragging = false;
}

void AADragNDropPlayerController::PlayerTick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (!bIsDragging || !DraggedActor) return;

	FVector WorldPos;
	if (GetCursorWorldProjection(WorldPos))
	{
		const FVector Delta = WorldPos - LastDragWorldLocation;
		IDraggable::Execute_Drag(DraggedActor, WorldPos, Delta);
		LastDragWorldLocation = WorldPos;
	}
}

void AADragNDropPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	// if (InputComponent)
	// {
	// 	InputComponent->BindKey(EKeys::LeftMouseButton, IE_Pressed, this, &AADragNDropPlayerController::OnPointerDown);
	// 	InputComponent->BindKey(EKeys::LeftMouseButton, IE_Released, this, &AADragNDropPlayerController::OnPointerUp);
	// }
}

void AADragNDropPlayerController::OnPointerDown(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("OnLeftMouseButtonDown"));
	FHitResult Hit;
	// trace under cursor
	if (GetHitResultUnderCursor(ECC_Visibility, true, Hit))
	{
		AActor* HitActor = Hit.GetActor();
		if (HitActor && HitActor->GetClass()->ImplementsInterface(UDraggable::StaticClass()))
		{
			DraggedActor = HitActor;
			DragPlaneOrigin = Hit.ImpactPoint;
			DragPlaneNormal = FVector::UpVector; // simple horizontal plane; adjust if needed
			LastDragWorldLocation = Hit.ImpactPoint;
			bIsDragging = true;
			IDraggable::Execute_BeginDrag(DraggedActor, Hit.ImpactPoint);
		}
	}
}

void AADragNDropPlayerController::OnPointerUp(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("OnleftMouseButtonUp"));
	if (bIsDragging && DraggedActor)
	{
		IDraggable::Execute_EndDrag(DraggedActor);
	}
	DraggedActor = nullptr;
	bIsDragging = false;
}

bool AADragNDropPlayerController::GetCursorWorldProjection(FVector& OutWorldLocation) const
{
	FVector WorldOrigin, WorldDir;
	if (!DeprojectMousePositionToWorld(WorldOrigin, WorldDir)) return false;

	// Line-plane intersection
	const FVector LineEnd = WorldOrigin + WorldDir * 100000.0f;
	const FPlane DragPlane(DragPlaneOrigin, DragPlaneNormal);
	OutWorldLocation = FMath::LinePlaneIntersection(WorldOrigin, LineEnd, DragPlane);

	return true;
}