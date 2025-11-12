// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DragView.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "SortingLayers/SortingLayerModifier.h"
#include "SortingLayerChangeOnDrag.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class KUMU_API USortingLayerChangeOnDrag : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USortingLayerChangeOnDrag();
	virtual void OnRegister() override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual  void BeginDestroy() override;

	UFUNCTION()
	void HandleDragBegan(FHitResult pointerEventData);

	UFUNCTION()
	void HandleDragEnd(FHitResult pointerEventData);

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UDragView* dragView;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USortingLayerModifier* SortingLayerModifier;

protected:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	FGameplayTag InitialSortingLayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	FGameplayTag DraggedSortingLayer=FGameplayTag::RequestGameplayTag(FName("SortingLayers.7_Dragged"));
};