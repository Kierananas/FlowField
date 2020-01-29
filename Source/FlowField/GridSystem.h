// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DataTypes.h"
#include "GridTile.h"
#include "GridSystem.generated.h"


class AGridTile;

USTRUCT(BlueprintType)
struct FGridTiles
{
	GENERATED_BODY()

		//now we can add our properties.

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid Struct")
		FVector2D GridIndex;
	//AActor TileActor;
	//AActor UnitOnThisTile;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid Struct")
		EGroundTypes GroundTypes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid Struct")
		FVector WorldLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid Struct")
		int32 TileCost;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid Struct")
		int32 FinalCost;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid Struct")
		int32 CostFromStart;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid Struct")
		int32 EstimatedCostToTarget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid Struct")
		FVector2D PreviousTile;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid Struct")
		int32 FlowDirection;


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
		USceneComponent* Root;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMesh* GridTileMesh;

	UPROPERTY()
		TMap<FVector2D, FGridTiles> GridOfTiles;
	/*

		float
		float
		FVector
		Fvector2D

	*/
	FVector2D GridSizeWorld;
	FVector GridLocation;
	float TileSize;
	float TileSizeMinus;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enum)
		EGroundTypes GroundTypesEnum;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//UPROPERTY(EditDefaultsOnly, Category = "Tile")
	//UObject<AGridTile> SpawnedTile;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void GenerateMapDataFromWorld();


	UFUNCTION()
	void SpawnTile(bool SpawnNoneTiles);


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

	//FVector
	FVector GridBottomLeft();

	int GetTileCost(EGroundTypes TileType);

	FVector GetTilePosition(int i, int j);
	//void AGridSystem::SetTilePosition(FVector TilePosition);

	void TraceFloorAndObstacles(FVector TilePosition, int i, int j);


};
