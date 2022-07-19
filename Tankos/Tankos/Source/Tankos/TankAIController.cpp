// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "TankPawn.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Pawn.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	
	Initialize();
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!TankPawn)
		Initialize();
	if (!TankPawn)
		return;

	TankPawn->MoveForward(1);

	float RotationValue = GetRotationValue();
	TankPawn->RotateRight(RotationValue);

	Targeting();
}

float ATankAIController::GetRotationValue()
{
	FVector currentPoint = PatrollingPath[CurrentPatrollingIndex];
	FVector pawnLocation = TankPawn->GetActorLocation();
	float dist = FVector::Distance(currentPoint, pawnLocation);
	if ( dist <= MovementAccurency)
	{
		CurrentPatrollingIndex++;
		if (CurrentPatrollingIndex >= PatrollingPath.Num())
		{
			CurrentPatrollingIndex = 0;
		}
	}
	

	FVector moveDirection = currentPoint - pawnLocation;
	moveDirection.Normalize();
	FVector forwardDirection = TankPawn->GetActorForwardVector();
	FVector rightDirection = TankPawn->GetActorRightVector();

	//DrawDebugLine(GetWorld(), pawnLocation, currentPoint, FColor::Green, false, 0.1f, 0, 5);

	float forwardAngle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(forwardDirection, moveDirection)));

	float rightAngle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(rightDirection, moveDirection)));

	float RotationValue = 1;
	
	if (rightAngle > 90)
	{
		RotationValue = -RotationValue;
	}

	return RotationValue;
}

void ATankAIController::Targeting()
{
	if (!PlayerPawn)
		return;
	
	if (IsPlayerRange())
		RotateToPlayer();
	if (CanFire() && IsPlayerRange())
		Fire();
}

void ATankAIController::RotateToPlayer()
{
	if (IsPlayerRange())
		TankPawn->RotateTurretTo(PlayerPawn->GetActorLocation());
}

bool ATankAIController::IsPlayerRange()
{
	return FVector::Distance(TankPawn->GetActorLocation(), PlayerPawn->GetActorLocation()) <= TargetingRange;
}

bool ATankAIController::CanFire()
{
	if (!IsPlayerSeen()) 
	{
		return false;
	}
	FVector targetingDir = TankPawn->GetTurretForwardVector();
	FVector dirToPlayer = PlayerPawn->GetActorLocation() - TankPawn->GetActorLocation();
	dirToPlayer.Normalize();
	float aimAngle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(targetingDir, dirToPlayer)));
	
	return aimAngle <= Accurency;
}

void ATankAIController::Fire()
{
	TankPawn->Fire();
}

bool ATankAIController::IsPlayerSeen()
{
	if (!PlayerPawn)
		Initialize();

	FVector playerPos = PlayerPawn->GetActorLocation();
	FVector eyesPos = TankPawn->GetEyesPosition();

	FHitResult HitResult;

	FCollisionQueryParams traceParams = FCollisionQueryParams(FName(TEXT("FireTrace")), true, this);
	traceParams.bTraceComplex = true;
	traceParams.AddIgnoredActor(TankPawn);
	traceParams.bReturnPhysicalMaterial = false;

	if (GetWorld()->LineTraceSingleByChannel(HitResult, eyesPos, playerPos, ECollisionChannel::ECC_Visibility, traceParams))
	{
		if (HitResult.GetActor())
		{
			DrawDebugLine(GetWorld(), eyesPos, HitResult.Location, FColor::Cyan, false, 0.5f, 0, 10);
			return HitResult.GetActor() == PlayerPawn;
		}
	}
	DrawDebugLine(GetWorld(), eyesPos, playerPos, FColor::Purple, false, 0.5f, 0, 10);
	return false;
}

void ATankAIController::Initialize()
{
	TankPawn = Cast<ATankPawn>(GetPawn());

	if (!TankPawn)
		return;

	PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	FVector pawnLocation = TankPawn->GetActorLocation();
	MovementAccurency = TankPawn->GetAccurency();
	TArray<FVector> points = TankPawn->GetPatrollingPoints();

	for (FVector point : points)
	{
		PatrollingPath.Add(point);
	}
	CurrentPatrollingIndex = 0;
}
