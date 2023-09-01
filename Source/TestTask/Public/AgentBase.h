// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/Pawn.h"
#include "AgentBase.generated.h"

DECLARE_DYNAMIC_DELEGATE(FGameplayTagDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStopAllJobsDelegate);

UCLASS(Blueprintable, Abstract)
class TESTTASK_API AAgentBase : public APawn
{
	GENERATED_BODY()

public:
	AAgentBase();

private:
	FGameplayTagDelegate CreateAndBind(FName FunctionName);

protected:

	UPROPERTY(BlueprintReadOnly)
	USceneComponent* DefaultRoot;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Appearence")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement")
	UFloatingPawnMovement* PawnMovement;
	
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, Category="Physics")
	bool IsGrounded;

	UPROPERTY(BlueprintReadWrite, Category="Jobs | Tags")
	FGameplayTagContainer JobTags;

	UFUNCTION(BlueprintImplementableEvent, Category="Jobs")
	void PerformJumpJob();
	
	UFUNCTION(BlueprintImplementableEvent, Category="Jobs")
	void PerformPlayAudioJob();

	UFUNCTION(BlueprintImplementableEvent, Category="Jobs")
	void PerformChangeColorJob();
	
	UFUNCTION(BlueprintCallable, Category="Jobs")
	void StopAllJobs();

	UPROPERTY(BlueprintAssignable, Category="Jobs")
	FStopAllJobsDelegate EventStopAllJobs;

	TMap<FGameplayTag, FGameplayTagDelegate> GameplayTagToDelegateMap;

public:
	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category="Jobs")
	void ScheduleJobsByTags(FGameplayTagContainer InJobTags);

	UFUNCTION(BlueprintCallable, Category="Physics")
	bool CanJump() const { return IsGrounded; }
};
