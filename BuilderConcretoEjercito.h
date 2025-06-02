// Fill out your copyright notice in the Description page of Project Settings.
// ----------- BuilderConcretoEjercito.h -----------

#pragma once

#include "CoreMinimal.h"
#include "BuilderEnemigoAbstracto.h"
#include "BuilderConcretoEjercito.generated.h"

/**
 * 
 */
 // Builder concreto que implementa los métodos para crear el ejército
UCLASS()
class BOMBERMAN_012025_API ABuilderConcretoEjercito : public ABuilderEnemigoAbstracto
{
	GENERATED_BODY()
	
public:
	// Implementaciones de los pasos del builder
	virtual void ConstruirComandante(const TArray<FVector>& PosicionesLibres) override;
	virtual void ConstruirTipo1(const TArray<FVector>& PosicionesLibres) override;
	virtual void ConstruirTipo2(const TArray<FVector>& PosicionesLibres) override;

private:
	// Función auxiliar para elegir una posición vacía aleatoria
	FVector ObtenerPosicionAleatoria(const TArray<FVector>& PosicionesLibres) const;
};
