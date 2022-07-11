// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"
#include "Projectile.h"
#include "TankController.h"
#include "Engine/StaticMesh.h"
#include "UObject/UObjectGlobals.h"
#include "Kismet/KismetMathLibrary.h"
#include "Cannon.h"
#include "TimerManager.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

ATurret::ATurret()
{
	PrimaryActorTick.bCanEverTick = false;

	UStaticMesh* BodyMeshTemp = LoadObject<UStaticMesh>(this, *BodyMeshPath);
	if (BodyMeshTemp)
		BodyMesh->SetStaticMesh(BodyMeshTemp);

	UStaticMesh* TurretMeshTemp = LoadObject<UStaticMesh>(this, *TurretMeshPath);
	if (TurretMeshTemp)
		TurretMesh->SetStaticMesh(TurretMeshTemp);

	projectile = CreateDefaultSubobject<AProjectile>(TEXT("Score Component"));
	/*projectile->OnDestroy.AddUObject(this, &ATurret::Died);
	projectile->OnAddScore.AddUObject(this, &ATurret::AddScore);*/
}

void ATurret::BeginPlay()
{
	Super::BeginPlay();

	PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	FTimerHandle TargetingTimer;
	GetWorld()->GetTimerManager().SetTimer(TargetingTimer, this, &ATurret::Targeting, TargetingRate, true, TargetingRate);
}

void ATurret::Destroyed()
{
	if (Cannon)
		Cannon->Destroy();
}

void ATurret::Targeting()
{
	if (IsPlayerInRange())
	{
		RotateToPlayer();
		if (CanFire() && Cannon && Cannon->IsReadyToFire())
		{
			Fire();
		}
	}
}

void ATurret::RotateToPlayer()
{
	FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), PlayerPawn->GetActorLocation());
	FRotator TurretRotation = TurretMesh->GetComponentRotation();
	targetRotation.Pitch = TurretRotation.Pitch;
	targetRotation.Roll = TurretRotation.Roll;
	TurretMesh->SetWorldRotation(FMath::Lerp(TurretRotation, targetRotation, TargetingSpeed));
}

bool ATurret::IsPlayerInRange()
{
	return FVector::Distance(PlayerPawn->GetActorLocation(), GetActorLocation()) <= TargetingRange;
}

bool ATurret::CanFire()
{
	FVector targetingDir = TurretMesh->GetForwardVector();
	FVector dirToPlayer = PlayerPawn->GetActorLocation() - GetActorLocation();
	dirToPlayer.Normalize();

	float aimAngle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(targetingDir, dirToPlayer)));
	return aimAngle <= Accurency;
}

//void ATurret::ScoreAdd(FScoreData ScoreData)
//{
//	projectile->ScoreAdd(ScoreData);
//}

//void ATurret::AddScore()
//{
//	//UE_LOG(LogTemp, Warning, TEXT("Score: %f"), projectile->GetCurrentScore());
//}
//
//void ATurret::Died(float score)
//{
//	Destroy();
//}
