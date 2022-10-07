// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BountyDash.h"
#include "BountyDashObject.h"
#include "Obstacle.generated.h"

UCLASS()
class BOUNTYDASH_API AObstacle : public ABountyDashObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObstacle();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Mesh;

};
