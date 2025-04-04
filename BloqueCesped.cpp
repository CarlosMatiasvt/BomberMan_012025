// Fill out your copyright notice in the Description page of Project Settings.


#include "BloqueCesped.h"

ABloqueCesped::ABloqueCesped()
{
	static ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("Material'/Game/StarterContent/Materials/M_Ground_Moss.M_Ground_Moss'"));
	if (Material.Succeeded())
	{
		MallaBloque->SetMaterial(0, Material.Object);
	}
	FloatSpeed = 3.0f;
	RotationSpeed = 3.0f;

	bPuedeMoverse = FMath::RandBool();
}


