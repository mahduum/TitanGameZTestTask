// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_PerformJumps.h"
#include "AIController.h"
#include "AgentBase_V2.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "VisualLogger/VisualLogger.h"

UBTTask_PerformJumps::UBTTask_PerformJumps(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NodeName = "Perform Jumps";
	INIT_TASK_NODE_NOTIFY_FLAGS();
	
	BlackboardKey.AddBoolFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_PerformJumps, BlackboardKey));
}

EBTNodeResult::Type UBTTask_PerformJumps::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const AAIController* AIController = OwnerComp.GetAIOwner();

	if (AIController == nullptr || AIController->GetPawn() == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	FBTaskPerformJumpsMemory* MyMemory = CastInstanceNodeMemory<FBTaskPerformJumpsMemory>(NodeMemory);

	if(AAgentBase_V2* Agent = Cast<AAgentBase_V2>(AIController->GetPawn()))
	{
		if(!Agent->CanJump())
		{
			return EBTNodeResult::Failed;
		}

		MyMemory->NodeResult = EBTNodeResult::InProgress;
		Agent->JumpOnce();
		
		UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
		if(ensure(BlackboardComp))
		{
			if(MyMemory->BBObserverDelegateHandle.IsValid())
			{
				UE_VLOG(AIController, LogBehaviorTree, Warning, TEXT("UBTTask_PerformJumps::ExecuteTask \'%s\' Old BBObserverDelegateHandle is still valid! Removing old Observer."), *GetNodeName());
				BlackboardComp->UnregisterObserver(BlackboardKey.GetSelectedKeyID(), MyMemory->BBObserverDelegateHandle);
			}
			
			MyMemory->BBObserverDelegateHandle =
				BlackboardComp->RegisterObserver(BlackboardKey.GetSelectedKeyID(),
					this,
					FOnBlackboardChangeNotification::CreateUObject(this, &UBTTask_PerformJumps::OnBlackboardValueChange));
		}
	}
	
	return EBTNodeResult::InProgress;
}

EBTNodeResult::Type UBTTask_PerformJumps::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return Super::AbortTask(OwnerComp, NodeMemory);
}

void UBTTask_PerformJumps::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
	EBTNodeResult::Type TaskResult)
{
	FBTaskPerformJumpsMemory* MyMemory = CastInstanceNodeMemory<FBTaskPerformJumpsMemory>(NodeMemory);
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (ensure(BlackboardComp) && MyMemory->BBObserverDelegateHandle.IsValid())
	{
		BlackboardComp->UnregisterObserver(BlackboardKey.GetSelectedKeyID(), MyMemory->BBObserverDelegateHandle);
	}

	MyMemory->BBObserverDelegateHandle.Reset();
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);
}

void UBTTask_PerformJumps::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	APawn* JumpingPawn = OwnerComp.GetAIOwner()->GetPawn();
	const FBTaskPerformJumpsMemory* MyMemory = CastInstanceNodeMemory<FBTaskPerformJumpsMemory>(NodeMemory);

	if (AAgentBase_V2* Agent = Cast<AAgentBase_V2>(JumpingPawn))
	{
		if (!Agent->CanJump())
		{
			return;
		}
		
		if (MyMemory->NodeResult == EBTNodeResult::InProgress)
		{
			Agent->JumpOnce();
		}
		else
		{
			FinishLatentTask(OwnerComp, MyMemory->NodeResult);
		}
	}
	else
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}
}

EBlackboardNotificationResult UBTTask_PerformJumps::OnBlackboardValueChange(const UBlackboardComponent& Blackboard,
	FBlackboard::FKey ChangedKeyID)
{
	const UBehaviorTreeComponent* BehaviorComp = Cast<UBehaviorTreeComponent>(Blackboard.GetBrainComponent());
	if (BehaviorComp == nullptr)
	{
		return EBlackboardNotificationResult::RemoveObserver;
	}
	
	uint8* RawMemory = BehaviorComp->GetNodeMemory(this, BehaviorComp->FindInstanceContainingNode(this));
	FBTaskPerformJumpsMemory* MyMemory = CastInstanceNodeMemory<FBTaskPerformJumpsMemory>(RawMemory);
	
	const EBTTaskStatus::Type TaskStatus = BehaviorComp->GetTaskStatus(this);
	if (TaskStatus != EBTTaskStatus::Active)
	{
		UE_VLOG(BehaviorComp->GetAIOwner(), LogBehaviorTree, Error, TEXT("BT Perform Jumps\'%s\' task observing BB entry while no longer being active!"), *GetNodeName());
		MyMemory->BBObserverDelegateHandle.Reset();
	
		return EBlackboardNotificationResult::RemoveObserver;
	}
	
	if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Bool::StaticClass())
	{
		if (const bool KeyValue = Blackboard.GetValue<UBlackboardKeyType_Bool>(ChangedKeyID); KeyValue == false)
		{
			MyMemory->NodeResult = EBTNodeResult::Succeeded;
			return EBlackboardNotificationResult::RemoveObserver;
		}
	}
	
	return EBlackboardNotificationResult::ContinueObserving;
}

uint16 UBTTask_PerformJumps::GetInstanceMemorySize() const
{
	return sizeof(FBTaskPerformJumpsMemory);
}

FString UBTTask_PerformJumps::GetStaticDescription() const
{
	const FString KeyDesc = BlackboardKey.SelectedKeyName.ToString();
	return FString::Printf(TEXT("%s: %s"), *Super::GetStaticDescription(), *KeyDesc);
}
