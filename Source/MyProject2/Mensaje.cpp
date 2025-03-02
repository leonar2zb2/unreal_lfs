// Fill out your copyright notice in the Description page of Project Settings.

#include "Mensaje.h"
void UMensaje::PrintString(FString cadena, bool EnPantalla, bool EnLog, FColor Color, int Clave, FString &Devuelta)
{
    if (EnLog)
        UE_LOG(LogTemp, Warning, TEXT("Aquí se imprime %s"), *cadena);
    if (EnPantalla && GEngine)
        GEngine->AddOnScreenDebugMessage(Clave, Tiempo, Color, *cadena);
    Devuelta = "Ejecutado correctamente";
}

UMensaje::UMensaje()
{
    Tiempo = 5.0f;
}