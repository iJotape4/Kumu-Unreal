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
		PrimitiveComponent->OnBeginCursorOver.AddDynamic(this, &UDropView::HandleBeginCursorOver);
		PrimitiveComponent->OnEndCursorOver.AddDynamic(this, &UDropView::HandleEndCursorOver);
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

void UDropView::HandleBeginCursorOver(UPrimitiveComponent* touchedComponent)
{
	if (!CachedPlayerController || !CachedPlayerController->IsDragging()) return;

	if (UActorComponent* draggedActor =  CachedPlayerController->GetDraggedActor().Get())
	{
		UE_LOG(LogTemp, Warning, TEXT("Begin Cursor Over"));
	}
}

void UDropView::HandleEndCursorOver(UPrimitiveComponent* touchedComponent)
{
	if (!CachedPlayerController || !CachedPlayerController->IsDragging()) return;

	if (UActorComponent* draggedActor =  CachedPlayerController->GetDraggedActor().Get())
	{
		UE_LOG(LogTemp, Warning, TEXT("End Cursor Over"));
	}
}
#if PLATFORM_ANDROID || PLATFORM_IOS
void UDropView::HandleEndCursorOver(ETouchIndex::Type touchIndex, UPrimitiveComponent* touchedComponent)
{
	HandleEndCursorOver(touchedComponent);
}

void UDropView::HandleBeginCursorOver(ETouchIndex::Type touchIndex, UPrimitiveComponent* touchedComponent)
{
	HandleBeginCursorOver(touchedComponent);
}
#endif
