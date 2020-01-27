// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DataTypes.h"
#include "GridSystem.generated.h"


USTRUCT()
struct FGridTiles
{
	GENERATED_BODY()

		//now we can add our properties.

	FVector2D GridIndex;
	//AActor TileActor;
	//AActor UnitOnThisTile;
	EGroundTypes* GroundTypes;
	FVector WorldLocation;
	int32 TileCost;
	int32 FinalCost;
	int32 CostFromStart;
	int32 EstimatedCostToTarget;
	FVector2D PreviousTile;
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

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
		USceneComponent* Root;

	void GridTileNumber(int& GridTileNumberX, int& GridTileNumberY);

	void GenerateMapDataFromWorld();
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
