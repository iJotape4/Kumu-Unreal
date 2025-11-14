// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerController/DragNDrop/DragNDropController.h"
#include "PlayerController/DragNDrop/DropTarget.h"
#include "PlayerController/DragNDrop/Hoverable.h"
#include "DropView.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDropped, FHitResult, eventData);


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class KUMU_API UDropView : public UActorComponent, public IDropTarget, public IHoverable
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UDropView();

protected:
	virtual void BeginPlay() override;

	virtual  void OnRegister() override;
	
	virtual void Drop_Implementation(const FHitResult eventData) override;

	virtual void HandleBeginCursorOver_Implementation(UPrimitiveComponent* touchedComponent) override;
	
	virtual void HandleEndCursorOver_Implementation(UPrimitiveComponent* touchedComponent) override;

public:
	UPROPERTY(BlueprintAssignable)
	FOnDropped OnDropped;
private:
	TObjectPtr<AActor> OwnerActor;
	UPrimitiveComponent* PrimitiveComponent;
	
	UPROPERTY(Transient)
	ADragNDropController* CachedPlayerController;
};