// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Mensaje.generated.h"

/**
 *
 */
UCLASS(Blueprintable)
class MYPROJECT2_API UMensaje : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Mis métodos")
	void MostrarMensaje(FString cadena, bool EnPantalla, bool EnLog, FColor Color, int Clave, FString &Devuelta);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Tiempo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int valor;

	UMensaje();

	UFUNCTION(BlueprintCallable, Category = "Mis métodos")
	bool RestableceTiempo();
};
