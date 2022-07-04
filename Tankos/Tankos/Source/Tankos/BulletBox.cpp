// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletBox.h"
#include "TankPawn.h"
#include "Cannon.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

ABulletBox::ABulletBox()
{
	USceneComponent* BulletBoxSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = BulletBoxSceneComponent;

	BulletBoxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AmmoMesh"));
	BulletBoxMesh->SetupAttachment(BulletBoxSceneComponent);
	BulletBoxMesh->OnComponentBeginOverlap.AddDynamic(this, &ABulletBox::OnMeshOverlapBegin);
	BulletBoxMesh->SetCollisionProfileName(FName("OverlapAll"));
	BulletBoxMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BulletBoxMesh->SetGenerateOverlapEvents(true);
}

void ABulletBox::OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Enter To ONMOB")));
	if ((OtherActor != nullptr) && (OtherActor != this))
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("ENTER TO 1 IF")));
		TankPawn = Cast<ATankPawn>(OtherActor);

		if (TankPawn && TankPawn->GetBulletValue() < 20.0f) 
		{
			Cannon->UpdateBullet(BulletAmmoValue);
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Add Ammo")));
			Destroy();
		}
	}
}
