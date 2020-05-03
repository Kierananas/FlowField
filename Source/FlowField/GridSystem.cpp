// Fill out your copyright notice in the Description page of Project Settings.


#include "GridSystem.h"
#include "Math.h"
#include "Math/Vector.h"
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
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	
	// Pre-defined in code but can be edited within Editor - sets the limits of the grid system.
	GridSizeWorld = FVector2D(500, 500);
	
	// How big the tiles should be (Divided by the size of the grid size).
	TileSize = 100;
	
	//Used for the shape of a collision sphere in tracefloorandobstacles function
	TileSizeMinus = 5.f;
}


// Called when the game starts or when spawned
void AGridSystem::BeginPlay()
{
	// Call any Unreal actor behaviour followed by our defined behaviour.
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("BeginPlay"));
	bool SpawnNoneTiles = false;
	GenerateMapDataFromWorld();
	//SpawnTile(SpawnNoneTiles);
	
}

// Called every frame
void AGridSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGridSystem::NewTileOvered(AGridTile* OveredTile)
{
	/*
	if(OveredTile == nullptr)
	{
		
		OveredTile;
	}
	else {
		OveredTile->EndOverTile();
		OveredTile;

		UE_LOG(LogTemp, Warning, TEXT("123142"));
	}
	*/
}
// This function's paramerters are passed in by referrence in GenerateMapDataFrom World function.
// It is used to Calculate how many tiles within the grid there are. 
void AGridSystem::GridTileNumber(int& GridTileNumberX, int& GridTileNumberY)
{
	FVector2D temp = GridSizeWorld / TileSize; // GridSizeWorld / TileSize gives us how many tiles we want.

	GridTileNumberX = FMath::RoundToInt(temp.X) - 1;
	GridTileNumberY = FMath::RoundToInt(temp.Y) - 1;
}


//void AGridSystem::SetTilePosition(FVector TilePosition)
//{
	//FVector X = GridLocation - (FVector GetRightVector() const * FVector2D GridSizeWorld.X);
	//FVector Y = UScene GetForwardVector() const * FVector2D GridSizeWorld.Y
	//FVector BottomLeft = FVector X - FVector Y


//}
// This Function is used to calculate how many tiles we have used other functions further down the file.
// A double Loop is used to calculate the X and the Y starting with the Y axis then proceeds to the next row.
// Two functions are fired for each iteration, one to provide the TilePosition and another to add the tile to the GridOfTiles Map and spawn into the world.
void AGridSystem::GenerateMapDataFromWorld()
{
	int GridTileNumberX, GridTileNumberY;
	GridTileNumber(GridTileNumberX, GridTileNumberY);
				
	//Loop Through X axis
	for (int i = 0; i < GridTileNumberX; i++)
	{
		int x = GridTileNumberX;
		//Loop Through Y axis
		for (int j = 0; j < GridTileNumberY; j++)
		{
			int Y = GridTileNumberY;
			
			
			//Provide the TilePosition function with the Loop i, j values. 
			FVector TilePosition = GetTilePosition(i, j);
			//UE_LOG(LogTemp, Warning, TEXT("TilePosition is %f, %F"), TilePosition.X, TilePosition.Y);
			
			
			//Provide the TraceFloorAndObstacles function with previous function and the Loop i, j values. 
			TraceFloorAndObstacles(TilePosition, i, j);

			//UE_LOG(LogTemp, Warning, TEXT("123142"));
			//UE_LOG(LogTemp, Warning, TEXT("Y %d"), j);
		}	
	}

	/* Loop through all the elements and spawn the grid tile actor on each index */


}
/*void AGridSystem::SpawnTile(bool SpawnNoneTiles)
{
	FGridTiles tile;
	
	//add the nothing thing
	for (auto& Entry : GridOfTiles)
	{
			FVector2D StructKey = GridOfTiles.Find(Entry.Key)->GridIndex;
			UE_LOG(LogTemp, Warning, TEXT("GridVector is %f, %f"), StructKey.X, StructKey.Y);

		if (GridOfTiles.Find(Entry.Key)->GroundTypes != (EGroundTypes::NONE) || SpawnNoneTiles == true) {
			
			FRotator roc;
			FVector TilePosition = GridOfTiles.Find(Entry.Key)->WorldLocation;

			
			FActorSpawnParameters SpawnParameters;
			AGridTile* SpawnedTileRef = GetWorld()->SpawnActor<AGridTile>(TileClass, TilePosition, roc, SpawnParameters);
			if (GridTileMesh) SpawnedTileRef->TileMeshAsset = GridTileMesh;
			tile.GridIndex = GridOfTiles.Find(Entry.Key)->GridIndex;
			tile.WorldLocation = GridOfTiles.Find(Entry.Key)->WorldLocation;
			//add the nothing thing
			tile.TileCost = GridOfTiles.Find(Entry.Key)->TileCost;
			tile.GroundTypes = GridOfTiles.Find(Entry.Key)->GroundTypes;
			tile.GridTile = SpawnedTileRef;
			this->GridOfTiles.FindOrAdd(StructKey, tile);


		} 

	}



	//this->GridOfTiles;
		

}
*/

