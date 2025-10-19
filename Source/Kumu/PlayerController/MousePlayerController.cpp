// Fill out your copyright notice in the Description page of Project Settings.


#include "MousePlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"

class UInputMappingContext;


void AMousePlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetShowMouseCursor(true);
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
}

void AMousePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (IsLocalPlayerController())
	{
		// Add Input Mapping Context
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
			{
				Subsystem->AddMappingContext(CurrentContext, 0);
			}
			if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
			{
				EnhancedInputComponent->BindAction(IA_PrimaryPointer_PressAction, ETriggerEvent::Started, this, &AMousePlayerController::OnPointerDown);
				EnhancedInputComponent->BindAction(IA_PrimaryPointer_PressAction, ETriggerEvent::Completed, this, &AMousePlayerController::OnPointerUp);
			}
		}
	}
}

void AMousePlayerController::OnPointerDown(const FInputActionValue& Value)
{
}

void AMousePlayerController::OnPointerUp(const FInputActionValue& Value)
{
}
