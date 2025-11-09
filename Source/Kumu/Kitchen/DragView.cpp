// Fill out your copyright notice in the Description page of Project Settings.


#include "DragView.h"

// Sets default values
UDragView::UDragView()
{
	OwnerActor = GetOwner();
}

void UDragView::OnRegister()
{
	Super::OnRegister();
	if (AActor* Owner = GetOwner())
	{
		if (USceneComponent* Root = Owner->GetRootComponent())
		{
			Root->SetMobility(EComponentMobility::Movable);
		}
	}
}

void UDragView::OnUnregister()
{
	if (GetWorld() && GetWorld()->IsGameWorld())
		if (AActor* Owner = GetOwner())
			if (USceneComponent* Root = Owner->GetRootComponent())
				Root->SetMobility(EComponentMobility::Static);

	Super::OnUnregister();
}

// Called when the game starts or when spawned
void UDragView::BeginPlay()
{
	bDragging = false;
}

void UDragView::BeginDrag_Implementation(const FVector& WorldLocation)
{
	//UE_LOG(LogTemp, Warning, TEXT("Begin Drag at Location: %s"), *WorldLocation.ToString());
	bDragging = true;
	DragPlaneOrigin = WorldLocation;
	LastDragLocation =  OwnerActor ->GetActorLocation();
	DragOffset = LastDragLocation-WorldLocation;
}

void UDragView::Drag_Implementation(const FVector& WorldLocation)
{
	if (!bDragging) return;
	//UE_LOG(LogTemp, Warning, TEXT("Dragging to Location: %s"), *WorldLocation.ToString());

	const FVector NewLocation = FVector(WorldLocation.X, DragPlaneOrigin.Y, WorldLocation.Z) + DragOffset;
	OwnerActor->SetActorLocation(NewLocation);
}

void UDragView::EndDrag_Implementation()
{
	bDragging = false;
}