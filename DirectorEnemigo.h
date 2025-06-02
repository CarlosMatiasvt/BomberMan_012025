// Fill out your copyright notice in the Description page of Project Settings.
// ----------- DirectorEnemigo.h -----------

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuilderEnemigoAbstracto.h"
#include "DirectorEnemigo.generated.h"

// Clase director que se encarga del proceso de construcción del ejército podemos añadir cantidades de ejercitos y llamarlos
//por este director

UCLASS()
class BOMBERMAN_012025_API ADirectorEnemigo : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADirectorEnemigo();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:
	// Builder que se usará para construir
	UPROPERTY(EditAnywhere, Category = "Builder")
	//EL DIRECTOR CREA UN PUNTERO BUILDER QUE APUNTA A BUILDERENEMIGOABSTRACTO
	ABuilderEnemigoAbstracto* Builder;

	// Función que ordena construir todo el ejército
	void ConstruirEjercito(const TArray<FVector>& PosicionesLibres);
	void ConstruirEjercito2(const TArray<FVector>& PosicionesLibres);

};
