// Fill out your copyright notice in the Description page of Project Settings.


#include "PhysicsComponent.h"

TArray<FVector> UPhysicsComponent::GenerateTrajectory(FVector StartPos, FVector Velocity, float maxTime, float TimeStep, float minZValue)
{
	TArray<FVector> Trajectory;
	FVector GravityVector(0.0f, 0.0f, Gravity);

	for (float time = 0; time < maxTime; time += TimeStep)
	{
		FVector position = StartPos + Velocity * time + GravityVector * time * time / 2;
		if (position.Z <= minZValue)
			break;

		Trajectory.Add(position);
	}
	return Trajectory;
}
