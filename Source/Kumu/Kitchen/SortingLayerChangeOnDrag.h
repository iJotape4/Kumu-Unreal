// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DragView.h"
#include "Components/ActorComponent.h"
#include "SortingLayerChangeOnDrag.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class KUMU_API USortingLayerChangeOnDrag : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USortingLayerChangeOnDrag();
	virtual void OnComponentCreated() override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UDragView* dragView;
};
