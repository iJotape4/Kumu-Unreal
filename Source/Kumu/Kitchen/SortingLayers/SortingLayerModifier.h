// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include  "PaperSpriteComponent.h"
#include "SortingLayers.h"
#include "SortingLayerModifier.generated.h"

	
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class KUMU_API USortingLayerModifier : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USortingLayerModifier();

	virtual void OnRegister() override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sorting Layer", meta=(BlueprintSetter="SetSortingLayer"))
	FSortingLayers SortingLayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UPaperSpriteComponent* Sprite;

protected:
	UFUNCTION(BlueprintSetter)
	void SetSortingLayer(FSortingLayers NewSortingLayer);
	
	void ChangeSortingLayer(FSortingLayers NewSortingLayer);
	
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};