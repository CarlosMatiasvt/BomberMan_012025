// Fill out your copyright notice in the Description page of Project Settings.


#include "Bloque.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/Material.h"
#include "GameFramework/Actor.h"

// Sets default values
ABloque::ABloque()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MallaBloque = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MallaBloque"));
	RootComponent = MallaBloque;

	
	MallaBloque->SetupAttachment(RootComponent);
	MallaBloque->SetWorldScale3D(FVector(1.0f, 1.0f, 3.0f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh>ObjetoMallaBloque(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));

	if (ObjetoMallaBloque.Succeeded())
	{
		MallaBloque->SetStaticMesh(ObjetoMallaBloque.Object);

		MallaBloque->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	}
	// ?? Activar colisiones
	MallaBloque->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MallaBloque->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	MallaBloque->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	FloatSpeed = 5.0f;
	RotationSpeed = 3.0f;

	bPuedeMoverse = FMath::RandBool();
	 
}

// Called when the game starts or when spawned
void ABloque::BeginPlay()
{
	Super::BeginPlay();
	PosicionInicial = GetActorLocation();
	
	
}

// Called every frame
void ABloque::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}


