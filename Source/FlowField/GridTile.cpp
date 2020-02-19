// Fill out your copyright notice in the Description page of Project Settings.


#include "GridTile.h"
//#include "Materials/MaterialInstanceDynamic.h"
#include "Components/StaticMeshComponent.h"
//#include "Materials/MaterialInstance.h"
#include "Math/Color.h"
#include "KismetMathLibrary.generated.h"
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
	/*auto Material = TileMesh->GetMaterial(0);
	DynamicMaterial = UMaterialInstanceDynamic::Create(Material, NULL);
	TileMesh->SetMaterial(0, DynamicMaterial);*/
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ModelPath(TEXT("StaticMesh'/Game/StarterContent/Architecture/Floor_400x400.Floor_400x400'"));
	TileMesh->SetStaticMesh(ModelPath.Object);

	TileMesh->OnBeginCursorOver.AddDynamic(this, &AGridTile::BeginCursorOver);
}



void AGridTile::BeginCursorOver(UPrimitiveComponent* TouchedComponent)
{
	//ive been touched. teehee
	StartOverTile();
	//the_grid->OveredTile = this;
	the_grid->NewTileOvered(this);
	//call function Event Start Over Tile
	//call function in the gird 
	//Grid.Event New Tile Overed(this);
}

void AGridTile::EndCursorOver(UPrimitiveComponent* TouchedComponent)
{
	the_grid->NewTileOvered(nullptr);
}



void AGridTile::StartOverTile()
{
	isOvered = true;
	SetTileColour();
}

void AGridTile::EndOverTile()
{
	isOvered = false;
	SetTileColour();
}

//void AGridTile::SetWidgetValues()
//{

	
//}

void AGridTile::SetTileColour() const
{
	FLinearColor TileColour;
	switch (the_grid->GridOfTiles.Find(GridIndex)->GroundTypes)
	{
	case EGroundTypes::NORMAL:
		TileColour = NormalTileColour;
		break;
	case EGroundTypes::DIFFICULT:
		TileColour = DifficultTileColour;
		break;
	case EGroundTypes::REALLYDIFFICULT:
		TileColour = ReallyDifficultTileColour;
		break;
	case EGroundTypes::IMPOSSIBLE:
		TileColour = ImpossibleTileColour;
		break;
	case EGroundTypes::NONE:
		TileColour = NoneTileColour;
		break;
	}

	if (isSelected)
	{
		TileMesh->SetScalarParameterValueOnMaterials("bIsSelected", 1.f);
		
	}	else {
		TileMesh->SetScalarParameterValueOnMaterials("bIsSelected", 0.f);
	}

	if (isOvered)
	{
		FVector OveredColour = TileColour * 3.f;
		TileColour = OveredColour;
		/*FVector OveredColour
		(
			const FLinearColor & TileColour
		);
		TileColour = OveredColour * 3.f*/
	}

	if (isInPath)
	{
		FLinearColor Colour
		(
			0.06343f,
			0.f,
			1.f,
			1.f
		);	TileColour = Colour;
	}
	const FVector OveredColour = TileColour;
	TileMesh->SetVectorParameterValueOnMaterials("TileColour", OveredColour);
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

