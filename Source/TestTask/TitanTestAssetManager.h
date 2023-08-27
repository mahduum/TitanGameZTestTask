// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "TitanTestAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class TESTTASK_API UTitanTestAssetManager : public UAssetManager
{
	GENERATED_BODY()

	virtual void StartInitialLoading() override;
};
