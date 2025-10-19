// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kumu/PlayerController/MousePlayerController.h"
#include "ADragNDropPlayerController.generated.h"
/**
 * 
 */
UCLASS()
class KUMU_API AADragNDropPlayerController : public AMousePlayerController
{
	GENERATED_BODY()

	
public:
	virtual void BeginPlay() override;
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

protected:
	virtual void OnPointerDown(const FInputActionValue& Value) override;
	virtual void OnPointerUp(const FInputActionValue& Value) override;
	
private:
	AActor* DraggedActor;
	FVector DragPlaneOrigin;
	FVector DragPlaneNormal;
	FVector LastDragWorldLocation;
	bool bIsDragging;
	bool GetCursorWorldProjection(FVector& OutWorldLocation) const;

};