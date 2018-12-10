// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ChooseNextWaypoint.generated.h"

/**
 * 
 */
UCLASS()
class TESTINGGROUNDS_API UChooseNextWaypoint : public UBTTaskNode
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	struct FBlackboardKeySelector IndexKey;

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	struct FBlackboardKeySelector WaypointKey;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	void SetNextWaypointIndex(const int32 &CurrentIndex, UBlackboardComponent * BlackboardComponent);
private:
	TArray<AActor*> PatrolPoints = TArray<AActor*>();

	void GetPatrolPoints(UBehaviorTreeComponent & OwnerComp);

	int32 SetWaypoint(UBlackboardComponent * BlackboardComponent);
};
