// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleClass.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AObstacleClass::AObstacleClass()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateAbstractDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	ObstacleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ObstacleMesh"));
	ObstacleMesh->AttachTo(Root);

}

// Called when the game starts or when spawned
void AObstacleClass::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AObstacleClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}