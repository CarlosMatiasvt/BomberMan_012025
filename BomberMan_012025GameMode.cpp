// Copyright Epic Games, Inc. All Rights Reserved.

#include "BomberMan_012025GameMode.h"
#include "BomberMan_012025Character.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "FabricaBloques.h"
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
#include "BuilderConcretoEjercito.h"
#include "BuilderConcretoEjercito2.h"
#include "DirectorEnemigo.h"





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
	// Inicializar el mapa de bloques
	aMapaBloques.SetNum(50);
	for (int32 i = 0; i < 50; i++) {
		aMapaBloques[i].SetNum(50);
	}
	//se encarga de generar aunquesea  un bloque de cada tipo
	for (int32 tipo = 1; tipo <= 9; ++tipo)
	{
		int32 fila = FMath::RandRange(1, 48);
		int32 columna = FMath::RandRange(1, 48);

		// Si ya hay un bloque distinto de 0, busca otra posición
		while (aMapaBloques[fila][columna] != 0)
		{
			fila = FMath::RandRange(1, 48);
			columna = FMath::RandRange(1, 48);
		}

		aMapaBloques[fila][columna] = tipo;
	}
	//generamos los demas bloques
	for (int32 i = 1; i <= 180; ++i)
	{

		int32 fila = FMath::RandRange(1, 48);
		int32 columna = FMath::RandRange(1, 48);
		int32 tipo = FMath::RandRange(1, 9); // Genera un número aleatorio entre 1 y 10

		// Si ya hay un bloque distinto de 0, busca otra posición
		while (aMapaBloques[fila][columna] != 0)
		{
			fila = FMath::RandRange(1, 48);
			columna = FMath::RandRange(1, 48);
		}

		aMapaBloques[fila][columna] = tipo;
	}

	//fabrica de bloques
	UFabricaBloques* Fabrica = NewObject<UFabricaBloques>();




	
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
			if (valor == 0) // Si es espacio vacío
			{
				if (fila == 0 || fila == 49 || columna == 0 || columna == 49) {
					//spawnear los limited con acero
					ABloque* NuevoBloque = Fabrica->CrearBloque(GetWorld(), 0, posicionBloque); 
				}
				else {
					// Añadir la posición a los espacios vacíos
					aEspaciosVacios.Add(posicionBloque);
				}
			}
			else {
				// Spawn del bloque usando la fábrica
				ABloque* NuevoBloque = Fabrica->CrearBloque(GetWorld(), valor, posicionBloque);
				//spawnear a un enemigo
			
			}
			
		}
	}
	//Spawnea el personaje xd
	SpawnPersonaje();
	 
	FActorSpawnParameters Params;
	// Configuramos los parámetros de spawn
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	// Spawn de enemigos
	// Creamos el director de enemigos LLAMADO DIRECTOR QUE APUNTO A DIRECTORENEMIGOS
	ADirectorEnemigo* Director = GetWorld()->SpawnActor<ADirectorEnemigo>(ADirectorEnemigo::StaticClass());
	// Creamos el builder concreto ESTE BUILDER APUNTA AL BUILDERCONCRETOEJERCITO QUE NOS PERMITE SPAWNEAR A LOS ENEMIGOS
	ABuilderConcretoEjercito* Builder = GetWorld()->SpawnActor<ABuilderConcretoEjercito>(ABuilderConcretoEjercito::StaticClass());
	// Asignamos el builder al director
	//ESTE DIRECTOR APUNTA AL BUILDER QUE YA TENEMOS EN EL DIRECTORENEMIGOS LO QUE HACE ESO ES POLIMORFISMO YA QUE A ESTO LE ASIGNAMOS
	//EL NUEVO BUILDER QUE ES EL BUILDERCONCRETOEJERCITO
	// Esto es polimorfismo, el director puede usar cualquier builder que herede de ABuilderEnemigoAbstracto
	Director->Builder = Builder;
	// Llamamos al director para construir el ejército
	Director->ConstruirEjercito(aEspaciosVacios);
	// Creamos el director de enemigos 2
	ADirectorEnemigo* Director2 = GetWorld()->SpawnActor<ADirectorEnemigo>(ADirectorEnemigo::StaticClass());
	// Creamos el builder concreto 2
	ABuilderConcretoEjercito2* Builder2 = GetWorld()->SpawnActor<ABuilderConcretoEjercito2>(ABuilderConcretoEjercito2::StaticClass());
	// Asignamos el builder al director 2
	Director2->Builder = Builder2;
	// Llamamos al director 2 para construir el segundo ejército
	Director2->ConstruirEjercito2(aEspaciosVacios);


}

void ABomberMan_012025GameMode::IniciarDesaparicionBloquesMadera()
{
	// Recorremos todos los bloques y los agregamos al array aBloques
	if (aBloques.Num() > 0)
	{
		GetWorld()->GetTimerManager().SetTimer(tHDestruirBloques, this, &ABomberMan_012025GameMode::DestruirBloque, 5.0f, true);

	}
}

void ABomberMan_012025GameMode::SpawnPersonaje()
{
	if (aEspaciosVacios.Num() > 0 && MiClaseDePersonaje)
	{
		int32 indiceAleatorio = FMath::RandRange(0, aEspaciosVacios.Num() - 1);
		FVector posicionInicial = aEspaciosVacios[indiceAleatorio];

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





