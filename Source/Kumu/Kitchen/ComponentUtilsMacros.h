// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ComponentUtils.h"
#include <type_traits>

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
    ComponentUtils::SetUpRequiredComponent<typename std::remove_pointer<decltype(Member)>::type>(OwnerPtr, Member)

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
