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
	virtual void OnRegister() override;
	virtual  void OnUnregister() override;

protected:
	virtual void BeginPlay() override;
	
	virtual void BeginDrag_Implementation(const FHitResult &pointerEventData) override;
	virtual void Drag_Implementation(const FHitResult &pointerEventData) override;
	virtual void EndDrag_Implementation(const FHitResult &pointerEventData) override;
private:
	bool bDragging;
	FVector DragOffset;
	FVector LastDragLocation;
	TObjectPtr<AActor> OwnerActor;
	UPrimitiveComponent* PrimitiveComponent;
	
	FVector DragPlaneOrigin;
};