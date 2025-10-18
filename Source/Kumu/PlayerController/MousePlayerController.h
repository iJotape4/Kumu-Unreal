// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MousePlayerController.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class KUMU_API AMousePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

protected:
	virtual void OnLeftMouseButtonDown() PURE_VIRTUAL(AMousePlayerController::OnLeftMouseButtonDown,);
	virtual void OnLeftMouseButtonUp() PURE_VIRTUAL(AMousePlayerController::OnLeftMouseButtonUp,);
	
	virtual void OnRightMouseButtonDown() PURE_VIRTUAL(AMousePlayerController::OnRightMouseButtonDown,);
	virtual void OnRightMouseButtonUp() PURE_VIRTUAL(AMousePlayerController::OnRightMouseButtonUp,);

	virtual  void OnMiddleMouseButtonDown() PURE_VIRTUAL(AMousePlayerController::OnMiddleMouseButtonDown,);
	virtual void OnMiddleMouseButtonUp() PURE_VIRTUAL(AMousePlayerController::OnMiddleMouseButtonUp,);
};
