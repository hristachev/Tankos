// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Machine.h"
#include "IScorable.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "HealthComponent.h"
#include "Cannon.h"
#include "DamageTaker.h"
#include "GameStruct.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Turret.generated.h"


UCLASS()
class TANKOS_API ATurret : public AMachine
{
	GENERATED_BODY()
	
public:	
	ATurret();

	
protected:
	
	virtual void BeginPlay() override;
	void Targeting();
	void Destroyed();
	void RotateToPlayer();
	bool IsPlayerInRange();
	bool CanFire();
	//virtual void ScoreAdd(FScoreData ScoreData);
	/*void AddScore();
	void Died(float score);*/

	UPROPERTY()
	class APawn* PlayerPawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
	float TargetingRange = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
	float TargetingSpeed = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
	float TargetingRate = 0.005f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
	float Accurency = 30.0f;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	AProjectile* projectile;

	const FString BodyMeshPath = "StaticMesh'/Game/CSC/Meshes/SM_CSC_Tower1.SM_CSC_Tower1'";

	const FString TurretMeshPath = "StaticMesh'/Game/CSC/Meshes/SM_CSC_Gun1.SM_CSC_Gun1'";
};
