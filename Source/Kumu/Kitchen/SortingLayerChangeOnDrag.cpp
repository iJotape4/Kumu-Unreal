#include "SortingLayerChangeOnDrag.h"
#include "ComponentUtilsMacros.h"

USortingLayerChangeOnDrag::USortingLayerChangeOnDrag()
{
}

void USortingLayerChangeOnDrag::OnRegister()
{
	Super::OnRegister();
	SETUP_REQUIRED_COMPONENT_FROM_OWNER(dragView);
	SETUP_REQUIRED_COMPONENT_FROM_OWNER(SortingLayerModifier);
}

void USortingLayerChangeOnDrag::BeginPlay()
{
	Super::BeginPlay();
	if (!dragView) return;
	
	dragView->OnDragBegan.AddDynamic(this, &USortingLayerChangeOnDrag::HandleDragBegan);
	dragView->OnDragEnd.AddDynamic(this, &USortingLayerChangeOnDrag::HandleDragEnd);
}

void USortingLayerChangeOnDrag::BeginDestroy()
{
	Super::BeginDestroy();
	if (!dragView) return;
	
	dragView->OnDragBegan.RemoveAll(this);
	dragView->OnDragEnd.RemoveAll(this);
}

void USortingLayerChangeOnDrag::HandleDragBegan(FHitResult pointerEventData)
{
	InitialSortingLayer = SortingLayerModifier->SortingLayer;
	SortingLayerModifier->SetSortingLayer(DraggedSortingLayer);
}

void USortingLayerChangeOnDrag::HandleDragEnd(FHitResult pointerEventData)
{
	SortingLayerModifier->SetSortingLayer(InitialSortingLayer);
}