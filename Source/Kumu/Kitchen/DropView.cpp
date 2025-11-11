// Fill out your copyright notice in the Description page of Project Settings.


#include "DropView.h"

#include "Kumu.h"


// Sets default values for this component's properties
UDropView::UDropView()
{
	OwnerActor = GetOwner();
}


// Called when the game starts
void UDropView::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UDropView::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UDropView::Drop_Implementation(const FVector& WorldLocation)
{
	UE_LOG(LogKumu, Warning, TEXT("Dropped at Location: %s"), *WorldLocation.ToString());
	//OwnerActor->SetActorLocation(WorldLocation);
}


