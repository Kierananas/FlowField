// Fill out your copyright notice in the Description page of Project Settings.


#include "GridSystem.h"
#include "Math.h"
#include "Components/SceneComponent.h"
#include "Engine/World.h"
#include "Engine/EngineTypes.h"
#include "Math/Quat.h"




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
	//UE_LOG(LogTemp, Warning, TEXT("BeginPlay"));
	GenerateMapDataFromWorld();
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
	
	//FString dave = "Dave";


			
	for (int i = 0; i < GridTileNumberX; i++)
	{
		int x = GridTileNumberX;
		//UE_LOG(LogTemp, Warning, TEXT("X %d"), i);
		for (int  j = 0; j < GridTileNumberY; j++)
		{
			int Y = GridTileNumberY;
			
			FVector TilePosition = GetTilePosition(i, j);
			//UE_LOG(LogTemp, Warning, TEXT("TilePosition is %f, %F"), TilePosition.X, TilePosition.Y);
			TraceFloorAndObstacles(TilePosition);

			//UE_LOG(LogTemp, Warning, TEXT("123142"));
			//UE_LOG(LogTemp, Warning, TEXT("Y %d"), j);
		
		}
	}
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

 void AGridSystem::TraceFloorAndObstacles(FVector TilePosition)
{
	 const ECollisionChannel CollisionChannel = Root->GetCollisionObjectType();
	 const UEnum* ourEnum = FindObject<UEnum>(ANY_PACKAGE, TEXT("ETraceTypeQuery"), true);
	 UE_LOG(LogTemp, Warning, TEXT("Hello"));

	 for (int i = 0; i < 5; i++) {
		 CollisionChannel(i)
	 }
	 //CollisionChannel
	 
	 //UE_LOG(LogTemp, Warning, TEXT("Enum: %s"));
	 //int numberOfChannels = CollisionChannel->GetMaxEnumValue();
	 //FHitResult OutHit;
	 //FVector TileAdded = TilePosition + FVector(1.f, 1.f, 1.f);
	 //bool bSphereTrace = GetWorld()->SweepSingleByChannel(OutHit, TilePosition, TileAdded, FQuat(0.f, 0.f, 0.f, 0.f), ourEnum);


	///* bool UWorld::SweepSingleByChannel(struct FHitResult& OutHit, const FVector& Start, const FVector& End, const FQuat& Rot, ECollisionChannel TraceChannel, const FCollisionShape& CollisionShape, const FCollisionQueryParams& Params /* = FCollisionQueryParams::DefaultQueryParam */, const FCollisionResponseParams& ResponseParam /* = FCollisionResponseParams::DefaultResponseParam */) const
	 /*{
		 if (CollisionShape.IsNearlyZero())
		 {
			 return LineTraceSingleByChannel(OutHit, Start, End, TraceChannel, Params, ResponseParam);
		 }
		 else
		 {
			 return FPhysicsInterface::GeomSweepSingle(this, CollisionShape, Rot, OutHit, Start, End, TraceChannel, Params, ResponseParam, FCollisionObjectQueryParams::DefaultObjectQueryParam);
		 }
	 }*/



}



