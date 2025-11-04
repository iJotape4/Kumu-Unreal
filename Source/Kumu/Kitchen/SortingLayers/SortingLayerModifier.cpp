// Fill out your copyright notice in the Description page of Project Settings.


#include "SortingLayerModifier.h"

#include "Kumu.h"


// Sets default values for this component's properties
USortingLayerModifier::USortingLayerModifier()
{
}

void USortingLayerModifier::OnRegister()
{
	Super::OnRegister();
	if (!Sprite && GetOwner())
	{
		Sprite = GetOwner()->FindComponentByClass<UPaperSpriteComponent>();
	}

	ChangeSortingLayer(SortingLayer);
}


// Called when the game starts
void USortingLayerModifier::BeginPlay()
{
	Super::BeginPlay();
}

void USortingLayerModifier::SetSortingLayer(FSortingLayers NewSortingLayer)
{
	ChangeSortingLayer(NewSortingLayer);
}

void USortingLayerModifier::ChangeSortingLayer(FSortingLayers NewSortingLayer)
{
	if (!Sprite) return;

	SortingLayer = NewSortingLayer;
	Sprite->TranslucencySortPriority = static_cast<int32>(SortingLayer);
	// Make sure render state updates so changes are visible immediately in-game
	Sprite->MarkRenderStateDirty();
	
	///Sprite->se
}

#if WITH_EDITOR
void USortingLayerModifier::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	UE_LOG(LogKumu, Warning, TEXT("PostEditChangeProperty"));
	Super::PostEditChangeProperty(PropertyChangedEvent);

	const FName PropertyName = PropertyChangedEvent.Property ? PropertyChangedEvent.Property->GetFName() : NAME_None;
	if (PropertyName == GET_MEMBER_NAME_CHECKED(USortingLayerModifier, SortingLayer))
	{
		UE_LOG(LogKumu, Warning, TEXT("Sorting Layer Changed"));
		ChangeSortingLayer(SortingLayer);
	}
}
#endif
