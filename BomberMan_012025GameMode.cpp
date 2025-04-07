// Copyright Epic Games, Inc. All Rights Reserved.

#include "BomberMan_012025GameMode.h"
#include "BomberMan_012025Character.h"
#include "UObject/ConstructorHelpers.h"
#include "Bloque.h"
#include "BloqueAcero.h"
#include "BloqueConcreto.h"
#include "BloqueAgua.h"
#include "BloqueLadrillo.h"
#include "BloqueCesped.h"
#include "BloqueArena.h"	
#include "BloqueMadera.h"
#include "BloqueRoca.h"
#include "BloqueOro.h"
#include "BloqueVidrio.h"
#include "EnemigoPadre.h"

ABomberMan_012025GameMode::ABomberMan_012025GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ABomberMan_012025GameMode::BeginPlay()
{
	Super::BeginPlay();

	GEngine->AddOnScreenDebugMessage(-1, -1, FColor::Red, TEXT("Bloque Spawning"));

	// Recorremos la matriz para generar los bloques
	for (int32 fila = 0; fila < aMapaBloques.Num(); ++fila)
	{
		for (int32 columna = 0; columna < aMapaBloques[fila].Num(); ++columna)
		{
			int32 valor = aMapaBloques[fila][columna];
			if (valor != 0) // Si no es espacio vacío
			{
				// Calculamos la posición del bloque
				FVector posicionBloque = FVector(
					XInicial + columna * AnchoBloque,
					YInicial + fila * LargoBloque,
					20.0f); // Z queda en 0 (altura del bloque)

				// Llamamos a la función para generar un bloque
				SpawnBloque(posicionBloque, valor);
				SpawnEnemigo(posicionBloque, valor);
			}
		}
	}

	GetWorld()->GetTimerManager().SetTimer(tHDestruirBloques, this, &ABomberMan_012025GameMode::DestruirBloque, 2.0f, true);

}

void ABomberMan_012025GameMode::SpawnBloque(FVector posicionBloque, int32 tipoBloque)
{
	ABloque* BloqueGenerado = nullptr;
	switch (tipoBloque)
	{
	case 1: BloqueGenerado = GetWorld()->SpawnActor<ABloqueAcero>(ABloqueAcero::StaticClass(), posicionBloque, FRotator(0.0f, 0.0f, 0.0f));
		break;
	case 2: BloqueGenerado = GetWorld()->SpawnActor<ABloqueConcreto>(ABloqueConcreto::StaticClass(), posicionBloque, FRotator(0.0f, 0.0f, 0.0f));
		break;
	case 3: BloqueGenerado = GetWorld()->SpawnActor<ABloqueAgua>(ABloqueAgua::StaticClass(), posicionBloque, FRotator(0.0f, 0.0f, 0.0f));
		break;
	case 4: BloqueGenerado = GetWorld()->SpawnActor<ABloqueLadrillo>(ABloqueLadrillo::StaticClass(), posicionBloque, FRotator(0.0f, 0.0f, 0.0f));
		break;
	case 5: BloqueGenerado = GetWorld()->SpawnActor<ABloqueCesped>(ABloqueCesped::StaticClass(), posicionBloque, FRotator(0.0f, 0.0f, 0.0f));
		break;
	case 6: BloqueGenerado = GetWorld()->SpawnActor<ABloqueMadera>(ABloqueMadera::StaticClass(), posicionBloque, FRotator(0.0f, 0.0f, 0.0f));
		break;
	case 7: BloqueGenerado = GetWorld()->SpawnActor<ABloqueRoca>(ABloqueRoca::StaticClass(), posicionBloque, FRotator(0.0f, 0.0f, 0.0f));
		break;
	case 8: BloqueGenerado = GetWorld()->SpawnActor<ABloqueOro>(ABloqueOro::StaticClass(), posicionBloque, FRotator(0.0f, 0.0f, 0.0f));
		break;
	case 9: BloqueGenerado = GetWorld()->SpawnActor<ABloqueVidrio>(ABloqueVidrio::StaticClass(), posicionBloque, FRotator(0.0f, 0.0f, 0.0f));
		break;
	case 10: BloqueGenerado = GetWorld()->SpawnActor<ABloqueArena>(ABloqueArena::StaticClass(), posicionBloque, FRotator(0.0f, 0.0f, 0.0f));
		break;
	default:
		break;
	}
	if (BloqueGenerado)
	{
		aBloques.Add(BloqueGenerado);
	}
}
void ABomberMan_012025GameMode::SpawnEnemigo(FVector posicion, int32 tipoEnemigo)
{
	AEnemigoPadre* EnemigoGenerado = nullptr;
	switch (tipoEnemigo)
	{
	case 11: EnemigoGenerado = GetWorld()->SpawnActor<AEnemigoPadre>(AEnemigoPadre::StaticClass(), posicion, FRotator(0.0f, 0.0f, 0.0f));
		break;
	default:
		break;
	}
	if (EnemigoGenerado)
	{
		aEnemigos.Add(EnemigoGenerado);
	}
}
void ABomberMan_012025GameMode::DestruirBloque()
{
	int numeroBloques = aBloques.Num();
	int NumeroAleatorio = FMath::RandRange(2, numeroBloques);

	if (aBloques.Num() > 0)
	{
		BloqueActual = aBloques[NumeroAleatorio]; // Obtén el primer bloque
		if (BloqueActual)
		{
			BloqueActual->Destroy();
			// Realiza operaciones con el bloque
			//primerBloque->SetActorLocation(FVector(100.0f, 100.0f, 100.0f));
		}
	}
}

void ABomberMan_012025GameMode::EliminarEnemigo()
{
}



