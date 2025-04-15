// Fill out your copyright notice in the Description page of Project Settings.

#include "PeonExamen.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "BomberMan_012025GameMode.h"

// Constructor
APeonExamen::APeonExamen()
{
	PrimaryActorTick.bCanEverTick = true;

	// Crear el componente de malla
	MallaPeon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MallaPeon"));
	RootComponent = MallaPeon;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cylinder.Shape_Cylinder'"));
	if (MeshAsset.Succeeded())
	{
		MallaPeon->SetStaticMesh(MeshAsset.Object);
	}

	FilaActual = 1;  // Ejemplo, puedes pasar la fila inicial desde el GameMode
	ColumnaActual = 1;  // Ejemplo, puedes pasar la columna inicial desde el GameMode
	VelocidadMovimiento = 100.0f;
	DireccionMovimiento = FVector(1, 0, 0); // Mover a la derecha por defecto
}

// Llamado al principio
void APeonExamen::BeginPlay()
{
	Super::BeginPlay();
	DireccionMovimiento = FVector(1, 0, 0); // Mover a la derecha

}

// Llamado cada frame
void APeonExamen::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Mover al pe�n solo si tiene una direcci�n v�lida
	if (DireccionMovimiento != FVector(0, 0, 0))
	{
		Mover();
	}
	// Mover al pe�n
	
}

void APeonExamen::Mover()
{
	// Buscar GameMode para acceder a la cuadr�cula de bloques
	ABomberMan_012025GameMode* GameMode = Cast<ABomberMan_012025GameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!GameMode) {
		UE_LOG(LogTemp, Warning, TEXT("GameMode no encontrado"));
		return;
	}

	int32 NuevaFila = FilaActual + DireccionMovimiento.Y;
	int32 NuevaColumna = ColumnaActual + DireccionMovimiento.X;

	// Verificar si el espacio est� libre (0 en la matriz)
	if (NuevaFila >= 0 && NuevaFila < 50 && NuevaColumna >= 0 && NuevaColumna < 50)
	{
		if (GameMode->aMapaBloques[NuevaFila][NuevaColumna] == 0)  // Verifica que sea un espacio vac�o
		{
			// Actualizar posici�n en la cuadr�cula
			FilaActual = NuevaFila;
			ColumnaActual = NuevaColumna;

			// Mover f�sicamente el pe�n
			FVector NuevaPos = FVector(
				GameMode->XInicial + ColumnaActual * GameMode->AnchoBloque,
				GameMode->YInicial + FilaActual * GameMode->LargoBloque,
				20.0f);  // Aseg�rate de ajustar el Z correctamente

			SetActorLocation(NuevaPos);
		}
	}
	else
	{
		// Si sale de los l�mites, cambiar direcci�n
		UE_LOG(LogTemp, Warning, TEXT("Fuera de l�mites: (%d, %d)"), NuevaFila, NuevaColumna);
	}
}