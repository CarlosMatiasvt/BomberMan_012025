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
	if (bPuedeMoverse)
	{
		FVector NewLocation = PosicionInicial;
	    NewLocation.Z = FMath::Sin(GetGameTimeSinceCreation() * FloatSpeed) * 170.0f + 230.0f;
		SetActorLocation(NewLocation);
	}
	//if (bPuedeMoverse)
	//{
		//FVector NewLocation = GetActorLocation();
		//FRotator NewRotation = GetActorRotation();
		//float RunningTime = GetGameTimeSinceCreation();

		// Aleatoriedad en el desplazamiento en Z
		//float DeltaHeight = (-3.0f, 3.0f) * FloatSpeed;
		//NewLocation.Z = FMath::Sin(GetGameTimeSinceCreation() * FloatSpeed) * 170.0f + 300.0f;


		// Asegurarse de que el bloque no se mueva más allá del suelo
		// Limitar la posición Z para que no vaya más abajo que el valor 0
		//NewLocation.Z = FMath::Clamp(NewLocation.Z, 0.0f, 500.0f); // El bloque no irá más abajo que 0, ni más arriba que 500
		// Aleatoriedad en la rotación
		//float DeltaRotation = FMath::FRandRange(-1.0f, 1.0f) * RotationSpeed;
		//NewRotation.Yaw += DeltaRotation;

		//SetActorLocation(NewLocation);

		//SetActorLocationAndRotation(NewLocation, NewRotation);
	//}*/
}


