// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PeonExamen.generated.h"

UCLASS()
class BOMBERMAN_012025_API APeonExamen : public APawn
{
	GENERATED_BODY()

public:
	// Constructor
	APeonExamen();

protected:
	// Componente de malla
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MallaPeon;

	// Posición del peón en la cuadrícula
	int32 FilaActual;
	int32 ColumnaActual;

	// Velocidad de movimiento del peón
	UPROPERTY(EditAnywhere)
	float VelocidadMovimiento;

	// Dirección en la que se mueve el peón
	FVector DireccionMovimiento;

	// Lógica que mueve al peón
	void Mover();

public:
	// Llamado cada frame
	virtual void Tick(float DeltaTime) override;

	// Llamado al inicio del juego
	virtual void BeginPlay() override;
};
