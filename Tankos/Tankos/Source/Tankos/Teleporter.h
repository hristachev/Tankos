// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "GameFramework/Actor.h"
#include "Teleporter.generated.h"

/**
 * 
 */
UCLASS()
class TANKOS_API ATeleporter : public ATriggerBox
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	ATeleporter();

	UFUNCTION()
	void EnterToTeleporter(class AActor* overlappedActor, class AActor* otherActor);

	UFUNCTION()
	void ExitTeleporter(class AActor* overlappedActor, class AActor* otherActor);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	class UArrowComponent* TankTeleportPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teleporter")
	class ATeleporter* otherTeleport;

	UPROPERTY()
		bool bIsTeleporting;
};
