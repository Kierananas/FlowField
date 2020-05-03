// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DataTypes.h"
#include "GridTile.h"
#include "GridSystem.generated.h"


class AGridTile; // The Tile actor to be placed over each tile location within the grid system.

USTRUCT(BlueprintType) // Can be read in UE4 Blueprint.
struct FGridTiles // The struct to hold all the data of each tile.
{
	GENERATED_BODY()

		//now we can add our properties.

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid Struct")
		FVector2D GridIndex; // The Key of the tile (X, Y) e.g. 0,0.
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid Struct")
	AGridTile* GridTile; // Actor referrence to the spawned tile actor.
	
		//TSubclassOf<AGridTile> TileActor;
	//AActor UnitOnThisTile;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid Struct")
		EGroundTypes GroundTypes; // Enum for the type of traversable ground e.g. obstacles, no/normal ground.
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid Struct")
		FVector WorldLocation; // The location of the tile in the world.
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid Struct")
		int32 TileCost; // What the traversable cost is for the tile.
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid Struct")
		int32 FinalCost; // The cost of the tile cost and estimated cost to target together.
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid Struct")
		int32 CostFromStart; // Cost of getting to current tile from the starting tile.
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid Struct")
		int32 EstimatedCostToTarget; // Using an heurstics method, estimates the cost to get to the target.
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid Struct")
		FVector2D PreviousTile; // A 2d vector storing the index of the previously used tile.
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid Struct")
		int32 FlowDirection; // Flow direction is a int that will tell the units what direction to move in, both orthogonal and diagonal (0 - 7).


	/*FGridTiles(FVector2D InGridIndex, EGroundTypes* InGroundTypes, FVector InWorldLocation,
		int32 InTileCost, int32 InFinalCost, int32 InCostFromStart, int32 InEstimatedCostToTarget, FVector2D InPreviousTile, int32 InFlowDirection) :
		GridIndex(InGridIndex), GroundTypes(InGroundTypes), WorldLocation(InWorldLocation), TileCost(InTileCost), FinalCost(InFinalCost),
		CostFromStart(InCostFromStart), EstimatedCostToTarget(InEstimatedCostToTarget), PreviousTile(InPreviousTile), FlowDirection(InFlowDirection)
	{

	};*/
};

UCLASS()
class FLOWFIELD_API AGridSystem : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGridSystem();
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//float;

	UPROPERTY()
		USceneComponent* Root; // The component used to place into the world and be moved/referred to.
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMesh* GridTileMesh; // Assignable mesh to be used for the tile actor.

	UPROPERTY(BlueprintType, BlueprintReadWrite, Category = "Map")
		TMap<FVector2D, FGridTiles> GridOfTiles; // The map used to store the tiles of the grid, using an 2D Vector as the key (X, Y) and the struct GridOfTiles to be set to each element of the map.
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map")
	FVector2D GridSizeWorld; // A 2D vector to set the max size of the grid.
	
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map")
	//FVector GridLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map")
	float TileSize; // Float to set how big the tiles will be.
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map")
	float TileSizeMinus; // Float used in sphere collision checks.


	/*
		float
		float
		FVector
		Fvector2D

	*/


	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enum)
		//EGroundTypes GroundTypesEnum;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//UPROPERTY(EditDefaultsOnly, Category = "Tile")
	//UObject<AGridTile> SpawnedTile;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
// This Function is used to calculate how many tiles we have used other functions further down the file.
// A double Loop is used to calculate the X and the Y starting with the Y axis then proceeds to the next row.
// Two functions are fired for each iteration, one to provide the TilePosition and another to add the tile to the GridOfTiles Map and spawn into the world.
	void GenerateMapDataFromWorld(); // 


	//UFUNCTION()
	//void SpawnTile(bool SpawnNoneTiles);

// This function's paramerters are passed in by referrence in GenerateMapDataFrom World function.
// It is used to Calculate how many tiles within the grid there are. 
	void GridTileNumber(int& GridTileNumberX, int& GridTileNumberY);

	
	//void GetTilePosition(int i, int j);

	/*void AddNewTile(FVector2D GridIndex, //AActor TileActor; //AActor UnitOnThisTile;
	EGroundTypes* GroundTypes,
	FVector WorldLocation,
	int32 TileCost,
	int32 FinalCost,
	int32 CostFromStart,
	int32 EstimatedCostToTarget,
	FVector2D PreviousTile,
	int32 FlowDirection);
	*/

// Given the grids bottom left position vector we know where to spawn the grid tiles.
	FVector GridBottomLeft();

// Switch Function that is used to provide tile costs to different ground type obstacles, e.g. tile with thick grass or untraversable terrain. 
	int GetTileCost(EGroundTypes TileType);

	
// This function provides the vector location of the tile int i and int j of the GenerateMapDatafromWorld function.
// With this data we can set the spawning location for each tile actor.
	FVector GetTilePosition(int i, int j);
	//void AGridSystem::SetTilePosition(FVector TilePosition);

	
// This function has a sphere trace to check if the tile is on ground aswell as checking for obstacles.
// Depending on said checks it spawns the tiles with the associated values.
	void TraceFloorAndObstacles(FVector TilePosition, int i, int j);

// Refference of the GridTile Actor class, used to spawn them within the TraceFloorAndObstacles function.
	UPROPERTY(EditAnywhere)
	TSubclassOf<AGridTile> TileClass = AGridTile::StaticClass();

	//A* code goes in this function
	UFUNCTION(BlueprintCallable, Category = "Tile")
	void NewTileOvered(AGridTile * OveredTile);

};
