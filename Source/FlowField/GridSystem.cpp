// Fill out your copyright notice in the Description page of Project Settings.


#include "GridSystem.h"
#include "Math.h"
#include "Components/SceneComponent.h"



// Sets default values
AGridSystem::AGridSystem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateAbstractDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	
	GridSizeWorld = FVector2D(500, 500);
	TileSize = 50;
}


// Called when the game starts or when spawned
void AGridSystem::BeginPlay()
{
	Super::BeginPlay();
	FVector GridLocation = GetActorLocation();
	//UE_LOG(LogTemp, Warning, TEXT("BeginPlay"));
	GenerateMapDataFromWorld();
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
	
	//FString dave = "Dave";



	for (int i = 0; i < GridTileNumberX; i++)
	{
		int x = GridTileNumberX;
		//UE_LOG(LogTemp, Warning, TEXT("X %d"), i);
		for (int  j = 0; j < GridTileNumberY; j++)
		{
			int Y = GridTileNumberY;
			GetTilePosition(i, j);
			//UE_LOG(LogTemp, Warning, TEXT("123142"));
			//UE_LOG(LogTemp, Warning, TEXT("Y %d"), j);
		
		}
	}
}
//FVector
 void AGridSystem::GetTilePosition(int i, int j)
{
	FVector vec1 = Root->GetRightVector();
	UE_LOG(LogTemp, Warning, TEXT("X location is %f"), vec1.X);
	float x = i * (TileSize * 2.0);
	UE_LOG(LogTemp, Warning, TEXT("MyCharacter's Health is %f"), x);
	//float x = x->ToFloat(i);
	
	
	FVector vec2 = Root->GetForwardVector();
	UE_LOG(LogTemp, Warning, TEXT("Y location is %f"), vec2.Y);

}