// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPawn.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "TankController.h"
#include "Kismet/KismetMathLibrary.h"
#include "Cannon.h"
#include "Components/ArrowComponent.h"
#include "HealthComponent.h"


// Sets default values
ATankPawn::ATankPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(BodyMesh);
	SpringArm->bDoCollisionTest = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

}

void ATankPawn::MoveForward(float Value)
{
	/*AxisValue.X = FMath::Clamp(Value, -1.0f, 1.0f);*/
	ForwardAxisValue = Value;
}

void ATankPawn::MoveRight(float Value)
{
	/*AxisValue.Y = FMath::Clamp(Value, -1.0f, 1.0f);*/
	RightAxisValue = Value;
}

void ATankPawn::RotateRight(float Value)
{
	RotateRightAxisValue = Value;
}

void ATankPawn::SetPatrollingPoints(TArray<ATargetPoint*> NewPatrollingPoints)
{
	PatrollingPoints = NewPatrollingPoints;
}

FVector ATankPawn::GetTurretForwardVector()
{
	return TurretMesh->GetForwardVector();
}

void ATankPawn::RotateTurretTo(FVector TargetPosition)
{
	FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetPosition);
	FRotator TurretRotation = TurretMesh->GetComponentRotation();

	targetRotation.Pitch = TurretRotation.Pitch;
	targetRotation.Roll = TurretRotation.Roll;

	TurretMesh->SetWorldRotation(FMath::Lerp(TurretRotation, targetRotation, RotationInterpolationKey));
}


void ATankPawn::RotateTurretRight(float Value)
{
	RotationTurretValue = Value;
}

FVector ATankPawn::GetEyesPosition()
{
	return CannonSetupPoint->GetComponentLocation();
}

void ATankPawn::FireSpecial()
{
	if (Cannon)
	{
		Cannon->FireSpecial();
	}
}

void ATankPawn::BulletReload()
{
	if (Cannon)
	{
		Cannon->BulletReload();
	}
}

void ATankPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	/*if (!AxisValue.IsZero())
	{
		FVector movePosition = GetActorLocation() + AxisValue * MoveSpeed * DeltaSeconds;
		SetActorLocation(movePosition, true);
	}*/

	FVector currentLocation = GetActorLocation();
	FVector forwardVector = GetActorForwardVector();
	FVector rightVector = GetActorRightVector();
	FVector movePosition = currentLocation + (forwardVector * ForwardAxisValue * MoveSpeed) + (rightVector * RightAxisValue * MoveSpeed) * DeltaSeconds;
	SetActorLocation(movePosition, true);

	//tank rotation
	CurrentRotateAxisValue = FMath::Lerp(CurrentRotateAxisValue, RotateRightAxisValue, InterpolationKey);

	//UE_LOG(LogTemp, Warning, TEXT("CurrentRightAxisValue = %f TargetRightAxisValue = % f"), CurrentRotateAxisValue, RotateRightAxisValue);

	float YawRotation = RotationSpeed * RotateRightAxisValue * DeltaSeconds;

	FRotator CurrentRotation = GetActorRotation();

	YawRotation += CurrentRotation.Yaw;
	FRotator newRotation = FRotator(0.0f, YawRotation, 0.0f);
	SetActorRotation(newRotation);

	//turret rotation
	if (TankController)
	{
		if(TankController->bShowMouseCursor && !TankController->getIsGamepadeValid())
		{
		FVector MousePos = TankController->GetMousePos();
		RotateTurretTo(MousePos);
		}
		else
		{
			CurrentRotationTurretValue = FMath::Lerp(CurrentRotationTurretValue, RotationTurretValue, RotationInterpolationKey);
			//UE_LOG(LogTemp, Warning, TEXT("CurrentRotationTurretValue = %f, RotationTurretValue = % f\n"), CurrentRotationTurretValue, RotationTurretValue);
			float turretYawRotation = 500.0f * RotationTurretValue * DeltaSeconds;
			//UE_LOG(LogTemp, Warning, TEXT("turretYawRotation = %f"), turretYawRotation);
			FRotator turretCurrentRotation = TurretMesh->GetComponentRotation();
			turretYawRotation += turretCurrentRotation.Yaw;

			FRotator turretNewRotation = FRotator(0.0f, turretYawRotation, 0.0f);

			TurretMesh->SetWorldRotation(FMath::Lerp(turretCurrentRotation, turretNewRotation, RotationInterpolationKey * 10.0f));
		}
	}
}
 
void ATankPawn::BeginPlay()
{
	Super::BeginPlay();

	SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, 0.0f));

	TankController = Cast<ATankController>(GetController());
}

TArray<FVector> ATankPawn::GetPatrollingPoints()
{
	TArray<FVector> points;
	for (ATargetPoint* point : PatrollingPoints)
	{
		points.Add(point->GetActorLocation());
	}
	return points;
}

void ATankPawn::ChangeCannon()
{
	if (bUseMainCannon)
	{
		SetupCannon(CannonClass);
		bUseMainCannon = false;
	}
	else
	{
		SetupCannon(SecondCannonClass);
		bUseMainCannon = true;
	}
}