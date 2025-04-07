// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemigoPadre.generated.h"

class UStaticMeshComponent;

UCLASS()
class BOMBERMAN_012025_API AEnemigoPadre : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemigoPadre();
	UStaticMeshComponent* MallaEnemigo;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	float SpeedEnemigo;
	bool EpuedeMoverse;
	FVector  PosicionInicialEnemigo;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
