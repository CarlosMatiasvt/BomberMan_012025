// Fill out your copyright notice in the Description page of Project Settings.


#include "BloqueAgua.h"

ABloqueAgua::ABloqueAgua() {

	static ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("Material'/Game/StarterContent/Materials/M_Water_Ocean.M_Water_Ocean'"));
	if (Material.Succeeded())
	{
		MallaBloque->SetMaterial(0, Material.Object);
	}
	FloatSpeed = 3.0f;
	RotationSpeed = 3.0f;
	bPuedeMoverse = false;
}


