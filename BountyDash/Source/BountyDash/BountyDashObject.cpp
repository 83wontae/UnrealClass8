// Fill out your copyright notice in the Description page of Project Settings.


#include "BountyDashObject.h"
#include "Components/SphereComponent.h"
#include "BountyDashGameModeBase.h"

ABountyDashObject::ABountyDashObject()
{
	PrimaryActorTick.bCanEverTick = true;
	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	check(Collider);

	RootComponent = Collider;
	Collider->SetCollisionProfileName("OverlapAllDynamic");

	OnActorBeginOverlap.AddDynamic(this, &ABountyDashObject::MyOnActorBeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &ABountyDashObject::MyOnActorEndOverlap);
}

void ABountyDashObject::BeginPlay()
{
	Super::BeginPlay();
}

void ABountyDashObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float gameSpeed = GetCustomGameMode<ABountyDashGameModeBase>(GetWorld())->GetInvGameSpeed();

	AddActorWorldOffset(FVector(gameSpeed, 0.0f, 0.0f));

	if (GetActorLocation().X < KillPoint)
	{
		Destroy();
	}
}

void ABountyDashObject::SetKillPoint(float point)
{
	KillPoint = point;
}

float ABountyDashObject::GetKillPoint()
{
	return KillPoint;
}

void ABountyDashObject::MyOnActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
}

void ABountyDashObject::MyOnActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
}
