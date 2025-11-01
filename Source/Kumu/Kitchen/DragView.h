// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MaterialPropertyHelpers.h"
#include "GameFramework/Actor.h"
#include "Kumu/PlayerController/DragNDrop/UDraggable.h"
#include "DragView.generated.h"


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class KUMU_API UDragView : public UActorComponent, public IDraggable
{
	GENERATED_BODY()
	
public:	
	UDragView();
	virtual ~UDragView() override;

protected:
	virtual void BeginPlay() override;
	
	virtual void BeginDrag_Implementation(const FVector& WorldLocation) override;
	virtual void Drag_Implementation(const FVector& WorldLocation) override;
	virtual void EndDrag_Implementation() override;

private:
	bool bDragging;
	FVector DragOffset;
	FVector LastDragLocation;
	TObjectPtr<AActor> OwnerActor;
};