// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "PatrolRouteComponent.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto BlackboardComponent = OwnerComp.GetBlackboardComponent();
	GetPatrolPoints(OwnerComp);
	
	auto CurrentIndex = SetWaypoint(BlackboardComponent);

	SetNextWaypointIndex(CurrentIndex, BlackboardComponent);

	return EBTNodeResult::Succeeded;
}

void UChooseNextWaypoint::GetPatrolPoints(UBehaviorTreeComponent & OwnerComp)
{
	auto AIController = OwnerComp.GetAIOwner();
	auto ControlledCharacter = AIController->GetPawn();
	auto PatrolRouteComponent = ControlledCharacter->FindComponentByClass<UPatrolRouteComponent>();

	if (!ensure(PatrolRouteComponent)) { return; }

	PatrolPoints = PatrolRouteComponent->GetPatrolPoints();
}

int32 UChooseNextWaypoint::SetWaypoint(UBlackboardComponent* BlackboardComponent)
{
	auto CurrentIndex = BlackboardComponent->GetValueAsInt(IndexKey.SelectedKeyName);
	auto Waypoint = PatrolPoints[CurrentIndex];
	BlackboardComponent->SetValueAsObject(WaypointKey.SelectedKeyName, Waypoint);
	return CurrentIndex;
}

void UChooseNextWaypoint::SetNextWaypointIndex(const int32 &CurrentIndex, UBlackboardComponent * BlackboardComponent)
{
	auto NextIndex = (CurrentIndex + 1) % PatrolPoints.Num();
	BlackboardComponent->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);
}
