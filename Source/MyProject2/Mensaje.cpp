// Fill out your copyright notice in the Description page of Project Settings.

#include "Mensaje.h"
void UMensaje::MostrarMensaje(FString cadena, bool EnPantalla, bool EnLog, FColor Color, int Clave, FString &Devuelta)
{
    if (EnLog)
        UE_LOG(LogTemp, Warning, TEXT("Aquí se imprime %s"), *cadena);
    if (EnPantalla && GEngine)
        GEngine->AddOnScreenDebugMessage(Clave, Tiempo, Color, *cadena);
    Devuelta = "Termina de mostrar la cadena";
}

UMensaje::UMensaje()
{
    Tiempo = 5.0f;
}

bool UMensaje::RestableceTiempo()
{
    bool diferente;
    diferente = Tiempo != 5.0f;
    Tiempo = 5.0f;
    return diferente;
}