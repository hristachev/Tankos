// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cannon.h"
#include "CoreMinimal.h"
#include "HealthComponent.h"
#include "DamageTaker.h"
#include "GameFramework/Pawn.h"
#include "Machine.generated.h"

class UStaticMeshComponent;
class ACannon;
UCLASS()
class TANKOS_API AMachine : public APawn, public IDamageTaker
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMachine();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UHealthComponent* HealthComponent;

	virtual void TakeDamage(FDamageData DamageData) override;

	void Fire();

	void SetupCannon(TSubclassOf<ACannon> NewCannonClass);

	UFUNCTION()
	void Die();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	UStaticMeshComponent* BodyMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	class UBoxComponent* BoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	class UArrowComponent* CannonSetupPoint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Turret|Component")
	TSubclassOf<ACannon> CannonClass;

	UPROPERTY()
	ACannon* Cannon;

	UFUNCTION()
	void DamageTaked(float DamageValue);
};
