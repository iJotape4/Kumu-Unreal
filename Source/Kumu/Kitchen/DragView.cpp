// Fill out your copyright notice in the Description page of Project Settings.


#include "DragView.h"

// Sets default values
UDragView::UDragView()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryComponentTick.bCanEverTick = true;
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
	//PrimaryComponentTick.bCanEverTick = true;
	bDragging = false;
}

void UDragView::BeginDrag_Implementation(const FVector& WorldLocation)
{
	UE_LOG(LogTemp, Warning, TEXT("Begin Drag at Location: %s"), *WorldLocation.ToString());
	bDragging = true;
	DragPlaneOrigin = WorldLocation;
	LastDragLocation =  OwnerActor ->GetActorLocation();
	DragOffset = LastDragLocation-WorldLocation;
	//UE_LOG(LogTemp, Warning, TEXT("WorldLocation: %s"), *WorldLocation.ToString());
	//UE_LOG(LogTemp, Warning, TEXT("Drag Offset: %s"), *DragOffset.ToString());
	//UE_LOG(LogTemp, Warning, TEXT("Last Drag Location: %s"), *LastDragLocation.ToString());
}

void UDragView::Drag_Implementation(const FVector& WorldLocation)
{
	if (!bDragging) return;
	UE_LOG(LogTemp, Warning, TEXT("Dragging to Location: %s"), *WorldLocation.ToString());

	const FVector NewLocation = FVector(WorldLocation.X, DragPlaneOrigin.Y, WorldLocation.Z) + DragOffset;
	OwnerActor->SetActorLocation(NewLocation);
}

void UDragView::EndDrag_Implementation()
{
	bDragging = false;
}