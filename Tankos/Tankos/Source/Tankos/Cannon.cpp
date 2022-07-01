// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"
#include "TankPawn.h"
#include "InputCoreTypes.h"
#include "GameFramework/PlayerController.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "TimerManager.h"
#include "Engine/Engine.h"


// Sets default values
ACannon::ACannon()
{
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* sceeneCpm = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = sceeneCpm;

	CannonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CannonMesh"));
	CannonMesh->SetupAttachment(RootComponent);

	ProjectileSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("ProjectileSpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(CannonMesh);
}

void ACannon::Fire()
{
	if (!bCanFire || EmptyAmmo())
	{
		return;
	}

	bCanFire = false;

	if (CannonType == ECannonType::FireProjectile)
	{
		--BulletValue;
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Fire Projectile\n Bullets: %d"), BulletValue));
	}
	else
	{
		--BulletValue;
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Fire Trace\n Bullets: %d"), BulletValue));
	}
	GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &ACannon::Reload, ReloadTime, false);
}

void ACannon::FireSpecial()
{
	if (!bCanFire || EmptyAmmo())
	{
		return;
	}

	bCanFire = false;
	
	while (valueOfShots != 0 )
	{
		valueOfShots--;
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Shots left: %d"), valueOfShots));
	}
	--BulletValue;
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Fire \n Bullets: %d"), BulletValue));
	GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &ACannon::Reload, ReloadTime, false);
}

void ACannon::Reload()
{
	bCanFire = true;
	valueOfShots = 2;
}

void ACannon::BulletReload()
{
	bCanFire = true;
	BulletValue = 10;
}

bool ACannon::EmptyAmmo()
{
	if (BulletValue == 0)
	{
		bCanFire = false;
		return true;
	}
	return false;
}
