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
	
	CachedPlayerController = Cast<ADragNDropController>(GetWorld()->GetFirstPlayerController());
	
	if (PrimitiveComponent)
	{
#if PLATFORM_WINDOWS || PLATFORM_MAC || PLATFORM_LINUX
		PrimitiveComponent->OnBeginCursorOver.AddDynamic(this, &UDropView::HandleBeginCursorOver);
		PrimitiveComponent->OnEndCursorOver.AddDynamic(this, &UDropView::HandleEndCursorOver);
#endif
	}
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

void UDropView::HandleBeginCursorOver_Implementation(UPrimitiveComponent* touchedComponent)
{
	if (!CachedPlayerController || !CachedPlayerController->IsDragging()) return;

	if (UActorComponent* draggedActor =  CachedPlayerController->GetDraggedActor().Get())
	{
		UE_LOG(LogTemp, Warning, TEXT("Begin Cursor Over"));
	}
}

void UDropView::HandleEndCursorOver_Implementation(UPrimitiveComponent* touchedComponent)
{
	if (!CachedPlayerController || !CachedPlayerController->IsDragging()) return;

	if (UActorComponent* draggedActor =  CachedPlayerController->GetDraggedActor().Get())
	{
		UE_LOG(LogTemp, Warning, TEXT("End Cursor Over"));
	}
}