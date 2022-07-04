// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Cannon.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankPawn.generated.h"


class UStaticMeshComponent;
class ACannon;
class UArrowComponent;
UCLASS()
class TANKOS_API ATankPawn : public APawn
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* BodyMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UCameraComponent* Camera;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Turret|Component")
	UArrowComponent* CannonSetupPoint;

	
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

	bool bUseMainCannon = true;
public:
	// Sets default values for this pawn's properties
	ATankPawn();

	void MoveForward(float Value);
	void MoveRight(float Value);
	void RotateRight(float Value);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Turret|Component")
	TSubclassOf<ACannon> CannonClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Turret|Component")
	TSubclassOf<ACannon> SecondCannonClass;

	TSubclassOf<ACannon> GetCannonClass() { return CannonClass; }

	TSubclassOf<ACannon> GetSecondCannonClass() { return SecondCannonClass; }

	UPROPERTY()
	ACannon* Cannon;

	ACannon* GetCannon() { return Cannon; }

	void Fire();
	void FireSpecial();
	void BulletReload();
	void SetupCannon(TSubclassOf<ACannon> NewCannonClass);
	void ChangeCannon();
	uint8 GetBulletValue() { return Cannon->GetBulletValue(); }

	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
};
