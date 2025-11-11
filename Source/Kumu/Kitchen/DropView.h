// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerController/DragNDrop/DropTarget.h"
#include "DropView.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class KUMU_API UDropView : public UActorComponent, public IDropTarget
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UDropView();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	virtual void Drop_Implementation(const FVector& WorldLocation) override;
private:
	TObjectPtr<AActor> OwnerActor;
};
