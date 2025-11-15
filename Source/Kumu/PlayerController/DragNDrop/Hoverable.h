// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Hoverable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UHoverable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class KUMU_API IHoverable
{
	GENERATED_BODY()

public:

#if PLATFORM_WINDOWS || PLATFORM_MAC || PLATFORM_LINUX
	virtual void HandleBeginCursorOver(UPrimitiveComponent* touchedComponent) =0;
	virtual void HandleEndCursorOver(UPrimitiveComponent* touchedComponent) =0;
#endif

#if PLATFORM_ANDROID || PLATFORM_IOS	
	virtual void HandleBeginCursorOver(ETouchIndex::Type touchIndex, UPrimitiveComponent* touchedComponent) =0;
	virtual void HandleEndCursorOver(ETouchIndex::Type touchIndex, UPrimitiveComponent* touchedComponent) =0;
#endif
	
	
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
};
