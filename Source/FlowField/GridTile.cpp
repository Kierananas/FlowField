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
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ModelPath(TEXT("StaticMesh'/Game/StarterContent/Architecture/Floor_400x400.Floor_400x400'")); // Locate the mesh asset and set it to ModelPath.
	TileMesh->SetStaticMesh(ModelPath.Object); // Set TileMesh to = ModelPath done above.

	TileMesh->OnBeginCursorOver.AddDynamic(this, &AGridTile::BeginCursorOver); // Setting the mesh to be dynamic so the player than interact with it to chnage colour.
}


// When the player's cursor overlaps the actor.
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
// The players cursor was on the actor but now been moved off.
void AGridTile::EndCursorOver(UPrimitiveComponent* TouchedComponent)
{
	the_grid->NewTileOvered(nullptr); // Set the selected tile referrence to be null as we no longer are on one.
}


// Called on overlapp, used to chnage the colour and other values.
void AGridTile::StartOverTile()
{
	isOvered = true; // If this bool is true then change values/ colour in SetTileColour function.
	SetTileColour(); // Change colour of tile
}

void AGridTile::EndOverTile()
{
	isOvered = false; // If this bool is false then reset the chnages done in StartOverTile.
	SetTileColour(); // Change colour of tile
}

//void AGridTile::SetWidgetValues()
//{

	
//}
// This function is used to switch between colours depending on groundtypes (obstacles) and slight chnage of colour to show whether they are selected or not.
void AGridTile::SetTileColour() const
{
	// Switch function between ground types.
	FLinearColor TileColour;
	switch (the_grid->GridOfTiles.Find(GridIndex)->GroundTypes)
	{
	case EGroundTypes::NORMAL:
		TileColour = NormalTileColour; // Reset to preset colour (GridTile.h)
		break;
	case EGroundTypes::DIFFICULT:
		TileColour = DifficultTileColour; // Reset to preset colour (GridTile.h)
		break;
	case EGroundTypes::REALLYDIFFICULT:
		TileColour = ReallyDifficultTileColour; // Reset to preset colour (GridTile.h)
		break;
	case EGroundTypes::IMPOSSIBLE:
		TileColour = ImpossibleTileColour; // Reset to preset colour (GridTile.h)
		break;
	case EGroundTypes::NONE:
		TileColour = NoneTileColour; // Reset to preset colour (GridTile.h)
		break; 
	}

	if (isSelected) // if the tile is selected, make the colour lighter by scaling the colour up, if not, remain the same.
	{
		TileMesh->SetScalarParameterValueOnMaterials("bIsSelected", 1.f); 
		
	}	else {
		TileMesh->SetScalarParameterValueOnMaterials("bIsSelected", 0.f);
	}

	if (isOvered) // If the cursor is over the tile, increase brightness.
	{
		FVector OveredColour = TileColour * 3.f;
		TileColour = OveredColour;
		/*FVector OveredColour
		(
			const FLinearColor & TileColour
		);
		TileColour = OveredColour * 3.f*/
	}

	if (isInPath) // For pathfinding, if a tile is part of the selected path, change colour to a blue colour.
	{
		FLinearColor Colour
		(
			0.06343f,
			0.f,
			1.f,
			1.f
		);	TileColour = Colour;
	}
	const FVector OveredColour = TileColour; // Once all checks have been done, set the colour to const.
	TileMesh->SetVectorParameterValueOnMaterials("TileColour", OveredColour); // Change the tilemesh colour to the colour the function has produced.
}

// Called when the game starts or when spawned
void AGridTile::BeginPlay()
{
		// Call any Unreal actor behaviour followed by our defined behaviour.
	Super::BeginPlay();

	if (TileMeshAsset) TileMesh->SetStaticMesh(TileMeshAsset); // Check if the actor has a mesh, if not assign the blueprint assignable mesh to the actor.
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
	if (TileMeshAsset) TileMesh->SetStaticMesh(TileMeshAsset); // Check if the actor has a mesh, if not assign the blueprint assignable mesh to the actor.


}




/*void AGridTile::SetTileSize()
{
	AGridSystem.TileSize;
}*/

