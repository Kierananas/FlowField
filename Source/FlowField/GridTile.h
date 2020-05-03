// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridTile.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTileCostChange); // Testing
class UMaterialInstanceDynamic; // Inheriting unreal material class.


UCLASS()
class FLOWFIELD_API AGridTile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGridTile();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Booleans")
		bool isOvered = false; // Boolean used for toggling cursor over tile and changing colour.
		

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Booleans")
		bool isSelected = false; // Boolean for selecting tiles and changing tile colour.

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Booleans")
		bool isInPath = false; // Used to toggle colour change to tiles that are in a path.

	UPROPERTY(VisibleAnywhere)
		USceneComponent* Root;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* TileMesh; // The mesh of the tile.

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMesh* TileMeshAsset; // A mesh that can be reassigned in editor that controls the tile's mesh.

	UPROPERTY(VisibleAnywhere)
		class AGridSystem* the_grid; // This is a referrence to the GridSystem Class, used to access memory stored within that class.

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GridTile")
		FVector2D GridIndex; // A 2D vector that represents the index of a tile.


	//UPROPERTY(BlueprintCallable)
		//FTileCostChange OnTileCostChange;

	
	UFUNCTION()
		void BeginCursorOver(UPrimitiveComponent* TouchedComponent); // Event that fires when the cursor is over the actor.

	UFUNCTION()
		void EndCursorOver(UPrimitiveComponent* TouchedComponent); // Event that fires when the cursor leaves the actor.

	UFUNCTION(BlueprintCallable, Category = "Tile")
		void StartOverTile(); // Function that is called in BeginCursorOver.

	UFUNCTION(BlueprintCallable, Category = "Tile") 
		void EndOverTile(); // Function that is called in EndCursorOver.



	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Tile")
		void SetWidgetValues(); // This function is called within the GridSystem class when the tiles are spawned. It sets the values associated with the widget of the tile actor.


	UFUNCTION(BlueprintCallable, Category = "Tile")
		void SetTileColour() const; // Sets the colour of the tile.

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GridColours")
		FLinearColor NormalTileColour;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GridColours")
		FLinearColor DifficultTileColour;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GridColours")
		FLinearColor ReallyDifficultTileColour;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GridColours")
		FLinearColor ImpossibleTileColour;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GridColours")
		FLinearColor NoneTileColour;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OnConstruction(const FTransform& Transform) override;

	//void SetTileSize();

private:
	//UMaterialInstanceDynamic* DynamicMaterial;
};
