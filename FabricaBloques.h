// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FabricaBloques.generated.h"

/**
 * 
 */
class ABloque;
UCLASS()
class BOMBERMAN_012025_API UFabricaBloques : public UObject
{
	GENERATED_BODY()
public:

public:
	ABloque* CrearBloque(UWorld* World, int TipoBloque, FVector Posicion);

	
};
