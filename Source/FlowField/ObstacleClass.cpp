// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleClass.h"

// Sets default values
AObstacleClass::AObstacleClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateAbstractDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	GroundType = 4;
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

