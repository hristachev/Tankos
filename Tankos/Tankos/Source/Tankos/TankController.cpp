// Fill out your copyright notice in the Description page of Project Settings.


#include "TankController.h"
#include "TankPawn.h"

ATankController::ATankController()
{
	bShowMouseCursor = true;
}

void ATankController::SetupInputComponent() 
{
	Super::SetupInputComponent();

	InputComponent->BindAxis(TEXT("MoveForward"), this, &ATankController::MoveForward);
	InputComponent->BindAxis(TEXT("MoveRight"), this, &ATankController::MoveRight);
	InputComponent->BindAxis(TEXT("RotateRight"), this, &ATankController::RotateRight);
	InputComponent->BindAxis(TEXT("RotateTurret"), this, &ATankController::RotateTurret);
	InputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Pressed, this, &ATankController::Fire);
	InputComponent->BindAction(TEXT("FireSpecial"), EInputEvent::IE_Pressed, this, &ATankController::FireSpecial);
	InputComponent->BindAction(TEXT("Reload"), EInputEvent::IE_Pressed, this, &ATankController::BulletReload);
	InputComponent->BindAction(TEXT("ChangeCannon"), EInputEvent::IE_Pressed, this, &ATankController::ChangeCannon);
}

void ATankController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector mouseDirection;
	DeprojectMousePositionToWorld(MousePos, mouseDirection);
	if (TankPawn)
	{
		FVector pawnPos = TankPawn->GetActorLocation();
		MousePos.Z = pawnPos.Z;
		FVector dir = MousePos - pawnPos;
		dir.Normalize();
		MousePos = pawnPos + dir * 1000.0f;
		//DrawDebugLine(GetWorld(), pawnPos, MousePos, FColor::Green, false, 0.1f, 0, 5);

		//simple auto show mouse change
		if (TankPawn->GetRotationTurretValue() < 0.004f && TankPawn->GetRotationTurretValue() >= 0.0f)
		{
			bShowMouseCursor = true;
			bIsGamepadeValid = false;
		}
		else
		{
			bShowMouseCursor = false;
			bIsGamepadeValid = true;
		}
	}
}


void ATankController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	TankPawn = Cast<ATankPawn>(InPawn);
}

void ATankController::MoveForward(float Value)
{
	if(TankPawn)
		TankPawn->MoveForward(Value);
}

void ATankController::MoveRight(float Value)
{
	if(TankPawn)
		TankPawn->MoveRight(Value);
}

void ATankController::RotateRight(float Value)
{
	if (TankPawn)
		TankPawn->RotateRight(Value);
}

void ATankController::Fire()
{
	if (TankPawn)
		TankPawn->Fire();
}

void ATankController::FireSpecial()
{
	if (TankPawn)
		TankPawn->FireSpecial();
}

void ATankController::BulletReload()
{
	ACannon* cannon = TankPawn->GetCannon();
	if (cannon)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, FString::Printf(TEXT("Reload")));
		cannon->BulletReload();
	}
}

void ATankController::ChangeCannon()
{
	if (TankPawn)
	{
		TankPawn->ChangeCannon();
	}
}

void ATankController::RotateTurret(float Value)
{
	if (TankPawn)
	{
		TankPawn->RotateTurretRight(Value);
	}
}
