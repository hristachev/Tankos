// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TankController.h"
#include "GameFramework/Actor.h"
#include "GameStruct.h"
#include "Cannon.generated.h"

UCLASS()
class TANKOS_API ACannon : public AActor
{
	GENERATED_BODY()

public:

	ACannon();

	void Fire();
	void FireSpecial();
	void Reload();
	void BulletReload();
	bool EmptyAmmo();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	class UStaticMeshComponent* CannonMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	class UArrowComponent* ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	ECannonType CannonType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	float ReloadTime = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component|Bullets")
	uint8 BulletValue = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component|Bullets")
	uint8 valueOfShots = 2;

	UPROPERTY()
	class ATankController* TankControl;

	FTimerHandle ReloadTimer;
	

private:
	bool bCanFire = true;
};
