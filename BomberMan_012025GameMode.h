
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BomberMan_012025GameMode.generated.h"

class ABloque;

UCLASS(minimalapi)
class ABomberMan_012025GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABomberMan_012025GameMode();
public:
	void virtual BeginPlay() override;

public:
	// Declarar la posición del siguiente bloque
	FVector posicionSiguienteBloque = FVector(1000.0f, 500.0f, 20.0f);

	// Declarar un mapa de bloques como un array bidimensional
	TArray<TArray<int32>> aMapaBloques;
	
	TArray<ABloque*> aBloques;
	float XInicial = -2500.00f;
	float YInicial = -2500.00f;
	float AnchoBloque = 100.0f;
	float LargoBloque = 100.0f;
	TSubclassOf<APawn> MiClaseDePersonaje;
	ABloque* BloqueActual = nullptr;
	// Declarar un array de punteros a objetos de tipo BloqueMadera
	FTimerHandle TemporizadorInicial;
	TArray<FVector> aEspaciosVacios;
	FTimerHandle tHDestruirBloques;
	TArray<FVector> aEspaciosVaciosBordes;
	TArray<ABloque*> aBloquesLadrillo;
	void IniciarDesaparicionBloquesMadera();
	void SpawnPersonaje();
	//void MoverBloques();
	//void SpawnBloques();
	void SpawnBloque(FVector posicion, int32 tipoBloque);

	void DestruirBloque();


};




