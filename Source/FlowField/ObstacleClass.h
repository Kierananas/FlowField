// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DataTypes.h"
#include "ObstacleClass.generated.h"

class AActor;
UCLASS()
class FLOWFIELD_API AObstacleClass : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AObstacleClass();

	UPROPERTY()
		USceneComponent* Root;
	
	UPROPERTY(VisibleAnywhere, Category = "Obstacle")
		UStaticMeshComponent* ObstacleMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obstacle", meta = (AllowPrivateAccess = "true"))
		EGroundTypes GroundTypes;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
