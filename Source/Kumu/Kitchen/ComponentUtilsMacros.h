// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"
#include <type_traits>

// -----------------------------------------------------------------------------
// Header-only template implementation
// This is the small utility that searches the Owner for a component of type T,
// and if missing creates it, registers it, and attaches it when it's a USceneComponent.
// -----------------------------------------------------------------------------
namespace ComponentUtilsMacros
{
    template <class T>
    inline void SetUpRequiredComponent(AActor* Owner, T*& RequiredComponent)
    {
        if (!Owner)
        {
            return;
        }

        if (T* Found = Owner->FindComponentByClass<T>())
        {
            RequiredComponent = Found;
            UE_LOG(LogTemp, Verbose, TEXT("ComponentUtilsMacros: found existing component %s on actor %s"), *T::StaticClass()->GetName(), *Owner->GetName());
            return;
        }

        // Create the component with the actor as the outer so it gets GC with the actor.
        FName BaseName = T::StaticClass()->GetFName();
        T* NewComp = NewObject<T>(Owner, T::StaticClass(), BaseName, RF_Transactional);
        if (!NewComp)
        {
            UE_LOG(LogTemp, Error, TEXT("ComponentUtilsMacros: failed to create component %s for actor %s"), *T::StaticClass()->GetName(), *Owner->GetName());
            return;
        }

        Owner->AddInstanceComponent(NewComp);
        NewComp->RegisterComponent();

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
        UE_LOG(LogTemp, Verbose, TEXT("ComponentUtilsMacros: created and attached component %s on actor %s"), *T::StaticClass()->GetName(), *Owner->GetName());
    }
} // namespace ComponentUtilsHeader

// -----------------------------------------------------------------------------
// Macros that call the header-only helper. They infer the component type from
// the Member pointer (decltype(Member) must be a raw pointer type, e.g. UMyComp*).
// -----------------------------------------------------------------------------

// Primary macro (type inferred from Member pointer)
// Usage:
//   // header
//   UPROPERTY()
//   UDragView* DragView = nullptr;
//
//   // .cpp (where `DragView` is visible):
//   SETUP_REQUIRED_COMPONENT(this, DragView);
//
// This will call:
//   ComponentUtils::SetUpRequiredComponent<UDragView>(this, DragView);
//
// Requirements & caveats:
// - `Member` must be a pointer type (e.g. UDragView*). If it's a wrapper (TWeakObjectPtr, TSharedPtr,
//   TSubclassOf, etc.) the macro will not deduce the intended inner type.
// - The `OwnerPtr` must be a valid AActor* (or nullptr; ComponentUtils guards for null owners).
// - Prefer calling in BeginPlay/OnRegister/InitializeComponent — after actor and root component exist.
// -----------------------------------------------------------------------------
#define SETUP_REQUIRED_COMPONENT(OwnerPtr, Member) \
    ComponentUtilsMacros::SetUpRequiredComponent<typename std::remove_pointer<decltype(Member)>::type>(OwnerPtr, Member)

// Convenience: use `this` as the owner. Good for AActor-derived classes.
// Example: SETUP_REQUIRED_COMPONENT_SELF(DragView);
#define SETUP_REQUIRED_COMPONENT_SELF(Member) \
    SETUP_REQUIRED_COMPONENT(this, Member)

// Convenience: use GetOwner() as the owner. Good for UActorComponent-derived classes.
// Example (inside a UActorComponent): SETUP_REQUIRED_COMPONENT_FROM_OWNER(DragView);
#define SETUP_REQUIRED_COMPONENT_FROM_OWNER(Member) \
    SETUP_REQUIRED_COMPONENT(GetOwner(), Member)

// -----------------------------------------------------------------------------
// Quick usage examples
// -----------------------------------------------------------------------------
// AActor example:
//   // header
//   UPROPERTY()
//   UDragView* DragView = nullptr;
//
//   // .cpp
//   void AMyActor::BeginPlay()
//   {
//       Super::BeginPlay();
//       SETUP_REQUIRED_COMPONENT_SELF(DragView); // ensures DragView exists and is registered
//   }
//
// UActorComponent example:
//   // header
//   UPROPERTY()
//   UDragView* DragView = nullptr;
//
//   // .cpp
//   void UMyComp::InitializeComponent()
//   {
//       Super::InitializeComponent();
//       SETUP_REQUIRED_COMPONENT_FROM_OWNER(DragView); // uses GetOwner() internally
//   }
//
// Implementation note:
// ComponentUtils::SetUpRequiredComponent<T> will search the Owner for an existing component of type T.
// If none is found it will create one with NewObject<T>(Owner, ...), call Owner->AddInstanceComponent, and
// register/attach it (if it is a USceneComponent). If you see linker errors for a specific T, add an
// explicit instantiation in ComponentUtils.cpp (we already add one for UDragView as an example).
// -----------------------------------------------------------------------------
