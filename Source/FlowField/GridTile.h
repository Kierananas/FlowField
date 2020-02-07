// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridTile.generated.h"

//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTileCostChange);

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

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* TileMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMesh* TileMeshAsset;


	UPROPERTY(VisibleAnywhere)
	class AGridSystem * the_grid;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
		FVector2D GridIndex;
	
	//UPROPERTY(BlueprintCallable)
		//FTileCostChange OnTileCostChange;


	UFUNCTION()
	void BeginCursorOver(UPrimitiveComponent* TouchedComponent);

	UFUNCTION(BlueprintImplementableEvent, Category = "Overlap Events")
	void StartOverTile();

	//UFUNCTION()
	//void SetTileColour();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OnConstruction(const FTransform& Transform) override;

	//void SetTileSize();

};
