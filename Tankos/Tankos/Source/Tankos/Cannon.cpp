// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"
#include "TankPawn.h"
#include "Projectile.h"
#include "GameFramework/PlayerController.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/SceneComponent.h"
#include "DrawDebugHelpers.h"
#include "TimerManager.h"
#include "Engine/Engine.h"


void ACannon::BeginPlay()
{
	Super::BeginPlay();
	
	FullBulletValue = 20.0f;
	BulletValue = FullBulletValue;
	RangeBulletValue = 1.0f;
	PreviousBulletValue = RangeBulletValue;
}
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
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Fire Projectile\n Bullets: %f"), BulletValue));
		
		AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation());
		if (projectile)
		{
			projectile->Start();
		}
	}
	else
	{
		--BulletValue;
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Fire Trace\n Bullets: %f"), BulletValue));

		FHitResult hitResult;
		FCollisionQueryParams traceParams = FCollisionQueryParams(FName(TEXT("FireTrace")), true, this);
		traceParams.bTraceComplex = true;
		traceParams.bReturnPhysicalMaterial = false;

		FVector StartTrace = ProjectileSpawnPoint->GetComponentLocation();
		FVector EndTrace = StartTrace + ProjectileSpawnPoint->GetForwardVector() * FireRange;

		if (GetWorld()->LineTraceSingleByChannel(hitResult, StartTrace, EndTrace, ECollisionChannel::ECC_Visibility, traceParams))
		{
			DrawDebugLine(GetWorld(), StartTrace, hitResult.Location, FColor::Red, false, 0.5f, 0, 10);
			if (hitResult.GetActor())
			{
				hitResult.GetActor()->Destroy();
			}
		}
		else
		{
			DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Purple, false, 0.5f, 0, 5);
		}
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
	
	while (valueOfShots != 0.0f )
	{
		valueOfShots--;
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Shots left: %f"), valueOfShots));
	}
	--BulletValue;
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Fire \n Bullets: %f"), BulletValue));
	GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &ACannon::Reload, ReloadTime, false);
}

void ACannon::Reload()
{
	bCanFire = true;
	valueOfShots = 2.0f;
}

void ACannon::BulletReload()
{
	bCanFire = true;
	BulletValue = FullBulletValue;
}

bool ACannon::EmptyAmmo()
{
	if (BulletValue == 0.0f)
	{
		bCanFire = false;
		return true;
	}
	return false;
}

void ACannon::UpdateBullet(float PickAmmo)
{
	BulletValue += PickAmmo;
	BulletValue = FMath::Clamp(BulletValue, 0.0, PickAmmo);
	PreviousBulletValue = RangeBulletValue;
	RangeBulletValue = BulletValue / FullBulletValue;
}

