// Fill out your copyright notice in the Description page of Project Settings.


#include "GridSystem.h"
#include "Math.h"
#include "Components/SceneComponent.h"
#include "Engine/World.h"
#include "Engine/EngineTypes.h"
#include "Engine/World.h"
#include "ObstacleClass.h"
#include "GridTile.h"
#include "Math/Quat.h"


#include "Kismet/BlueprintFunctionLibrary.h"


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
	UE_LOG(LogTemp, Warning, TEXT("BeginPlay"));
	bool SpawnNoneTiles = false;
	GenerateMapDataFromWorld();
	SpawnTile(SpawnNoneTiles);
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
		int x = GridTileNumberX;
		//UE_LOG(LogTemp, Warning, TEXT("X %d"), i);
		for (int j = 0; j < GridTileNumberY; j++)
		{
			int Y = GridTileNumberY;

			FVector TilePosition = GetTilePosition(i, j);
			//UE_LOG(LogTemp, Warning, TEXT("TilePosition is %f, %F"), TilePosition.X, TilePosition.Y);
			TraceFloorAndObstacles(TilePosition, i, j);

			//UE_LOG(LogTemp, Warning, TEXT("123142"));
			//UE_LOG(LogTemp, Warning, TEXT("Y %d"), j);
		}	
	}

	/* Loop through all the elements and spawn the grid tile actor on each index */


}
void AGridSystem::SpawnTile(bool SpawnNoneTiles)
{

	for (auto& Entry : GridOfTiles)
	{
			FVector2D StructKey = GridOfTiles.Find(Entry.Key)->GridIndex;
			UE_LOG(LogTemp, Warning, TEXT("GridVector is %f, %f"), StructKey.X, StructKey.Y);

			FRotator roc;
			FVector TilePosition = GridOfTiles.Find(Entry.Key)->WorldLocation;

			
			FActorSpawnParameters SpawnParameters;
			AGridTile* SpawnedTileRef = GetWorld()->SpawnActor<AGridTile>(SpawnedTile, TilePosition, roc, SpawnParameters);

		
		if (GridOfTiles.Find(Entry.Key)->GroundTypes != (EGroundTypes::NORMAL) || SpawnNoneTiles == true) {


			/*template< class T >
			 T* SpawnActor
			 (
				 UClass* Class,
				 FVector const& Location,
				 FRotator const& Rotation,
				 AActor* Owner = NULL,
				 APawn* Instigator = NULL,
				 bool bNoCollisionFail = false
			 )
			 {
				 return (Class != NULL) ? Cast<T>(GetWorld()->SpawnActor(Class, NAME_None, &Location, &Rotation, NULL, bNoCollisionFail, false, Owner, Instigator)) : NULL;
			 }


			 AGridTile* GridTile = SpawnActor<AActor>(DefaultPawnClass, StartLocation, StartRotation, NULL, Instigator);


		 }*/


		}


	}



	//this->GridOfTiles;
		

}


//FVector
FVector AGridSystem::GridBottomLeft()
 {
	 FVector rightVector = Root->GetRightVector();
	 FVector xVector = (rightVector * GridSizeWorld.X) - GridLocation;

	 
	 FVector forwardVector = Root->GetForwardVector();
	 FVector yVector = forwardVector * GridSizeWorld.Y;
	 return FVector(xVector - yVector);
 }

int AGridSystem::GetTileCost(EGroundTypes TileType)
{
	int TileCost = 0;
	switch (TileType)
	{
	case EGroundTypes::NORMAL:
		TileCost = 1;
		break;
	case EGroundTypes::DIFFICULT:
		TileCost = 2;
			break;
	case EGroundTypes::REALLYDIFFICULT:
		TileCost = 5;
		break;
	case EGroundTypes::IMPOSSIBLE:
		TileCost = 255;
		break;
	case EGroundTypes::NONE:
		TileCost = 255;
		break;
	}

	return TileCost;

}




 FVector AGridSystem::GetTilePosition(int i, int j)
{
	FVector rightVector = Root->GetRightVector();
	//UE_LOG(LogTemp, Warning, TEXT("X location is %f"), rightVector.X);
	float x = i * (TileSize * 2.0);
	FVector xvec = rightVector * (x + TileSize);
	//UE_LOG(LogTemp, Warning, TEXT("X is %f"), x);
	//float x = x->ToFloat(i);
	
	
	FVector forwardVector = Root->GetForwardVector();
	//UE_LOG(LogTemp, Warning, TEXT("Y location is %f"), forwardVector.Y);
	float y = j * (TileSize * 2.0);
	FVector yvec = forwardVector * (y + TileSize);
	//UE_LOG(LogTemp, Warning, TEXT("Y is %f"), y);
 
	FVector GridBottomLeftPoint = GridBottomLeft();

	FVector TilePosition = GridBottomLeftPoint + xvec + yvec;

	return FVector(TilePosition);
 
 }

/* void AGridSystem::AddNewTile(FVector2D GridIndex, //AActor TileActor; //AActor UnitOnThisTile;
EGroundTypes* GroundTypes,
FVector WorldLocation,
int32 TileCost,
int32 FinalCost,
int32 CostFromStart,
int32 EstimatedCostToTarget,
FVector2D PreviousTile,
int32 FlowDirection)
{
FGridTiles NewTile(GridIndex, //AActor TileActor; //AActor UnitOnThisTile;
	GroundTypes,
	WorldLocation,
	TileCost,
	FinalCost,
	CostFromStart,
	EstimatedCostToTarget,
	PreviousTile,
	FlowDirection);
//GridOfTiles.Add(GridIndex, NewTile);
	} */

 void AGridSystem::TraceFloorAndObstacles(FVector TilePosition, int i, int j)
{
	 FVector TileAdded = TilePosition + FVector(1.f, 1.f, 1.f);
	 FHitResult OutHit;
	 float X(i);
	 float Y(j);
	 /*GridOfTilesKey*/
	 FVector2D StructKey(X,Y);


	 /*Make Struct*/
	 FGridTiles tile;
	 tile.GridIndex = StructKey;
	 tile.WorldLocation = TilePosition;
	 //add the nothing thing
	 tile.TileCost = GetTileCost(EGroundTypes::NONE);
	 tile.GroundTypes = EGroundTypes::NONE;
	
	 bool bSphereTrace = GetWorld()->SweepSingleByChannel(OutHit, TilePosition, TileAdded, FQuat(), ECollisionChannel::ECC_GameTraceChannel1, FCollisionShape::MakeSphere(TileSize - TileSizeMinus));
	 if (bSphereTrace) {
		 
		 bSphereTrace = GetWorld()->SweepSingleByChannel(OutHit, TilePosition, TileAdded, FQuat(), ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeSphere(TileSize - TileSizeMinus));

		 if (bSphereTrace) {

			 AObstacleClass* obstacle = Cast<AObstacleClass>(OutHit.Actor);
			 //is valid.
			 if (obstacle) {
				tile.TileCost = GetTileCost(obstacle->GroundTypes);
				tile.GroundTypes = obstacle->GroundTypes;
			 }
		 }
		 else {

			 tile.TileCost = GetTileCost(EGroundTypes::NORMAL);
			 tile.GroundTypes = EGroundTypes::NORMAL;
		 }
	 }

	 this->GridOfTiles.Add(StructKey, tile);
	 //UE_LOG(LogTemp, Warning, TEXT("End of SphereTrace Loop X %f, Y %f"), StructKey.X, StructKey.Y);










}



