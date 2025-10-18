// Fill out your copyright notice in the Description page of Project Settings.


#include "MousePlayerController.h"

void AMousePlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetShowMouseCursor(true);
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
}