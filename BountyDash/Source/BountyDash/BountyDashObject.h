// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BountyDashObject.generated.h"

/**
 * 
 */
UCLASS()
class BOUNTYDASH_API ABountyDashObject : public AActor
{
	GENERATED_BODY()

	float KillPoint;

public:
	ABountyDashObject();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetKillPoint(float point);
	float GetKillPoint();

protected:
	UFUNCTION()
	virtual void MyOnActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	virtual void MyOnActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UPROPERTY(EditAnywhere)
	class USphereComponent* Collider;
};
