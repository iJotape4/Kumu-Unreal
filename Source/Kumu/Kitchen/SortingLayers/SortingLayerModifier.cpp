// Fill out your copyright notice in the Description page of Project Settings.


#include "SortingLayerModifier.h"

#include "GameplayTagsManager.h"
#include "Kumu.h"
#include "SortingLayerUtils.h"


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
	if (!SortingLayersAsset) SortingLayersAsset = SortingLayerUtils::GetSortingLayersAsset();
	ChangeSortingLayer(SortingLayer);
}

int USortingLayerModifier::GetTagLocalIndex(FGameplayTag Tag)
{
	if (!SortingLayersAsset) return 0;

	TArray<FGameplayTagTableRow*> Rows;
	SortingLayersAsset->GetAllRows<FGameplayTagTableRow>(TEXT("GetTagLocalIndex"), Rows);
	for (int32 Index = 0; Index < Rows.Num(); Index++)
	{
		//UE_LOG(LogKumu, Warning, TEXT("Row Name %s"), *Rows[Index]->Tag.ToString());
		if (Rows[Index]->Tag == Tag.GetTagName())
			return Index;
	}

	return 0;
}


// Called when the game starts
void USortingLayerModifier::BeginPlay()
{
	Super::BeginPlay();
}

void USortingLayerModifier::SetSortingLayer(FGameplayTag NewSortingLayer)
{
	ChangeSortingLayer(NewSortingLayer);
}

void USortingLayerModifier::ChangeSortingLayer(FGameplayTag NewSortingLayer)
{
	if (!Sprite) return;

	SortingLayer = NewSortingLayer;
	int number = GetTagLocalIndex(NewSortingLayer);
	Sprite->TranslucencySortPriority = number;
	//UE_LOG(LogKumu, Warning, TEXT("Changed Sorting Layer to %s with priority %d"), *SortingLayer.GetTagLeafName().ToString(), number);

	// Make sure render state updates so changes are visible immediately in-game
	Sprite->MarkRenderStateDirty();
}

#if WITH_EDITOR
void USortingLayerModifier::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	//UE_LOG(LogKumu, Warning, TEXT("PostEditChangeProperty"));
	Super::PostEditChangeProperty(PropertyChangedEvent);

	const FName PropertyName = PropertyChangedEvent.Property ? PropertyChangedEvent.Property->GetFName() : NAME_None;
	if (PropertyName == GET_MEMBER_NAME_CHECKED(USortingLayerModifier, SortingLayer))
	{
		//UE_LOG(LogKumu, Warning, TEXT("Sorting Layer Changed"));
		ChangeSortingLayer(SortingLayer);
	}
}
#endif
