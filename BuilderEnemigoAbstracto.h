// Fill out your copyright notice in the Description page of Project Settings.
// ----------- BuilderEnemigoAbstracto.h -----------
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuilderEnemigoAbstracto.generated.h"

// Clase abstracta del Builder, define la interfaz del constructor

UCLASS()
class BOMBERMAN_012025_API ABuilderEnemigoAbstracto : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuilderEnemigoAbstracto();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:
	// Métodos virtual puro: deben ser implementados por clases hijas
	virtual void ConstruirComandante(const TArray<FVector>& PosicionesLibres) PURE_VIRTUAL(ABuilderEnemigoAbstracto::ConstruirComandante, ) ;
	// Construir enemigos de tipo 1, 2, 3 y 4
	// Estos métodos son opcionales, pueden ser implementados o no por las clases hijas
	virtual void ConstruirTipo1(const TArray<FVector>& PosicionesLibres)  {};
	virtual void ConstruirTipo2(const TArray<FVector>& PosicionesLibres)  {};
	virtual void ConstruirTipo3(const TArray<FVector>& PosicionesLibres)  {};
	virtual void ConstruirTipo4(const TArray<FVector>& PosicionesLibres)  {};

};
