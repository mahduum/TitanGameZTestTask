// Fill out your copyright notice in the Description page of Project Settings.


#include "AgentBase.h"

#include "NativeGameplayTags.h"
UE_DEFINE_GAMEPLAY_TAG(TAG_Gameplay_Jumping_Job, "Gameplay.Job.Jump");
UE_DEFINE_GAMEPLAY_TAG(TAG_Gameplay_Playing_Audio_Job, "Gameplay.Job.Play.Audio");
UE_DEFINE_GAMEPLAY_TAG(TAG_Gameplay_Change_Color_Job, "Gameplay.Job.Change.Color");

// Sets default values
AAgentBase::AAgentBase()
{
	PrimaryActorTick.bCanEverTick = true;

	/*Bind all tags for job ability regardless whether the agent will have assigned all tags and actually be able to perform all the jobs*/
	GameplayTagToDelegateMap.Add(TAG_Gameplay_Jumping_Job, CreateAndBind(FName("PerformJumpJob")));
	GameplayTagToDelegateMap.Add(TAG_Gameplay_Playing_Audio_Job, CreateAndBind(FName("PerformPLayAudioJob")));
	GameplayTagToDelegateMap.Add(TAG_Gameplay_Change_Color_Job, CreateAndBind(FName("PerformChangeColorJob")));

	DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));
	SetRootComponent(DefaultRoot);
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComp->SetupAttachment(RootComponent);
	MeshComp->SetConstraintMode(EDOFMode::SixDOF);
	MeshComp->SetEnableGravity(false);
	MeshComp->SetSimulatePhysics(false);

	PawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(FName("Floating Pawn Movement"));
	PawnMovement->SetAutoActivate(true);

	IsGrounded = true;
}

FGameplayTagDelegate AAgentBase::CreateAndBind(FName FunctionName)
{
	FGameplayTagDelegate Delegate;
	Delegate.BindUFunction(this, FunctionName);
	return Delegate;
}

// Called when the game starts or when spawned
void AAgentBase::BeginPlay()
{
	Super::BeginPlay();
}

void AAgentBase::StopAllJobs()
{
	EventStopAllJobs.Broadcast();
}

// Called every frame
void AAgentBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AAgentBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AAgentBase::ScheduleJobsByTags(FGameplayTagContainer InJobTags)
{
	TArray<FGameplayTag> TagsArray;
	InJobTags.GetGameplayTagArray(TagsArray);
	
	for (auto Element : TagsArray)
	{
		if(JobTags.HasTag(Element))
		{
			GameplayTagToDelegateMap[Element].Execute();//this one will execute delegates defined in bps, 
		}
	}
}

void AAgentBase::JumpOnce_Implementation()
{
	
}

