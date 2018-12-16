// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "PatrolRouteComponent.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto BlackboardComponent = OwnerComp.GetBlackboardComponent();
	auto AIController = OwnerComp.GetAIOwner();
	auto ControlledCharacter = AIController->GetPawn();
	auto PatrolRouteComponent = ControlledCharacter->FindComponentByClass<UPatrolRouteComponent>();

	if (!ensure(PatrolRouteComponent)) { return EBTNodeResult::Failed; }

	auto PatrolPoints = PatrolRouteComponent->GetPatrolPoints();

	if (PatrolPoints.Num() <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("A guard is missing patrol points."));
		return EBTNodeResult::Failed;
	}

	auto CurrentIndex = BlackboardComponent->GetValueAsInt(IndexKey.SelectedKeyName);
	auto Waypoint = PatrolPoints[CurrentIndex];
	BlackboardComponent->SetValueAsObject(WaypointKey.SelectedKeyName, Waypoint);

	auto NextIndex = (CurrentIndex + 1) % PatrolPoints.Num();
	BlackboardComponent->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);

	return EBTNodeResult::Succeeded;
}
