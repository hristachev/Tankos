// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Turret.h"
#include "CoreMinimal.h"
#include "IScorable.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TANKOS_API AProjectile : public AActor
{
	GENERATED_BODY()

	/*DECLARE_EVENT_OneParam(AProjectile, FOnDestroy, float);
	DECLARE_EVENT(AProjectile, FOnAddScore);*/
	
public:	
	AProjectile();

	/*FOnDestroy OnDestroy;
	FOnAddScore OnAddScore;*/

	/*virtual void ScoreAdd(FScoreData ScoreData);*/
	//virtual void BeginPlay() override;

	//float GetCurrentScore() { return currentScore; }

	virtual void Start();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	bool bEnableExplode = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	float MoveSpeed = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	float MoveRate = 0.01f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	float Damage = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	float PushForce = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement params")
	float ExplodeRadius = 50.0f;

	void Explode();

	void DamageHit(IDamageTaker* damageTakerActor, AActor* owner);

	void PhysicPush(AActor* otherActor, UPrimitiveComponent* mesh);

	FTimerHandle MoveTimer;
	virtual void Move();

	UFUNCTION()
	void OnMeshOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/*UPROPERTY()
	float currentScore;

	UPROPERTY()
	float startScore;

	UPROPERTY()
	float killingPoints = 1.0f;*/

	UPROPERTY()
	ATurret* turret;
	
};
