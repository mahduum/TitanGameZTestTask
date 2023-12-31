﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "TestTask/Public/BuildingBase.h"


// Sets default values
ABuildingBase::ABuildingBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Default Root"));
	DefaultRoot->Mobility = EComponentMobility::Static;
	SetRootComponent(DefaultRoot);
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Presentation Mesh"));
	MeshComponent->SetupAttachment(RootComponent);
	MeshComponent->Mobility = EComponentMobility::Static;
}

// Called when the game starts or when spawned
void ABuildingBase::BeginPlay()
{
	Super::BeginPlay();
}

void ABuildingBase::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
	TagContainer.Reset();
	TagContainer.AppendTags(AssignmentTags);
}

bool ABuildingBase::HasMatchingGameplayTag(FGameplayTag TagToCheck) const
{
	return AssignmentTags.HasTag(TagToCheck);
}

bool ABuildingBase::HasAllMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const
{
	return AssignmentTags.HasAll(TagContainer);
}

bool ABuildingBase::HasAnyMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const
{
	return AssignmentTags.HasAny(TagContainer);
}

