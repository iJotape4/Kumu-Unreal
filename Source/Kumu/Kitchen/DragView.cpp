// Fill out your copyright notice in the Description page of Project Settings.


#include "DragView.h"

// Sets default values
UDragView::UDragView()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryComponentTick.bCanEverTick = true;
	OwnerActor = GetOwner();
}

// Called when the game starts or when spawned
void UDragView::BeginPlay()
{
	//PrimaryComponentTick.bCanEverTick = true;
	bDragging = false;
}

void UDragView::BeginDrag_Implementation(const FVector& WorldLocation)
{
	UE_LOG(LogTemp, Warning, TEXT("Begin Drag at Location: %s"), *WorldLocation.ToString());
	bDragging = true;
	DragOffset = WorldLocation - OwnerActor->GetActorLocation();
	LastDragLocation = WorldLocation + DragOffset;
}

void UDragView::Drag_Implementation(const FVector& WorldLocation)
{
	if (!bDragging) return;
	UE_LOG(LogTemp, Warning, TEXT("Dragging to Location: %s"), *WorldLocation.ToString());

	const FVector NewLocation = WorldLocation + DragOffset;
	OwnerActor->SetActorLocation(NewLocation);
	LastDragLocation = NewLocation;
}

void UDragView::EndDrag_Implementation()
{
	bDragging = false;
}