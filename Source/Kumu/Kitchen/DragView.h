// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kumu/PlayerController/DragNDrop/UDraggable.h"
#include "DragView.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDragBegan, FHitResult, eventData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDragEnd, FHitResult, eventData);

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
	void SetCollisionResponsesForDragging(bool enable) const;

	virtual void BeginDrag_Implementation(const FHitResult &pointerEventData) override;
	virtual void Drag_Implementation(const FHitResult &pointerEventData) override;
	virtual void EndDrag_Implementation(const FHitResult &pointerEventData) override;
public:
	UPROPERTY(BlueprintAssignable)
	FOnDragBegan OnDragBegan;
	
	UPROPERTY(BlueprintAssignable)
	FOnDragEnd OnDragEnd;
	
private:
	bool bDragging;
	FVector DragOffset;
	FVector LastDragLocation;
	TObjectPtr<AActor> OwnerActor;
	UPrimitiveComponent* PrimitiveComponent;
	
	FVector DragPlaneOrigin;
};