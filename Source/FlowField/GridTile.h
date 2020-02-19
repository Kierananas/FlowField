// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridTile.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTileCostChange);
class UMaterialInstanceDynamic;


UCLASS()
class FLOWFIELD_API AGridTile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGridTile();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Booleans")
		bool isOvered = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Booleans")
		bool isSelected = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Booleans")
		bool isInPath = false;

	UPROPERTY(VisibleAnywhere)
		USceneComponent* Root;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* TileMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMesh* TileMeshAsset;

	UPROPERTY(VisibleAnywhere)
		class AGridSystem* the_grid;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GridTile")
		FVector2D GridIndex;


	//UPROPERTY(BlueprintCallable)
		//FTileCostChange OnTileCostChange;

	
	UFUNCTION()
		void BeginCursorOver(UPrimitiveComponent* TouchedComponent);

	UFUNCTION()
		void EndCursorOver(UPrimitiveComponent* TouchedComponent);

	UFUNCTION(BlueprintCallable, Category = "Tile")
		void StartOverTile();

	UFUNCTION(BlueprintCallable, Category = "Tile")
		void EndOverTile();



	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Tile")
		void SetWidgetValues();


	UFUNCTION(BlueprintCallable, Category = "Tile")
		void SetTileColour() const;

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
