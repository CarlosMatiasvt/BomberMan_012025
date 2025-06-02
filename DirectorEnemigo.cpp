// Fill out your copyright notice in the Description page of Project Settings.
// ----------- DirectorEnemigo.cpp -----------


#include "DirectorEnemigo.h"


// Sets default values
ADirectorEnemigo::ADirectorEnemigo()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADirectorEnemigo::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADirectorEnemigo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADirectorEnemigo::ConstruirEjercito(const TArray<FVector>& PosicionesLibres)
{
	if (!Builder) return; // Asegura que haya un builder asignado

	// Llama a los métodos en orden para construir el ejército
	Builder->ConstruirComandante(PosicionesLibres);
	Builder->ConstruirTipo1(PosicionesLibres);
	Builder->ConstruirTipo2(PosicionesLibres);
}

void ADirectorEnemigo::ConstruirEjercito2(const TArray<FVector>& PosicionesLibres)
{
	if (!Builder) return; // Asegura que haya un builder asignado
	// Llama a los métodos en orden para construir el ejército
	Builder->ConstruirComandante(PosicionesLibres);
	Builder->ConstruirTipo3(PosicionesLibres);
	Builder->ConstruirTipo4(PosicionesLibres);
}

