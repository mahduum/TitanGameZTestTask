// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagAssetInterface.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "BuildingBase.generated.h"

UCLASS()
class TESTTASK_API ABuildingBase : public AActor, public IGameplayTagAssetInterface
{
	GENERATED_BODY()

public:
	ABuildingBase();

protected:
	UPROPERTY(EditAnywhere)
	USceneComponent* DefaultRoot;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComponent;

	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Assignments | Tags")
	FGameplayTagContainer AssignmentTags;

	UFUNCTION(BlueprintCallable, Category ="GameplayTags")
	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;

	UFUNCTION(BlueprintCallable, Category="GameplayTags")
	virtual bool HasMatchingGameplayTag(FGameplayTag TagToCheck) const override;
	
	UFUNCTION(BlueprintCallable, Category="GameplayTags")
	virtual bool HasAllMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const override;
	
	UFUNCTION(BlueprintCallable, Category="GameplayTags")
	virtual bool HasAnyMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const override;
};
