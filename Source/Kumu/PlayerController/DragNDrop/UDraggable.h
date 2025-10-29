// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UDraggable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDraggable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class KUMU_API IDraggable
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Drag")
	void BeginDrag(const FVector &WorldLocation);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Drag")
	void Drag(const FVector &WorldLocation, const FVector &Delta);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Drag")
	void EndDrag();
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
};
