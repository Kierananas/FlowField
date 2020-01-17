// Fill out your copyright notice in the Description page of Project Settings.


#include "GridSystem.h"
#include "Math.h"

// Sets default values
AGridSystem::AGridSystem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GridSizeWorld = FVector2D(250, 250);
	TileSize = 50;
}


// Called when the game starts or when spawned
void AGridSystem::BeginPlay()
{
	Super::BeginPlay();
	FVector GridLocation = GetActorLocation();
	UE_LOG(LogTemp, Warning, TEXT("BeginPlay"));
}

// Called every frame
void AGridSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGridSystem::GridTileNumber(int& GridTileNumberX, int& GridTileNumberY)
{
	FVector2D temp = GridSizeWorld / TileSize;

	GridTileNumberX = FMath::RoundToInt(temp.X) - 1;
	GridTileNumberY = FMath::RoundToInt(temp.Y) - 1;
}


//void AGridSystem::SetTilePosition(FVector TilePosition)
//{
	//FVector X = GridLocation - (FVector GetRightVector() const * FVector2D GridSizeWorld.X);
	//FVector Y = UScene GetForwardVector() const * FVector2D GridSizeWorld.Y
	//FVector BottomLeft = FVector X - FVector Y


//}

void AGridSystem::GenerateMapDataFromWorld()
{
	int GridTileNumberX, GridTileNumberY;
	GridTileNumber(GridTileNumberX, GridTileNumberY);

	for (int i = 0; i < GridTileNumberX; i++)
	{
		int X = GridTileNumberX;
		for (int  j = 0; j < GridTileNumberY; j++)
		{
			int Y = GridTileNumberY;
		
			UE_LOG(LogTemp, Warning, TEXT("BeginPlay"));
		
		
		}
	}
}

