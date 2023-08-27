// Fill out your copyright notice in the Description page of Project Settings.
#include "TitanTestAssetManager.h"
#include "TitanTestGameplayTags.h"

void UTitanTestAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	FTitanTestGameplayTags::InitializeGameplayTags();
}
