// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Cannon.h"
#include "TankPawn.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletBox.generated.h"

UCLASS()
class TANKOS_API ABulletBox : public AActor
{
	GENERATED_BODY()
public:	
	ABulletBox();

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	UStaticMeshComponent* BulletBoxMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	float BulletAmmoValue = 5.0f;

	UPROPERTY()
	class ACannon* Cannon;

	UPROPERTY()
	class ATankPawn* TankPawn;

	UFUNCTION()
	void OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
