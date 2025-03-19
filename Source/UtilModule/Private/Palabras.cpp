// Fill out your copyright notice in the Description page of Project Settings.

#include "Palabras.h"
#include "Math/UnrealMathUtility.h"

int UPalabras::Agregar(FString cadena)
{
    Almacen.Add(cadena);
    return Almacen.Num();
}

int UPalabras::AgregarMultiples(TArray<FString> cadenas)
{
    Almacen.Append(cadenas);
    return Almacen.Num();
}

void UPalabras::Listar()
{
    for (FString palabra : Almacen)
        UE_LOG(LogTemp, Warning, TEXT("Palabra %s"), *palabra);
}

FString UPalabras::Iniciar(int CuantosIntentos)
{
    int32 RandomValue = -1;
    Seleccionada = "";
    Respuesta = "";
    IntentosRestantes = CuantosIntentos;
    MaxIntentos = CuantosIntentos;
    if (Almacen.Num() > 0)
    {
        RandomValue = FMath::RandRange(0, Almacen.Num() - 1);
        Seleccionada = Almacen[RandomValue];
    }
    for (char letra : Seleccionada)
        Respuesta += '_';
    UE_LOG(LogTemp, Warning, TEXT("Random Value: %d"), RandomValue);
    UE_LOG(LogTemp, Warning, TEXT("Palabra %s"), *Seleccionada);
    return Respuesta;
}

bool UPalabras::ProbarConLetra(FString letra, FString &Resultado, int &IntentosPendientes)
{
    bool Presente = false;
    TCHAR caracter;
    if (!letra.IsEmpty()) // Verificar que la cadena no esté vacía
    {
        caracter = letra[0]; // Tomar el primer carácter
        for (int i = 0; i < Seleccionada.Len(); i++)
            if (FChar::ToLower(Seleccionada[i]) == FChar::ToLower(caracter))
            {
                Presente = true;
                Respuesta[i] = Seleccionada[i];
            }
    }
    if (!Presente)
        IntentosRestantes--;
    IntentosPendientes = IntentosRestantes;
    Resultado = Respuesta;

    if (Resultado == Seleccionada)
    {
        if (Adivinado.IsBound())
        {
            if (GEngine)
                GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, TEXT("Ocurrio el EVENTO ha adivinado!"));
            Adivinado.Broadcast();
        }
    }

    return Presente;
}

FString UPalabras::Revelar(bool &Revelado)
{
    Revelado = IntentosRestantes <= 0;
    if (Revelado)
        return Seleccionada;
    return FString::ChrN(Seleccionada.Len(), TEXT('*'));
}