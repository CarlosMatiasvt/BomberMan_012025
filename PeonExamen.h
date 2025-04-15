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

	// Posici�n del pe�n en la cuadr�cula
	int32 FilaActual;
	int32 ColumnaActual;

	// Velocidad de movimiento del pe�n
	UPROPERTY(EditAnywhere)
	float VelocidadMovimiento;

	// Direcci�n en la que se mueve el pe�n
	FVector DireccionMovimiento;

	// L�gica que mueve al pe�n
	void Mover();

public:
	// Llamado cada frame
	virtual void Tick(float DeltaTime) override;

	// Llamado al inicio del juego
	virtual void BeginPlay() override;
};
