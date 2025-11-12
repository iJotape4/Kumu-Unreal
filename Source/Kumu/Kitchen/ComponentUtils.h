// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"

/**
 * 
 */
class KUMU_API ComponentUtils
{
public:
	template <class T>
	static void SetUpRequiredComponent(AActor* Owner, T*& RequiredComponent)
	{
		if (!Owner) return;

		if (T* Found = Owner->FindComponentByClass<T>())
		{
			RequiredComponent = Found;
			UE_LOG(LogTemp, Warning, TEXT("Found existing component of type %s on actor %s"), *T::StaticClass()->GetName(), *Owner->GetName());
		}
		else
		{
			// Create the component with the actor as the outer so it gets garbage-collected with the actor.
			FName BaseName = T::StaticClass()->GetFName();
			T* NewComp = NewObject<T>(Owner, T::StaticClass(), BaseName, RF_Transactional);
			if (!NewComp)
			{
				UE_LOG(LogTemp, Error, TEXT("Failed to create component of type %s for actor %s"), *T::StaticClass()->GetName(), *Owner->GetName());
				return;
			}

			// Make the actor aware of this component instance so it appears in the editor/runtime component list.
			Owner->AddInstanceComponent(NewComp);

			// Register the component so it begins its lifecycle (BeginPlay/registering, ticking if enabled, etc.).
			NewComp->RegisterComponent();

			// If it's a scene component, attach it to the actor root (or set as root if none exists).
			if (USceneComponent* SceneComp = Cast<USceneComponent>(NewComp))
			{
				if (USceneComponent* RootComp = Owner->GetRootComponent())
				{
					SceneComp->AttachToComponent(RootComp, FAttachmentTransformRules::KeepRelativeTransform);
				}
				else
				{
					Owner->SetRootComponent(SceneComp);
				}
			}

			RequiredComponent = NewComp;
			UE_LOG(LogTemp, Warning, TEXT("Created and attached component of type %s on actor %s"), *T::StaticClass()->GetName(), *Owner->GetName());
		}
	}
};
