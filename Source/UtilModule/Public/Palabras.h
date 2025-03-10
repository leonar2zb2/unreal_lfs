// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Palabras.generated.h"

/**
 *
 */
UCLASS(Blueprintable)
class UTILMODULE_API UPalabras : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Palabras")
	int Agregar(FString cadena);

	UFUNCTION(BlueprintCallable, Category = "Palabras")
	void Listar();

private:
	TArray<FString> Almacen;
};
