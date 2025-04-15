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
#include "Kismet/GameplayStatics.h"
#include "PeonExamen.h"


ABomberMan_012025GameMode::ABomberMan_012025GameMode()
{
	DefaultPawnClass = nullptr;

	// Opcional: asignar clase manualmente si no lo hacés desde el editor
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		MiClaseDePersonaje = PlayerPawnBPClass.Class;
	}
}

void ABomberMan_012025GameMode::BeginPlay()
{
	Super::BeginPlay();

	GEngine->AddOnScreenDebugMessage(-1, -1, FColor::Red, TEXT("Bloque Spawning"));
	aMapaBloques.SetNum(50);
	for (int32 i = 0; i < 50; i++) {
		aMapaBloques[i].SetNum(50);
	}
	for (int32 tipo = 1; tipo <= 10; ++tipo)
	{
		int32 fila = FMath::RandRange(0, 49);
		int32 columna = FMath::RandRange(0, 29);

		// Si ya hay un bloque distinto de 0, busca otra posición
		while (aMapaBloques[fila][columna] != 0)
		{
			fila = FMath::RandRange(0, 49);
			columna = FMath::RandRange(0, 49);
		}

		aMapaBloques[fila][columna] = tipo;
	}
	for (int32 i = 1; i <= 200; ++i)
	{

		int32 fila = FMath::RandRange(0, 49);
		int32 columna = FMath::RandRange(0, 49);
		int32 tipo = FMath::RandRange(1, 10); // Genera un número aleatorio entre 1 y 10

		// Si ya hay un bloque distinto de 0, busca otra posición
		while (aMapaBloques[fila][columna] != 0)
		{
			fila = FMath::RandRange(0, 49);
			columna = FMath::RandRange(0, 49);
		}

		aMapaBloques[fila][columna] = tipo;
	}

	
	/*for (int32 i = 0; i < 30; i++)
	{
		for (int32 j = 0; j < 30; j++)
		{
			if (aMapaBloques[i][j] == 0)
			{
				int32 elemento = FMath::RandRange(0, 10); // 0 = vacío
				aMapaBloques[i][j] = elemento;
			}
		}
	}*/
	// Recorremos la matriz para generar los bloques
	for (int32 fila = 0; fila < aMapaBloques.Num(); ++fila)
	{
		for (int32 columna = 0; columna < aMapaBloques[fila].Num(); ++columna)
		{
			
			int32 valor = aMapaBloques[fila][columna];
			// Calculamos la posición del bloque

			FVector posicionBloque = FVector(
				XInicial + columna * AnchoBloque,
				YInicial + fila * LargoBloque,
				20.0f); // Z queda en 0 (altura del bloque)
			if (valor != 0) // Si no es espacio vacío
			{
				// Llamamos a la función para generar un bloque
				SpawnBloque(posicionBloque, valor);
			}
			else {
				aEspaciosVacios.Add(posicionBloque);
				if (fila == 0 || fila == 24 || columna == 0 || columna == 49) {
					aEspaciosVaciosBordes.Add(posicionBloque);
				}
			}
			
		}
	}

	if (aEspaciosVaciosBordes.Num() > 0 && MiClaseDePersonaje)
	{
		int32 indiceAleatorio = FMath::RandRange(0, aEspaciosVaciosBordes.Num() - 1);
		FVector posicionInicial = aEspaciosVaciosBordes[indiceAleatorio];

		// Spawn del personaje

		FActorSpawnParameters spawnParams;
		APawn* personaje = GetWorld()->SpawnActor<APawn>(MiClaseDePersonaje, posicionInicial, FRotator::ZeroRotator, spawnParams);

		// Asignar control
		APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (PC && personaje)
		{
			PC->Possess(personaje);
		}
	}
	int32 filaInicial = 0;  // O cualquier fila de borde que elijas
	int32 columnaInicial = 0;  // O cualquier columna de borde que elijas

	FVector posicionInicial = FVector(XInicial + columnaInicial * AnchoBloque, YInicial + filaInicial * LargoBloque, 20.0f);
	APeonExamen* Peon = GetWorld()->SpawnActor<APeonExamen>(APeonExamen::StaticClass(), posicionInicial, FRotator::ZeroRotator);	GetWorld()->GetTimerManager().SetTimer(TemporizadorInicial,this,&ABomberMan_012025GameMode::IniciarDesaparicionBloquesMadera,10.0f,false);

}

void ABomberMan_012025GameMode::IniciarDesaparicionBloquesMadera()
{
	if (aBloques.Num() > 0)
	{
		GetWorld()->GetTimerManager().SetTimer(tHDestruirBloques, this, &ABomberMan_012025GameMode::DestruirBloque, 5.0f, true);

	}
}

void ABomberMan_012025GameMode::SpawnPersonaje()
{

}

/*/void ABomberMan_012025GameMode::MoverBloques()
{
	int32 cantidadMovibles = 0;
	while (cantidadMovibles < 4 && aBloques.Num() > 0)
	{
		int32 indice = FMath::RandRange(0, aBloques.Num() - 1);
		if (aBloques[indice])
		{
			aBloques[indice]->bPuedeMoverse = true;
			cantidadMovibles++;
			aBloques.RemoveAt(indice); // Evita duplicados
		}
	}
}*/

void ABomberMan_012025GameMode::SpawnBloque(FVector posicionBloque, int32 tipoBloque)
{
	ABloque* BloqueGenerado = nullptr;
	int32 fila = (posicionBloque.Y - YInicial) / LargoBloque;
	int32 columna = (posicionBloque.X - XInicial) / AnchoBloque;
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

void ABomberMan_012025GameMode::DestruirBloque()
{
	int numeroBloques = aBloques.Num();
	int NumeroAleatorio = FMath::RandRange(0, numeroBloques);

	if (aBloques.Num() > 0)
	{
		BloqueActual = aBloques[NumeroAleatorio]; // Obtén el primer bloque
		if (BloqueActual)
		{
			BloqueActual->Destroy(); // Destruye el bloque
			GEngine->AddOnScreenDebugMessage(-1, -1, FColor::Red, TEXT("Bloque Eliminado"));


			// Realiza operaciones con el bloque
			//primerBloque->SetActorLocation(FVector(100.0f, 100.0f, 100.0f));
		}
	}
	else
	{
		// Cuando se destruyen todos, detenemos el timer
		GetWorld()->GetTimerManager().ClearTimer(tHDestruirBloques);
	}
}





