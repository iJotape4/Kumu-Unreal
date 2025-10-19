// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MousePlayerController.generated.h"

struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
/**
 * 
 */
UCLASS(Abstract)
class KUMU_API AMousePlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, Category="Input|Input Mappings")
	TArray<UInputMappingContext*> DefaultMappingContexts;

	UPROPERTY(EditAnywhere, Category ="Input")
	UInputAction* IA_PrimaryPointer_PressAction;

	UPROPERTY(EditAnywhere, Category ="Input")
	UInputAction* SecondaryPointerAction;

	UPROPERTY(EditAnywhere, Category ="Input")
	UInputAction* ThirdPointerAction;
	
public:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
protected:
	virtual void OnPointerDown(const FInputActionValue& Value) PURE_VIRTUAL(AMousePlayerController::OnLeftMouseButtonDown,);
	virtual void OnPointerUp(const FInputActionValue& Value) PURE_VIRTUAL(AMousePlayerController::OnLeftMouseButtonUp,);
};