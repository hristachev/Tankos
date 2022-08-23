// Fill out your copyright notice in the Description page of Project Settings.


#include "TankFactory.h"
#include "TimerManager.h"
#include "MapLoader.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"


ATankFactory::ATankFactory()
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* sceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = sceneComp;

	BuildingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BuildingMesh"));
	BuildingMesh->SetupAttachment(sceneComp);

	DestroyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DestroyMesh"));
	DestroyMesh->SetAutoActivate(false);
	DestroyMesh->SetupAttachment(sceneComp);

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	BoxCollider->SetupAttachment(BuildingMesh);

	TankSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("TankSpawnPoint"));
	TankSpawnPoint->AttachToComponent(sceneComp, FAttachmentTransformRules::KeepRelativeTransform);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	HealthComponent->OnHealthChanged.AddUObject(this, &ATankFactory::DamageTaked);
	HealthComponent->OnDie.AddUObject(this, &ATankFactory::Die);

	ATankSpawn = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioTankSpawnEffect"));
	ATankSpawn->SetAutoActivate(false);

	PTankSpawn = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("TankSpawnEffect"));
	PTankSpawn->SetAutoActivate(false);
	PTankSpawn->SetupAttachment(TankSpawnPoint);

	ADestroyFactory = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioDestroyFactoryEffect"));
	ADestroyFactory->SetAutoActivate(false);

	PDestroyFactory = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("DestroyFactoryEffect"));
	PDestroyFactory->SetAutoActivate(false);
	PDestroyFactory->SetupAttachment(sceneComp);

}

void ATankFactory::BeginPlay()
{
	Super::BeginPlay();

	if (MapLoader)
	{
		MapLoader->SetIsActivated(false);
	}

	if (Teleport)
	{
		Teleport->SetIsActivated(false);
	}
	if (SecondTeleport)
	{
		SecondTeleport->SetIsActivated(false);
	}

	if (bIsCanSpawn)
	{
		FTimerHandle SpawnTimer;
		GetWorld()->GetTimerManager().SetTimer(SpawnTimer, this, &ATankFactory::SpawnTank, SpawnTankRate, true, SpawnTankRate);
	}
}

void ATankFactory::SpawnTank()
{
	if (!bIsCanSpawn)
		return;

	ATankSpawn->Play();

	FTransform spawnTransform(TankSpawnPoint->GetComponentRotation(), TankSpawnPoint->GetComponentLocation(), FVector(1));
	ATankPawn* newTank = GetWorld()->SpawnActorDeferred<ATankPawn>(SpawnTankClass, spawnTransform, this, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	newTank->SetPatrollingPoints(TankWayPoints);

	
	PTankSpawn->ActivateSystem();

	UGameplayStatics::FinishSpawningActor(newTank, spawnTransform);

}

void ATankFactory::TakeDamage(FDamageData DamageData)
{
	HealthComponent->TakeDamage(DamageData);
}

void ATankFactory::Die()
{
	if (MapLoader)
	{
		MapLoader->SetIsActivated(true); 
	}

	if (Teleport)
	{
		Teleport->SetIsActivated(true);
		Teleport->DestroyGate();
	}
	if (SecondTeleport)
	{
		SecondTeleport->SetIsActivated(true);
		SecondTeleport->DestroyGate();
	}

	ADestroyFactory->Play();
	PDestroyFactory->ActivateSystem();

	bIsCanSpawn = false;

	BuildingMesh->SetVisibility(false);
	DestroyMesh->SetActive(true);
}

void ATankFactory::DamageTaked(float DamageValue)
{
	UE_LOG(LogTemp, Warning, TEXT("Factory %s take Damage: %f, Health: %f"), *GetName(), DamageValue, HealthComponent->GetHealth());
}
