// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "DamageTaker.h"
#include "Machine.h"
#include "GameStruct.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "TimerManager.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	
	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = SceneComponent;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	ProjectileMesh->SetupAttachment(SceneComponent);
	ProjectileMesh->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnMeshOverlapBegin);
	ProjectileMesh->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
}

//void AProjectile::ScoreAdd(FScoreData ScoreData)
//{
//	float scoreAdd = ScoreData.scoreValue;
//	currentScore += scoreAdd;
//
//	if () //??
//	{
//		if (OnDestroy.IsBound())
//			OnDestroy.Broadcast(scoreAdd);
//	}
//	else
//	{
//		if (OnAddScore.IsBound())
//			OnAddScore.Broadcast();
//	}
//}

//void AProjectile::BeginPlay()
//{
//	/*startScore = 0.0f;
//	currentScore = startScore;
//	FScoreData score;
//	score.scoreValue = startScore;*/
//}

void AProjectile::Start()
{
	GetWorld()->GetTimerManager().SetTimer(MoveTimer, this, &AProjectile::Move, MoveRate, true, MoveRate);
}

void AProjectile::Move()
{
	FVector nextPosition = GetActorLocation() + GetActorForwardVector() * MoveSpeed * MoveRate;
	SetActorLocation(nextPosition);
}

void AProjectile::OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//UE_LOG(LogTemp, Warning, TEXT("Projectile collided with %s"), *OtherActor->GetName());
	AActor* owner = GetOwner();
	AActor* ownerByOwner = owner != nullptr ? owner->GetOwner() : nullptr;

	if (OtherActor != owner && OtherActor != ownerByOwner)
	{
		IDamageTaker* damageTakerActor = Cast<IDamageTaker>(OtherActor);
		//IIScorable* scorable = Cast<IIScorable>(OtherActor);
		if (damageTakerActor)
		{
			FDamageData damageData;
			damageData.DamageValue = Damage;
			damageData.Instigator = owner;
			damageData.DamageMaker = this;

			damageTakerActor->TakeDamage(damageData);

			
			/*FScoreData scoreData;
			scoreData.scoreValue = killingPoints;
			scoreData.ScoreInstigator = owner;
			scorable->ScoreAdd(scoreData);*/
		}
		else
		{
			
			OtherActor->Destroy();	
			
		}
		Destroy();
	}
}
