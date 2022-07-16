// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Machine.h"
#include "Cannon.h"
#include "GameStruct.h"
#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "HealthComponent.h"
#include "Components/BoxComponent.h"
#include "DamageTaker.h"
#include "GameFramework/Pawn.h"
#include "TankPawn.generated.h"

class UArrowComponent;
UCLASS()
class TANKOS_API ATankPawn : public AMachine
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Components", Meta = (MakeEditWidget = true))
	TArray<class ATargetPoint*> PatrollingPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Components")
	float MovementAccurency = 30.0f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
	float MoveSpeed = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
	float RotationSpeed = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
	float InterpolationKey = 0.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
	float RotationInterpolationKey = 0.1f;

	UPROPERTY()
	class ATankController* TankController;

private: 
	/*FVector AxisValue;*/
	float ForwardAxisValue = 0.0f;
	float RightAxisValue = 0.0f;
	float CurrentRotateAxisValue = 0.0f;
	float RotateRightAxisValue = 0.0f;
	float RotationTurretValue = 0.0f;
	float CurrentRotationTurretValue = 0.0f;

	bool bUseMainCannon = true;
public:
	// Sets default values for this pawn's properties
	ATankPawn();

	void MoveForward(float Value);
	void MoveRight(float Value);
	void RotateRight(float Value);

	void SetPatrollingPoints(TArray<ATargetPoint*> NewPatrollingPoints);

	UFUNCTION()
	float GetRotationTurretValue() { return RotationTurretValue; }

	UFUNCTION()
	FVector GetTurretForwardVector();

	UFUNCTION()
	void RotateTurretTo(FVector TargetPosition);

	UFUNCTION()
	void RotateTurretRight(float Value);

	FVector GetEyesPosition();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Turret|Component")
	TSubclassOf<ACannon> SecondCannonClass;

	/*TSubclassOf<ACannon> GetCannonClass() { return CannonClass; }*/

	TSubclassOf<ACannon> GetSecondCannonClass() { return SecondCannonClass; }

	ACannon* GetCannon() { return Cannon; }

	
	void FireSpecial();
	void BulletReload();
	
	void ChangeCannon();
	uint8 GetBulletValue() { return Cannon->GetBulletValue(); }

	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;

	UFUNCTION()
	TArray<FVector> GetPatrollingPoints();

	UFUNCTION()
	float GetAccurency() { return MovementAccurency; }
};
