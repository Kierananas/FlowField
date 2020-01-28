// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridTile.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTileCostChange);

UCLASS()
class FLOWFIELD_API AGridTile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGridTile();

	UPROPERTY()
		USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, Category = "Tile")
		UStaticMeshComponent* TileMesh;

	UPROPERTY(BlueprintCallable)
		FTileCostChange OnTileCostChange;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;




};