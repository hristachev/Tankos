// Fill out your copyright notice in the Description page of Project Settings.


#include "Machine.h"
#include "Components\StaticMeshComponent.h"
#include "Components\ArrowComponent.h"
#include "Components\BoxComponent.h"
#include "HealthComponent.h"
#include "Cannon.h"

// Sets default values
AMachine::AMachine()
{
	PrimaryActorTick.bCanEverTick = false;

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	RootComponent = BodyMesh;

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->SetupAttachment(BodyMesh);

	CannonSetupPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("CannonSetupPoint"));
	CannonSetupPoint->SetupAttachment(TurretMesh);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	BoxComponent->SetupAttachment(BodyMesh);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	HealthComponent->OnDie.AddUObject(this, &AMachine::Die);
	HealthComponent->OnHealthChanged.AddUObject(this, &AMachine::DamageTaked);
}

void AMachine::TakeDamage(FDamageData DamageData)
{
	HealthComponent->TakeDamage(DamageData);
}

void AMachine::Fire()
{
	if (Cannon)
	{
		Cannon->Fire();
	}
}

void AMachine::SetupCannon(TSubclassOf<ACannon> NewCannonClass)
{
	if (!NewCannonClass)
	{
		return;
	}
	if (Cannon)
	{
		Cannon->Destroy();
	}


	FActorSpawnParameters params;
	params.Instigator = this;
	params.Owner = this;

	Cannon = GetWorld()->SpawnActor<ACannon>(NewCannonClass, params);
	//Cannon->SetOwner(this);

	Cannon->AttachToComponent(CannonSetupPoint, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

void AMachine::BeginPlay()
{
	Super::BeginPlay();
	
	SetupCannon(CannonClass);
}

void AMachine::Die()
{
	Destroy();
}

void AMachine::DamageTaked(float DamageValue)
{
	UE_LOG(LogTemp, Warning, TEXT("Machine %s take Damage: %f, Health: %f"), *GetName(), DamageValue, HealthComponent->GetHealth());
}


