// Fill out your copyright notice in the Description page of Project Settings.


#include "Teleporter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/ArrowComponent.h"
#include "TankPawn.h"

ATeleporter::ATeleporter()
{
	USceneComponent* sceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = sceneComp;

	TankTeleportPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("TankTeleportPoint"));
	TankTeleportPoint->AttachToComponent(sceneComp, FAttachmentTransformRules::KeepRelativeTransform);

	OnActorBeginOverlap.AddDynamic(this, &ATeleporter::EnterToTeleporter);
	OnActorEndOverlap.AddDynamic(this, &ATeleporter::ExitTeleporter);
	bIsTeleporting = false;
}

void ATeleporter::BeginPlay()
{
	Super::BeginPlay();
}

void ATeleporter::EnterToTeleporter(AActor* overlappedActor, AActor* otherActor)
{
	if (otherActor && otherActor != this)
	{
		if (otherTeleport)
		{
			ATankPawn* Tank = Cast<ATankPawn>(otherActor);
			if (Tank && !otherTeleport->bIsTeleporting)
			{
				bIsTeleporting = true;
				Tank->SetActorRotation(otherTeleport->GetActorRotation());
				Tank->GetController()->SetControlRotation(Tank->GetActorRotation());
				Tank->SetActorLocation(otherTeleport->TankTeleportPoint->GetComponentLocation());
			}
		}
	}

}

void ATeleporter::ExitTeleporter(AActor* overlappedActor, AActor* otherActor)
{
	if (otherActor && otherActor != this)
	{
		if (otherTeleport && !bIsTeleporting)
		{
			otherTeleport->bIsTeleporting = false;
		}
	}
}
