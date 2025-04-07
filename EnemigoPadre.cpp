// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemigoPadre.h"

// Sets default values
AEnemigoPadre::AEnemigoPadre()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MallaEnemigo = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MallaEnemigo"));
	RootComponent = MallaEnemigo;


	MallaEnemigo->SetupAttachment(RootComponent);
	MallaEnemigo->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh>ObjetoMallaEnemigo(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_QuadPyramid.Shape_QuadPyramid'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("Material'/Game/StarterContent/Materials/M_Tech_Hex_Tile.M_Tech_Hex_Tile'"));
	if (ObjetoMallaEnemigo.Succeeded())
	{
		MallaEnemigo->SetStaticMesh(ObjetoMallaEnemigo.Object);

		MallaEnemigo->SetRelativeLocation(FVector(0.0f, 0.0f, 10.0f));
		if (Material.Succeeded())
		{
			MallaEnemigo->SetMaterial(0, Material.Object);
		}
	}
	EpuedeMoverse = FMath::RandBool();
	SpeedEnemigo = 4.0f;
}

// Called when the game starts or when spawned
void AEnemigoPadre::BeginPlay()
{
	Super::BeginPlay();
	PosicionInicialEnemigo = GetActorLocation();
}

// Called every frame
void AEnemigoPadre::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (EpuedeMoverse)
	{
		FVector NewLocation = PosicionInicialEnemigo;
		NewLocation.Y = PosicionInicialEnemigo.Y + FMath::Sin(GetGameTimeSinceCreation() * SpeedEnemigo) * 100.0f;
		SetActorLocation(NewLocation);
	}

}

// Called to bind functionality to input
void AEnemigoPadre::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

