// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/Pawn.h"
#include "AgentBase.generated.h"

DECLARE_DYNAMIC_DELEGATE(FGameplayTagDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStopAllJobsDelegate);

// Bind a method to a gameplay tag.

UCLASS(Blueprintable, Abstract)
class TESTTASK_API AAgentBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAgentBase();//Initialize in 

private:

	FGameplayTagDelegate CreateAndBind(FName FunctionName);

protected:

	UPROPERTY(BlueprintReadOnly)
	USceneComponent* DefaultRoot;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Appearence")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement")
	UFloatingPawnMovement* PawnMovement;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, Category="Physics")
	bool IsGrounded;

	UPROPERTY(BlueprintReadWrite, Category="Jobs | Tags")
	FGameplayTagContainer JobTags;

	UFUNCTION(BlueprintImplementableEvent, Category="Jobs")
	void PerformJumpJob();//can be changed to "one-off" job
	
	UFUNCTION(BlueprintImplementableEvent, Category="Jobs")
	void PerformPlayAudioJob();

	UFUNCTION(BlueprintImplementableEvent, Category="Jobs")
	void PerformChangeColorJob();
	
	UFUNCTION(BlueprintCallable, Category="Jobs")
	void StopAllJobs();

	UPROPERTY(BlueprintAssignable, Category="Jobs")
	FStopAllJobsDelegate EventStopAllJobs;
	
	// Create a map to associate gameplay tags with delegate instances.
	TMap<FGameplayTag, FGameplayTagDelegate> GameplayTagToDelegateMap;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category="Jobs")
	void ScheduleJobsByTags(FGameplayTagContainer InJobTags);

	UFUNCTION(BlueprintCallable, Category="Physics")
	bool CanJump() const { return IsGrounded; }

	UFUNCTION(BlueprintNativeEvent, Category="Physics")
	void JumpOnce();//todo implement default???

};
