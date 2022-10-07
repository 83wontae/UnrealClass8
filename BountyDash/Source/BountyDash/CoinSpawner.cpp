// Fill out your copyright notice in the Description page of Project Settings.


#include "CoinSpawner.h"
#include "EngineUtils.h"
#include "Floor.h"
#include "Engine/TargetPoint.h"
#include "Components/SphereComponent.h"
#include "Coin.h"

ACoinSpawner::ACoinSpawner()
{
	PrimaryActorTick.bCanEverTick = true;

	//Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	//RootComponent = Root;

	MaxSetCoins = 5;
	MinSetCoins = 3;
	CoinSetTimeInterval = 4.0f;
	CoinTimeInterval = 0.5f;
	MovermentTImeInterval = 1.0f;
}

void ACoinSpawner::BeginPlay()
{
	Super::BeginPlay();

	for (TActorIterator<ATargetPoint> TargetIter(GetWorld()); TargetIter; ++TargetIter)
	{
		SpawnTransforms.Add(*TargetIter);
	}

	for (TActorIterator<AFloor> FloorIter(GetWorld()); FloorIter; ++FloorIter)
	{
		if (FloorIter->GetWorld() == GetWorld())
		{
			KillPoint = FloorIter->GetKillPoint();
			SpawnPoint = FloorIter->GetSpawnPoint();
		}
	}

	FTimerManager& worldTimeManager = GetWorld()->GetTimerManager();

	worldTimeManager.SetTimer(CoinSetTimerHandle, this, &ACoinSpawner::SpawnCoinSet, CoinSetTimeInterval, false);
	worldTimeManager.SetTimer(SpawnMoveTimerHandle, this, &ACoinSpawner::MoveSpawner, MovermentTImeInterval, true);
}

void ACoinSpawner::SpawnCoin()
{
	FActorSpawnParameters spawnParams;

	FTransform coinTransform = SpawnTransforms[TargetLoc]->GetTransform();

	coinTransform.SetLocation(FVector(SpawnPoint, coinTransform.GetLocation().Y, coinTransform.GetLocation().Z));

	ACoin* spawnedCoin = GetWorld()->SpawnActor<ACoin>(CoinObject, coinTransform, spawnParams);

	if (spawnedCoin)
	{
		USphereComponent* coinSphere = Cast<USphereComponent>(spawnedCoin->GetComponentByClass(USphereComponent::StaticClass()));

		if (coinSphere)
		{
			float offset = coinSphere->GetUnscaledSphereRadius();
			spawnedCoin->AddActorLocalOffset(FVector(0.0f, 0.0f, offset));
		}

		NumCoinsToSpawn--;
	}

	if (NumCoinsToSpawn <= 0)
	{
		FTimerManager& worldTimeManager = GetWorld()->GetTimerManager();

		worldTimeManager.SetTimer(CoinSetTimerHandle, this, &ACoinSpawner::SpawnCoinSet, CoinSetTimeInterval, false);
		worldTimeManager.ClearTimer(CoinTimerHandle);
	}
}

void ACoinSpawner::SpawnCoinSet()
{
	NumCoinsToSpawn = FMath::RandRange(MinSetCoins, MaxSetCoins);

	FTimerManager& worldTimeManager = GetWorld()->GetTimerManager();

	worldTimeManager.ClearTimer(CoinSetTimerHandle);

	worldTimeManager.SetTimer(CoinTimerHandle, this, &ACoinSpawner::SpawnCoin, CoinTimeInterval, true);
}

void ACoinSpawner::MoveSpawner()
{
	TargetLoc = FMath::Rand() % SpawnTransforms.Num();
}
