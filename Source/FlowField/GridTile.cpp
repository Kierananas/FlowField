// Fill out your copyright notice in the Description page of Project Settings.


#include "GridTile.h"
#include "Components/StaticMeshComponent.h"
#include "GridSystem.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AGridTile::AGridTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	TileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TileMesh"));
	TileMesh->SetupAttachment(this->RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ModelPath(TEXT("StaticMesh'/Game/StarterContent/Props/SM_Chair.SM_Chair'"));
	TileMesh->SetStaticMesh(ModelPath.Object);
}

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

