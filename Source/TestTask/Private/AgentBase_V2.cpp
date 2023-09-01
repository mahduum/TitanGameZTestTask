// Fill out your copyright notice in the Description page of Project Settings.


#include "AgentBase_V2.h"

#include "AIController.h"
#include "GameFramework/FloatingPawnMovement.h"
// Sets default values
AAgentBase_V2::AAgentBase_V2()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));
	SetRootComponent(DefaultRoot);
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComp->SetupAttachment(RootComponent);
	MeshComp->SetConstraintMode(EDOFMode::SixDOF);
	MeshComp->SetEnableGravity(false);
	MeshComp->SetSimulatePhysics(false);
	MeshComp->SetGenerateOverlapEvents(true);
	MeshComp->OnComponentHit.AddDynamic(this, &AAgentBase_V2::OnMeshHit);

	PawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(FName("Floating Pawn Movement"));
	PawnMovement->SetAutoActivate(true);
	PawnMovement->SetUpdateNavAgentWithOwnersCollisions(false);

	JumpForce = 500.0f;

	IsGrounded = true;
}

// Called when the game starts or when spawned
void AAgentBase_V2::BeginPlay()
{
	if(AAIController* AI = Cast<AAIController>(this->GetController()); ActiveBehaviorTree != nullptr)
	{
		AI->RunBehaviorTree(ActiveBehaviorTree);
	}
	
	Super::BeginPlay();
}

// Called every frame
void AAgentBase_V2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAgentBase_V2::JumpOnce()
{
	IsGrounded = false;
	MeshComp->SetEnableGravity(true);
	MeshComp->SetSimulatePhysics(true);
	MeshComp->AddImpulse(FVector(0, 0, JumpForce));
}

void AAgentBase_V2::LandJump()
{
	MeshComp->SetEnableGravity(false);
	MeshComp->SetSimulatePhysics(false);
	MeshComp->K2_AttachToComponent(DefaultRoot, EName::None, EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, true);
	IsGrounded = true;
}

void AAgentBase_V2::OnMeshHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->ActorHasTag(FName("Ground")))
	{
		LandJump();
	}
}

