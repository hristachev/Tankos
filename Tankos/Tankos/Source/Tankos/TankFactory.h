// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TankPawn.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/AudioComponent.h"
#include "Engine/TargetPoint.h"
#include "GameFramework/Actor.h"
#include "DamageTaker.h"
#include "TankFactory.generated.h"

class UParticleSystemComponent;
class UAudioComponent;
class UStaticMeshComponent;

UCLASS()
class TANKOS_API ATankFactory : public AActor, public IDamageTaker
{
	GENERATED_BODY()
	
public:	
	ATankFactory();

	UFUNCTION()
		virtual void TakeDamage(FDamageData DamageData);

protected:
	virtual void BeginPlay() override;

	void SpawnTank();

	UFUNCTION()
	void Die();

	UFUNCTION()
	void DamageTaked(float DamageValue);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	UStaticMeshComponent* BuildingMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	UStaticMeshComponent* DestroyMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	class UBoxComponent* BoxCollider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	class UHealthComponent* HealthComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	class UArrowComponent* TankSpawnPoint;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Parameters")
	TSubclassOf<class ATankPawn> SpawnTankClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Parameters")
	float SpawnTankRate = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Parameters")
	TArray<class ATargetPoint*> TankWayPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MapLoader")
	class AMapLoader* MapLoader;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	UAudioComponent* ATankSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	UParticleSystemComponent* PTankSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	UAudioComponent* ADestroyFactory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	UParticleSystemComponent* PDestroyFactory;

};
