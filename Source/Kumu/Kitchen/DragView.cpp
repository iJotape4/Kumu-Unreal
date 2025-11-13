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

	PrimitiveComponent = GetOwner()->FindComponentByClass<UPrimitiveComponent>();
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

void UDragView::BeginDrag_Implementation(const FHitResult &pointerEventData)
{
	OnDragBegan.Broadcast(pointerEventData);
	//UE_LOG(LogTemp, Warning, TEXT("Begin Drag at Location: %s"), *WorldLocation.ToString());
	bDragging = true;
	FVector WorldLocation = pointerEventData.ImpactPoint;
	DragPlaneOrigin = WorldLocation;
	LastDragLocation =  OwnerActor ->GetActorLocation();
	DragOffset = LastDragLocation-WorldLocation;
	PrimitiveComponent->SetCollisionResponseToChannel(ECC_Camera, ECR_Overlap);
	
}

void UDragView::Drag_Implementation(const FHitResult &pointerEventData)
{
	if (!bDragging) return;
	//UE_LOG(LogTemp, Warning, TEXT("Dragging to Location: %s"), *WorldLocation.ToString());
	FVector WorldLocation = pointerEventData.ImpactPoint;
	const FVector NewLocation = FVector(WorldLocation.X, DragPlaneOrigin.Y, WorldLocation.Z) + DragOffset;
	OwnerActor->SetActorLocation(NewLocation);
}

void UDragView::EndDrag_Implementation(const FHitResult &pointerEventData)
{
	OnDragEnd.Broadcast(pointerEventData);
	bDragging = false;
	OwnerActor->SetActorLocation(LastDragLocation);
	PrimitiveComponent->SetCollisionResponseToChannel(ECC_Camera, ECR_Block);
}