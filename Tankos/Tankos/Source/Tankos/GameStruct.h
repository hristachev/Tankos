// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameStruct.generated.h"

UENUM(BlueprintType)
enum class ECannonType : uint8
{
	FireProjectile = 0 UMETA(DisplayName = "Use Projectile"),
	FireTrace = 1 UMETA(DispplayName = "Use Trace")
};

USTRUCT()
struct FDamageData
{
	GENERATED_BODY()

	UPROPERTY()
	float DamageValue;

	UPROPERTY()
	AActor* Instigator;

	UPROPERTY()
	AActor* DamageMaker;

};

USTRUCT()
struct FScoreData
{
	GENERATED_BODY()

	UPROPERTY()
	float scoreValue;

	UPROPERTY()
	AActor* ScoreInstigator;
};

UCLASS()
class TANKOS_API UGameStruct : public UObject
{
	GENERATED_BODY()

};