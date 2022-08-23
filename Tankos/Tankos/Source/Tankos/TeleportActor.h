// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Teleporter.h"
#include "GameFramework/Actor.h"
#include "TeleportActor.generated.h"

class UStaticMeshComponent;
class UPointLightComponent;

UCLASS()
class TANKOS_API ATeleportActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ATeleportActor();

protected:
	void SetActiveLights();
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* BasicMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* BlockGateMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class ATeleporter* Trigger;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UPointLightComponent* ActivatedLight;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UPointLightComponent* DeactivatedLight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	class UAudioComponent* OpenBlockGate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teleport parameters")
	bool IsActivated = false;

public:	
	void SetIsActivated(bool NewIsActivated);
	void DestroyGate();
};
