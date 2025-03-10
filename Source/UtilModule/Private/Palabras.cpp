// Fill out your copyright notice in the Description page of Project Settings.

#include "Palabras.h"

int UPalabras::Agregar(FString cadena)
{
    Almacen.Add(cadena);
    return Almacen.Num();
}

void UPalabras::Listar()
{
    for (FString palabra : Almacen)
        UE_LOG(LogTemp, Warning, TEXT("Palabra %s"), *palabra);
}