// Fill out your copyright notice in the Description page of Project Settings.


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

ABloque* UFabricaBloques::CrearBloque(UWorld* World, int TipoBloque, FVector Posicion)
{
    if (!World) return nullptr;

    TSubclassOf<ABloque> ClaseBloque = nullptr;

    switch (TipoBloque)
    {
    case 0:
        ClaseBloque = ABloqueAcero::StaticClass();
        break;
    case 1:
        ClaseBloque = ABloqueLadrillo::StaticClass();
        break;
    case 2:
        ClaseBloque = ABloqueMadera::StaticClass();
        break;
    case 3:
        ClaseBloque = ABloqueAgua::StaticClass();
        break;
	case 4:
		ClaseBloque = ABloqueConcreto::StaticClass();
		break;
	case 5:
		ClaseBloque = ABloqueCesped::StaticClass();
		break;
	case 6:
		ClaseBloque = ABloqueRoca::StaticClass();
		break;
	case 7:
		ClaseBloque = ABloqueOro::StaticClass();
		break;
	case 8:
		ClaseBloque = ABloqueVidrio::StaticClass();
		break;
	case 9:
		ClaseBloque = ABloqueArena::StaticClass();
		break;
    default:
        UE_LOG(LogTemp, Warning, TEXT("Tipo de bloque inválido: %d"), TipoBloque);
        return nullptr;
    }

    return World->SpawnActor<ABloque>(ClaseBloque, Posicion, FRotator::ZeroRotator);
}