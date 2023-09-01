// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_PerformJumps.generated.h"

struct FBTaskPerformJumpsMemory
{
	FDelegateHandle BBObserverDelegateHandle;
	EBTNodeResult::Type NodeResult;
};
/**
 * 
 */
UCLASS()
class TESTTASK_API UBTTask_PerformJumps : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_PerformJumps(const FObjectInitializer& ObjectInitializer);
	//virtual void PostInitProperties() override;//define some initial data if relevant
	//virtual void PostLoad() override;
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	EBlackboardNotificationResult OnBlackboardValueChange(const UBlackboardComponent& Blackboard, FBlackboard::FKey ChangedKeyID);

	virtual uint16 GetInstanceMemorySize() const override;

	virtual FString GetStaticDescription() const override;
};
