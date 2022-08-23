// Fill out your copyright notice in the Description page of Project Settings.


#include "TeleportActor.h"
#include "Components/PointLightComponent.h"
#include "Components/AudioComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ATeleportActor::ATeleportActor()
{
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* sceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = sceneComp;

	BasicMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Basic Mesh"));
	BasicMesh->SetupAttachment(sceneComp);

	BlockGateMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gate Mesh"));
	BlockGateMesh->SetupAttachment(sceneComp);

	ActivatedLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("ActivatedLights"));
	ActivatedLight->SetupAttachment(sceneComp);

	DeactivatedLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("DeactivatedLights"));
	DeactivatedLight->SetupAttachment(sceneComp);

	Trigger = CreateDefaultSubobject<ATeleporter>(TEXT("TriggerCollider"));
	Trigger->AttachToComponent(sceneComp, FAttachmentTransformRules::KeepRelativeTransform);

	OpenBlockGate = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioEffect"));
	OpenBlockGate->SetAutoActivate(false);
}

void ATeleportActor::SetActiveLights()
{
	ActivatedLight->SetHiddenInGame(!IsActivated);
	DeactivatedLight->SetHiddenInGame(IsActivated);
}

// Called when the game starts or when spawned
void ATeleportActor::BeginPlay()
{
	Super::BeginPlay();
	
	SetActiveLights();
}

void ATeleportActor::SetIsActivated(bool NewIsActivated)
{
	IsActivated = NewIsActivated;

	SetActiveLights();
}

void ATeleportActor::DestroyGate()
{
	if (BlockGateMesh)
	{
		BlockGateMesh->DestroyComponent();
		OpenBlockGate->Play();
	}
}
