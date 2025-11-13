// Fill out your copyright notice in the Description page of Project Settings.


#include "PointerPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

APointerPlayerController::APointerPlayerController()
{
#if PLATFORM_WINDOWS || PLATFORM_MAC || PLATFORM_LINUX
	// configure the controller
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
	DefaultMouseCursor = EMouseCursor::Default;
#endif

#if PLATFORM_ANDROID || PLATFORM_IOS
	bEnableTouchEvents = true;
	bEnableTouchOverEvents = true;
#endif
}

void APointerPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	// Only set up input on local player controllers
	if (IsLocalPlayerController())
	{
		// Add Input Mapping Context
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}

		// Set up action bindings
		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
		{
			// Setup mouse input events
			EnhancedInputComponent->BindAction(PrimaryPointerAction, ETriggerEvent::Started, this, &APointerPlayerController::OnPointerDown);
			EnhancedInputComponent->BindAction(PrimaryPointerAction, ETriggerEvent::Triggered, this, &APointerPlayerController::OnPointerHold);
			EnhancedInputComponent->BindAction(PrimaryPointerAction, ETriggerEvent::Completed, this, &APointerPlayerController::OnPointerUp);
			EnhancedInputComponent->BindAction(PrimaryPointerAction, ETriggerEvent::Canceled, this, &APointerPlayerController::OnPointerUp);

			// Setup touch input events
			EnhancedInputComponent->BindAction(PrimaryTouchAction, ETriggerEvent::Started, this, &APointerPlayerController::OnPointerDown);
			EnhancedInputComponent->BindAction(PrimaryTouchAction, ETriggerEvent::Triggered, this, &APointerPlayerController::OnTouchTriggered);
			EnhancedInputComponent->BindAction(PrimaryTouchAction, ETriggerEvent::Completed, this, &APointerPlayerController::OnTouchReleased);
			EnhancedInputComponent->BindAction(PrimaryTouchAction, ETriggerEvent::Canceled, this, &APointerPlayerController::OnTouchReleased);
		}
		else
		{
			UE_LOG(LogPlayerController, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
		}
	}
}
