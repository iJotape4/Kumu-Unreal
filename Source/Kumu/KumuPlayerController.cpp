// Copyright Epic Games, Inc. All Rights Reserved.

#include "KumuPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "KumuCharacter.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "Kumu.h"
#include "PlayerController/DragNDrop/UDraggable.h"

AKumuPlayerController::AKumuPlayerController()
{
	bIsTouch = false;
	bMoveToMouseCursor = false;

	// configure the controller
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
}

void AKumuPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
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
			EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &AKumuPlayerController::OnInputStarted);
			EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &AKumuPlayerController::OnSetDestinationTriggered);
			EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &AKumuPlayerController::OnSetDestinationReleased);
			EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &AKumuPlayerController::OnSetDestinationReleased);

			// Setup touch input events
			EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Started, this, &AKumuPlayerController::OnInputStarted);
			EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Triggered, this, &AKumuPlayerController::OnTouchTriggered);
			EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Completed, this, &AKumuPlayerController::OnTouchReleased);
			EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Canceled, this, &AKumuPlayerController::OnTouchReleased);
		}
		else
		{
			UE_LOG(LogKumu, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
		}
	}
}

void AKumuPlayerController::OnInputStarted()
{
	UE_LOG(LogKumu, Warning, TEXT("Input Started"));
	StopMovement();
}

void AKumuPlayerController::OnSetDestinationTriggered()
{
	FHitResult Hit;
	bool bHitSuccessful = false;
	
	if (bIsTouch)
		bHitSuccessful = GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_Visibility, true, Hit);
	else
		bHitSuccessful = GetHitResultUnderCursor(ECC_Visibility, true, Hit);
	

	if (!bHitSuccessful)
		return;
	
	AActor* HitActor = Hit.GetActor();
	UE_LOG( LogKumu, Warning, TEXT("Hit actor : %s"), *HitActor->GetClass()->GetName())
	if (HitActor)
	{
		TArray<UActorComponent*> DraggableComps = HitActor->GetComponentsByInterface(UDraggable::StaticClass());
		if (DraggableComps.Num() > 0)
		{
			IDraggable::Execute_BeginDrag(DraggableComps[0], Hit.ImpactPoint);
		}
	}
}

void AKumuPlayerController::OnSetDestinationReleased()
{
	UE_LOG(LogKumu, Warning, TEXT("Input Released"));

}

// Triggered every frame when the input is held down
void AKumuPlayerController::OnTouchTriggered()
{
	bIsTouch = true;
	OnSetDestinationTriggered();
}

void AKumuPlayerController::OnTouchReleased()
{
	bIsTouch = false;
	OnSetDestinationReleased();
}