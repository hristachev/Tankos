// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankController.generated.h"

/**
 * 
 */
UCLASS()
class TANKOS_API ATankController : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY()
		class ATankPawn* TankPawn;
	UPROPERTY()
		FVector MousePos;
public:
	ATankController();
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetPawn(APawn* InPawn) override;
	FVector GetMousePos() { return MousePos; }
protected:
	virtual void BeginPlay() override;
	UFUNCTION()
	void MoveForward(float Value);
	UFUNCTION()
	void MoveRight(float Value);
	UFUNCTION()
	void RotateRight(float Value);
	UFUNCTION()
	void Fire();
	UFUNCTION()
	void FireSpecial();
	UFUNCTION()
	void BulletReload();
};
