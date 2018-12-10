// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TP_ThirdPerson/PatrollingGuard.h"
#include "AIController.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto BlackboardComponent = OwnerComp.GetBlackboardComponent();
	GetPatrolPoints(OwnerComp);
	
	auto CurrentIndex = SetWaypoint(BlackboardComponent);

	SetNextWaypointIndex(CurrentIndex, BlackboardComponent);

	return EBTNodeResult::Succeeded;
}

void UChooseNextWaypoint::SetNextWaypointIndex(const int32 &CurrentIndex, UBlackboardComponent * BlackboardComponent)
{
	auto NextIndex = (CurrentIndex + 1) % PatrolPoints.Num();
	BlackboardComponent->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);
}

void UChooseNextWaypoint::GetPatrolPoints(UBehaviorTreeComponent & OwnerComp)
{
	auto Owner = OwnerComp.GetAIOwner();
	auto AI = Cast<APatrollingGuard>(Owner->GetPawn());
	PatrolPoints = AI->PatrolPoints;
}

int32 UChooseNextWaypoint::SetWaypoint(UBlackboardComponent* BlackboardComponent)
{
	auto CurrentIndex = BlackboardComponent->GetValueAsInt(IndexKey.SelectedKeyName);
	auto Waypoint = PatrolPoints[CurrentIndex];
	BlackboardComponent->SetValueAsObject(WaypointKey.SelectedKeyName, Waypoint);
	return CurrentIndex;
}
