// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankController.generated.h"


UCLASS()
class TANKOS_API ATankController : public APlayerController
{
	GENERATED_BODY()

public:
	ATankController();
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetPawn(APawn* InPawn) override;
	FVector GetMousePos() { return MousePos; }
	bool getIsGamepadeValid() { return bIsGamepadeValid; }
	UPROPERTY()
	class ATankPawn* TankPawn;
	UPROPERTY()
	FVector MousePos = FVector::Zero();
protected:
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
	UFUNCTION()
	void ChangeCannon();
	UFUNCTION()
	void RotateTurret(float Value);
private:
	bool bIsGamepadeValid = false;
};
