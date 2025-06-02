// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BuilderEnemigoAbstracto.h"
#include "BuilderConcretoEjercito2.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMAN_012025_API ABuilderConcretoEjercito2 : public ABuilderEnemigoAbstracto
{
	GENERATED_BODY()
public:
	// Implementaciones de los pasos del builder
	virtual void ConstruirComandante(const TArray<FVector>& PosicionesLibres) override;
	virtual void ConstruirTipo3(const TArray<FVector>& PosicionesLibres) override;
	virtual void ConstruirTipo4(const TArray<FVector>& PosicionesLibres) override;
private:
	// Función auxiliar para elegir una posición vacía aleatoria
	FVector ObtenerPosicionAleatoria(const TArray<FVector>& PosicionesLibres) const;

	
};
