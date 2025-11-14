// Fill out your copyright notice in the Description page of Project Settings.


#include "DropView.h"

#include "Kumu.h"


// Sets default values for this component's properties
UDropView::UDropView()
{
	OwnerActor = GetOwner();
}

void UDropView::BeginPlay()
{
	Super::BeginPlay();
	
}

void UDropView::OnRegister()
{
	Super::OnRegister();

	/*
	 Drop targets must block all channels in order to work properly
	 */
	PrimitiveComponent = GetOwner()->FindComponentByClass<UPrimitiveComponent>();
	
	if (PrimitiveComponent)
	{
		PrimitiveComponent->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
		PrimitiveComponent->SetCollisionResponseToAllChannels(ECR_Block);
	}
}

void UDropView::Drop_Implementation(const FHitResult eventData)
{
	OnDropped.Broadcast(eventData);
}


