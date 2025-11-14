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
	
	if (!OwnerActor) return;

	/*
	 * Draggable objects must be movable in order to work properly
	 */
	
	if (USceneComponent* Root = OwnerActor->GetRootComponent())
	{
		Root->SetMobility(EComponentMobility::Movable);
	}

	PrimitiveComponent = OwnerActor->FindComponentByClass<UPrimitiveComponent>();
	
	/*
	 * Draggable objects must initialize blocking all channels in order to work properly
	 */
	if (PrimitiveComponent)
	{
		PrimitiveComponent->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
		PrimitiveComponent->SetCollisionResponseToAllChannels(ECR_Block);
	}

	PrimitiveComponent = OwnerActor->FindComponentByClass<UPrimitiveComponent>();
	
	/*
	 Draggable objects must initialize blocking all channels in order to work properly
	 */
	if (PrimitiveComponent)
	{
		PrimitiveComponent->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
		PrimitiveComponent->SetCollisionResponseToAllChannels(ECR_Block);
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


void UDragView::BeginDrag_Implementation(const FHitResult &pointerEventData)
{
	OnDragBegan.Broadcast(pointerEventData);
	//UE_LOG(LogTemp, Warning, TEXT("Begin Drag at Location: %s"), *WorldLocation.ToString());
	bDragging = true;
	FVector WorldLocation = pointerEventData.ImpactPoint;
	DragPlaneOrigin = WorldLocation;
	LastDragLocation =  OwnerActor ->GetActorLocation();
	DragOffset = LastDragLocation-WorldLocation;
	SetCollisionResponsesForDragging(false);
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
	SetCollisionResponsesForDragging(true);
}

/*
 This function sets the collision responses of the PrimitiveComponent to either block or overlap collision channels based on the enable parameter.
  If enable is true, the component will block these channels; if false, it will overlap

 * ECC_Visibility is being used for hovering, disabling it prevents the dragged object from blocking the raycast to detect the hovered objects underneath
 * ECC_Camera is being used for DropTargets, disabling it prevent the dragged object from blocking the raycast to detect DropTargets underneath
 */
void UDragView::SetCollisionResponsesForDragging(bool enable) const
{
	ECollisionResponse collisionResponse = enable ? ECR_Block : ECR_Overlap;
	PrimitiveComponent->SetCollisionResponseToChannel(ECC_Camera, collisionResponse);
	PrimitiveComponent->SetCollisionResponseToChannel(ECC_Visibility, collisionResponse);
}