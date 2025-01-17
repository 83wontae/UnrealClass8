// Fill out your copyright notice in the Description page of Project Settings.


#include "HybridSphere.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/TextRenderComponent.h"

// Sets default values
AHybridSphere::AHybridSphere()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("OverlapSphere"));
	RootComponent = Sphere;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->AttachTo(Sphere);

	Particles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particles"));
	Particles->AttachTo(Mesh);

	Text = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Text"));
	Text->AttachTo(Mesh);

	OnActorBeginOverlap.AddDynamic(this, &AHybridSphere::MyOnBeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &AHybridSphere::MyOnEndOverlap);
}

// Called when the game starts or when spawned
void AHybridSphere::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHybridSphere::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHybridSphere::MyOnBeginOverlap_Implementation(AActor* OverlappedActor, AActor* OtherActor)
{
	FString outputString;
	outputString = "Hello From C++!";
	Text->SetText(FText::FromString(outputString));
}

void AHybridSphere::MyOnEndOverlap_Implementation(AActor* OverlappedActor, AActor* OtherActor)
{
	Text->SetText(NSLOCTEXT("AnyNs", "Any", "Goodbye From C++"));
}

