// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Palabras.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPalabraAdivinada);
/**
 *
 */
UCLASS(Blueprintable)
class UTILMODULE_API UPalabras : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable, Category = "Event")
	FPalabraAdivinada Adivinado;
	/**
	 * Permite agregar una cadena de texto a las palabras seleccionadas a adivinar
	 * @param cadena La cadena que se desea agregar
	 * @return Cantidad de palabras de la lista a adivinar
	 */
	UFUNCTION(BlueprintCallable, Category = "Palabras")
	int Agregar(FString cadena);

	/**
	 * Agrega en un paso un conjunto de palabras candidatas a adivinar
	 * @param cadenas Arreglo de cadenas a agregar
	 * @return Devuelve la cantidad de palabras totales
	 */
	UFUNCTION(BlueprintCallable, Category = "Palabras")
	int AgregarMultiples(TArray<FString> cadenas);

	/**
	 * Lista todas las palabras agregadas
	 */
	UFUNCTION(BlueprintCallable, Category = "Palabras")
	void Listar();

	/**
	 * Inicia, seleccionando arbitrariamente una palabra de las agregadas
	 * @param CuantosIntentos Define la cantidad de veces a errar admisibles
	 * @return Regresa una cadena formateada con guiones bajos, uno por cada letra de la palabra seleccionada
	 */
	UFUNCTION(BlueprintCallable, Category = "Palabras")
	FString Iniciar(int CuantosIntentos = 5);

	/**
	 * Verifica si una letra está incluida en la palabra secreta
	 * @param letra Letra a intentar buscar
	 * @param Resultado Cadena con las letras ya sustituidas y acumuladas
	 * @param IntentosPendientes Devuelve la cantidad de intentos por realizar
	 */
	UFUNCTION(BlueprintCallable, Category = "Palabras")
	bool ProbarConLetra(FString letra, FString &Resultado, int &IntentosPendientes);

	/**
	 * Devuelve la cadena secreta pero sólo si se agotaron los intentos previstos
	 *
	 * @param Revelado Verdadero si fue revelada, falso en caso contrario
	 * @return Cadena seleccionada o varios asteriscos(*) cuando no debe
	 *
	 */
	UFUNCTION(BlueprintCallable, Category = "Palabras")
	FString Revelar(bool &Revelado);

private:
	TArray<FString> Almacen;
	FString Seleccionada;
	FString Respuesta;
	int MaxIntentos;
	int IntentosRestantes;
};
