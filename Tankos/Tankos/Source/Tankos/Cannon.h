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
	bool IsReadyToFire() { return bCanFire; }

	float GetBulletValue() { return BulletValue; }
	void UpdateBullet(float PickAmmo);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	class UStaticMeshComponent* CannonMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	class UArrowComponent* ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	ECannonType CannonType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	float ReloadTime = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component|Bullets")
	float FullBulletValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component|Bullets")
	float BulletValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component|Bullets")
	float RangeBulletValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component|Bullets")
	float PreviousBulletValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component|Bullets")
	float valueOfShots = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component|Bullets")
	float FireRange = 100.0f;

	UPROPERTY()
	class ATankController* TankControl;
	
	UPROPERTY()
	class ATankPawn* TankPawn;

	FTimerHandle ReloadTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	TSubclassOf<class AProjectile> ProjectileClass;
	

private:
	bool bCanFire = true;
};
