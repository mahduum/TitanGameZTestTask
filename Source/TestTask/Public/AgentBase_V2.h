// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/Pawn.h"
#include "AgentBase_V2.generated.h"


class UFloatingPawnMovement;

UCLASS()
class TESTTASK_API AAgentBase_V2 : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAgentBase_V2();

protected:

	UPROPERTY(BlueprintReadOnly)
	USceneComponent* DefaultRoot;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Appearence")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Movement")
	UFloatingPawnMovement* PawnMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
	UBehaviorTree* ActiveBehaviorTree;

	UPROPERTY(BlueprintReadWrite, Category="Physics")
	bool IsGrounded;
	
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Physics")
	float JumpForce;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Jobs")//assign to building but maybe change to load the whole tree
	void AssignTo(AActor* Actor);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Jobs")
	void AbortAssignment();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Jobs")
	void ChangeColor();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Jobs")
	void ActivateSound(bool bNewIsActive);

	UFUNCTION(BlueprintCallable, Category="Physics")
	bool CanJump() const { return IsGrounded; }

	UFUNCTION(BlueprintCallable, Category="Physics")
	void JumpOnce();

	UFUNCTION(BlueprintCallable, Category="Physics")
	void LandJump();

private:

	UFUNCTION()
	void OnMeshHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			   FVector NormalImpulse, const FHitResult& Hit);
};
