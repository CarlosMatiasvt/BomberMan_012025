// Fill out your copyright notice in the Description page of Project Settings.


#include "BloqueAcero.h"

ABloqueAcero::ABloqueAcero()
{
	if (MallaBloque) {
		static ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("Material'/Game/StarterContent/Materials/M_Metal_Burnished_Steel.M_Metal_Burnished_Steel'"));
		if (Material.Succeeded())
		{
			MallaBloque->SetMaterial(0, Material.Object);
		}
	}
}

void ABloqueAcero::BeginPlay()
{
}
