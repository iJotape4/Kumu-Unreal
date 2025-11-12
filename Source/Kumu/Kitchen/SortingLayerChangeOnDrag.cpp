// Fill out your copyright notice in the Description page of Project Settings.


#include "SortingLayerChangeOnDrag.h"

#include "ComponentUtilsMacros.h"


// Sets default values for this component's properties
USortingLayerChangeOnDrag::USortingLayerChangeOnDrag()
{
	
}

void USortingLayerChangeOnDrag::OnComponentCreated()
{
	Super::OnComponentCreated();
	SETUP_REQUIRED_COMPONENT_FROM_OWNER(dragView);
}

// Called when the game starts
void USortingLayerChangeOnDrag::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USortingLayerChangeOnDrag::TickComponent(float DeltaTime, ELevelTick TickType,
                                              FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