// Given the grids bottom left position vector we know where to spawn the grid tiles.
FVector AGridSystem::GridBottomLeft()
 {
	 FVector GridLocation = GetActorLocation(); // Where the grid system actor is placed in world space.
	 FVector rightVector = Root->GetRightVector(); // X axis of root.
	 FVector xVector = rightVector * GridSizeWorld.X; // Get the grids max X axis
	 FVector xGridVector = GridLocation - xVector; // This vector will provide the vector for the left edge of the grid.

	 // Repeat of the code above for the Y axis to get the vector for the bottom.
	 FVector forwardVector = Root->GetForwardVector(); // Y axis of root.
	 FVector yVector = forwardVector * GridSizeWorld.Y; // Get the grids max Y axis
	// UE_LOG(LogTemp, Warning, TEXT("Forward Vector Math %f, %f, %f"), yVector.X, yVector.Y, yVector.Z);
	 
	 return FVector(xGridVector - yVector);
 }

 // Switch Function that is used to provide tile costs to different ground type obstacles, e.g. tile with thick grass or untraversable terrain. 
int AGridSystem::GetTileCost(EGroundTypes TileType)
{
	int TileCost = 0; // set tile cost to 0 as a default.
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



// This function provides the vector location of the tile int i and int j of the GenerateMapDatafromWorld function.
// With this data we can set the spawning location for each tile actor.
 FVector AGridSystem::GetTilePosition(int i, int j) // 
{
	FVector rightVector = Root->GetRightVector();
	//UE_LOG(LogTemp, Warning, TEXT("X location is %f"), rightVector.X);
	float x = i * (TileSize * 2.0); // This value is used to separate the tiles 200 spaces apart from each other (if TileSize is 100).
	FVector xvec = rightVector * (x + TileSize); // By adding TileSize to x, we get the top of the tile's position.
	//UE_LOG(LogTemp, Warning, TEXT("X is %f"), x);
	//float x = x->ToFloat(i); 
	
	
	FVector forwardVector = Root->GetForwardVector();
	//UE_LOG(LogTemp, Warning, TEXT("Y location is %f"), forwardVector.Y); 
	float y = j * (TileSize * 2.0); // This value is used to separate the tiles 200 spaces apart from each other (if TileSize is 100).
	FVector yvec = forwardVector * (y + TileSize); // By adding TileSize to x, we get the top of the tile's position.
	//UE_LOG(LogTemp, Warning, TEXT("Y is %f"), y);
 
	FVector GridBottomLeftPoint = GridBottomLeft(); // Get the bottom left corner of the grid

	FVector TilePosition = GridBottomLeftPoint + xvec + yvec; // Start of the grid at the bottom left + x axis offset + y axis offset = TilePosition.

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
	
	
// This function has a sphere trace to check if the tile is on ground aswell as checking for obstacles.
// Depending on said checks it spawns the tiles with the associated values.
 void AGridSystem::TraceFloorAndObstacles(FVector TilePosition, int i, int j)
 {
	 FVector TileAdded = TilePosition + FVector(1.f, 1.f, 1.f); // This FVector is used for creating the sphere shape as it needs to have a start position (TilePosition) and an end position.
	 FHitResult OutHit; // Outhit is the actor hit by the sphere check.
	 float X(i);
	 float Y(j);
	 /*GridOfTiles Map Key*/
	 FVector2D StructKey(X, Y);


	 /*Make Struct*/
	 FGridTiles tile; // FGridTiles is the struct that will contain tile data.
	 FRotator roc; // The collision check needs a rotation value so this is a default rotation to provide the check.
	 tile.GridIndex = StructKey; // Grid Index is a 2D Vector that stores the X and Y of the tiles which is also used as the key to the map of tiles.
	 tile.WorldLocation = TilePosition; // Setting the struct's WorldLocation vector to the TilePosition value provided throughout the function.
	 //add the nothing thing
	 tile.TileCost = GetTileCost(EGroundTypes::NONE); // Setting the TileCost of the struct to NONE intially but will be set depending on the collision check throughout the function.
	 tile.GroundTypes = EGroundTypes::NONE; // Setting the ground types to NONE but might change throughout the function with the TileCost.

// Collision check

	 bool bSphereTrace = GetWorld()->SweepSingleByChannel(OutHit, TilePosition, TileAdded, FQuat(), ECollisionChannel::ECC_GameTraceChannel1, FCollisionShape::MakeSphere(TileSize - TileSizeMinus)); // Unreal function for sphere check, checking for the floor.
	 if (bSphereTrace) { // Checking whether the sphere collides with the floor, if not do nothing, if it does, do another check for obstacles on the floor.

		 bSphereTrace = GetWorld()->SweepSingleByChannel(OutHit, TilePosition, TileAdded, FQuat(), ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeSphere(TileSize - TileSizeMinus)); // Unreal function for sphere check, checking for obstacles.

		 if (bSphereTrace) {
			
			 AObstacleClass* obstacle = Cast<AObstacleClass>(OutHit.Actor);
			 //is the obstacle cast valid.
			 
			 if (obstacle) {
			 // Collided with an obstacle.
				 tile.TileCost = GetTileCost(obstacle->GroundTypes); // Set Tile cost using the GetTileCost function, setting the cost to the correct cost depending on the obstacle provided.
				 tile.GroundTypes = obstacle->GroundTypes; // Just like tile cost, set the ground types to match the obstacle colldied with.
				 tile.GridIndex = StructKey; // Set the GridIndex (Map Key) to the tile's index (X, Y). 
				 FActorSpawnParameters SpawnParameters; // Unreal spawning parameters that can be reset but I've kept them to default.
				 AGridTile* SpawnedTileRef = GetWorld()->SpawnActor<AGridTile>(TileClass, TilePosition, roc, SpawnParameters); // Spawn the GridTile actor into the world. 
				 if (GridTileMesh) SpawnedTileRef->TileMeshAsset = GridTileMesh; // Set the tile's mesh to a blueprint writable mesh (changable in editor).
				 tile.GridTile = SpawnedTileRef; // Give the spawned actor a referrence to add into the struct.
			 }
		 }
		 else {
			// Not collided with any obstacles but has collided with the floor.
			 tile.TileCost = GetTileCost(EGroundTypes::NORMAL); // Set Tile cost using the GetTileCost function, setting the cost to normal as no obstacle has been detected.
			 tile.GroundTypes = EGroundTypes::NORMAL; // Just like tile cost, set the ground types to normal.
			 tile.GridIndex = StructKey; // Set the GridIndex (Map Key) to the tile's index (X, Y). 
			 FActorSpawnParameters SpawnParameters; // Unreal spawning parameters that can be reset but I've kept them to default.
			 AGridTile* SpawnedTileRef = GetWorld()->SpawnActor<AGridTile>(TileClass, TilePosition, roc, SpawnParameters); // Spawn the GridTile actor into the world.
			 if (GridTileMesh) SpawnedTileRef->TileMeshAsset = GridTileMesh; // Set the tile's mesh to a blueprint writable mesh (changable in editor).
			 tile.GridTile = SpawnedTileRef; // Give the spawned actor a referrence to add into the struct.
		 }
	 } // No else check because we dont want anything happening if there is no floor beneath the tile.
	 
	 
	 this->GridOfTiles.Add(StructKey, tile); // Now we have set the data of the tiles in our checks, store them in the GridOfTiles Map.
	 if (tile.GridTile) { // If the tile has been spawned correctly, do this.
		 tile.GridTile->the_grid = this; // the_grid is used to referrence this class within the GridTile class.
		 tile.GridTile->GridIndex = tile.GridIndex; // Set the GridIndex vlaue within the GridTile class to the provided index.
		 this->GridOfTiles.Add(StructKey, tile); // Now we have set the data of the tiles in our checks, store them in the GridOfTiles Map.
		 tile.GridTile->SetWidgetValues(); // Call the function that sets the values of the tile's widget to update.
	 }
	 //UE_LOG(LogTemp, Warning, TEXT("End of SphereTrace Loop X %f, Y %f"), StructKey.X, StructKey.Y);


	 








 }



