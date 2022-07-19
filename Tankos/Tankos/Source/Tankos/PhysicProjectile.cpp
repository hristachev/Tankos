// Fill out your copyright notice in the Description page of Project Settings.


#include "PhysicProjectile.h"
#include "PhysicsComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"

APhysicProjectile::APhysicProjectile()
{
	PhysicsComponent = CreateDefaultSubobject<UPhysicsComponent>(TEXT("PhysicComponent"));

	TrailEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("TrailEffect"));
	TrailEffect->SetupAttachment(RootComponent);
}

void APhysicProjectile::Start()
{
	MoveVector = GetActorForwardVector() * MoveSpeedPhys;
	CurrentTrajectory = PhysicsComponent->GenerateTrajectory(GetActorLocation(), MoveVector, MaxTimeSimulation, TimeStep, 0.0f);

	if (bShowTrajectory)
	{
		for (FVector position : CurrentTrajectory)
		{
			DrawDebugSphere(GetWorld(), position, 5, 8, FColor::Purple, true, 1, 0, 2);
		}
	}
	TrajectoryPointIndex = 0;


	Super::Start();
}

void APhysicProjectile::Move()
{
	FVector currentMoveVector = CurrentTrajectory[TrajectoryPointIndex] - GetActorLocation();
	currentMoveVector.Normalize();
	FVector newLocation = GetActorLocation() + currentMoveVector * MoveSpeedPhys * MoveRate;
	SetActorLocation(newLocation);

	if (FVector::Distance(newLocation, CurrentTrajectory[TrajectoryPointIndex]) <= MovementAccurency)
	{
		TrajectoryPointIndex++;
		if (TrajectoryPointIndex >= CurrentTrajectory.Num())
		{
			if (bEnableExplode)
				Explode();

			Destroy();
		}
		else
		{
			FRotator newRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), CurrentTrajectory[TrajectoryPointIndex]);
			SetActorRotation(newRotation);
		}
	}
}

