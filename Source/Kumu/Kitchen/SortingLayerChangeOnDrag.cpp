// Fill out your copyright notice in the Description page of Project Settings.


#include "SortingLayerChangeOnDrag.h"

#include "ComponentUtilsMacros.h"


// Sets default values for this component's properties
USortingLayerChangeOnDrag::USortingLayerChangeOnDrag()
{
	
}

void USortingLayerChangeOnDrag::OnRegister()
{
	Super::OnRegister();
	SETUP_REQUIRED_COMPONENT_FROM_OWNER(dragView);
	SETUP_REQUIRED_COMPONENT_FROM_OWNER(SortingLayerModifier);
}

// Called when the game starts
void USortingLayerChangeOnDrag::BeginPlay()
{
	Super::BeginPlay();
	dragView->OnDragBegan.AddDynamic(this, &USortingLayerChangeOnDrag::HandleDragBegan);
	dragView->OnDragEnd.AddDynamic(this, &USortingLayerChangeOnDrag::HandleDragEnd);
}

void USortingLayerChangeOnDrag::HandleDragBegan(FHitResult pointerEventData)
{
}

void USortingLayerChangeOnDrag::HandleDragEnd(FHitResult pointerEventData)
{
}
