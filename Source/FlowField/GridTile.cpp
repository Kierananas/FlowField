// Fill out your copyright notice in the Description page of Project Settings.


#include "GridTile.h"
#include "Components/StaticMeshComponent.h"
#include "GridSystem.h"
#include "UObject/ConstructorHelpers.h"

//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCursorOver);

// Sets default values
AGridTile::AGridTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	TileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TileMesh"));
	TileMesh->SetupAttachment(this->RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ModelPath(TEXT("StaticMesh'/Game/StarterContent/Architecture/Floor_400x400.Floor_400x400'"));
	TileMesh->SetStaticMesh(ModelPath.Object);


	TileMesh->OnBeginCursorOver.AddDynamic(this, &AGridTile::BeginCursorOver);

}

void AGridTile::BeginCursorOver(UPrimitiveComponent* TouchedComponent)
{
	//ive been touched. teehee


	//call function Event Start Over Tile
	//call function in the gird 
	//the_grid.
	//Grid.Event New Tile Overed(this);
}

void AGridTile::StartOverTile()
{
	isOvered = true;
	//SetTileColour();

}

/*void AGridTile::SetTileColour()
{
	FGridTiles tile;
	
	the_grid->GridOfTiles.Find(GridIndex)->GroundTypes;

	

	

}*/






// Called when the game starts or when spawned
void AGridTile::BeginPlay()
{
	Super::BeginPlay();

	if (TileMeshAsset) TileMesh->SetStaticMesh(TileMeshAsset);
	TileMesh->RegisterComponent();
	


	//TileMesh->SetRelativeScale3D()
}

// Called every frame
void AGridTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	//OnTileCostChange.Broadcast();

}

void AGridTile::OnConstruction(const FTransform& Transform)
{
	if (TileMeshAsset) TileMesh->SetStaticMesh(TileMeshAsset);


}




/*void AGridTile::SetTileSize()
{
	AGridSystem.TileSize;
}*/

