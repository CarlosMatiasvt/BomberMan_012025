// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bloque.h"
#include "BloqueRoca.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMAN_012025_API ABloqueRoca : public ABloque
{
	GENERATED_BODY()
	

public:
	ABloqueRoca();
protected:
	void virtual BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;

};
