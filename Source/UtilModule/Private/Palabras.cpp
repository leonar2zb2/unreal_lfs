// Fill out your copyright notice in the Description page of Project Settings.

#include "Palabras.h"
#include "Math/UnrealMathUtility.h"
#include "JsonObjectConverter.h"
#include "Http.h"

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
            Adivinado.Broadcast(Resultado);
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

void UPalabras::DescargarDesdeApi()
{
    FHttpRequestPtr HttpRequest = FHttpModule::Get().CreateRequest();
    HttpRequest->OnProcessRequestComplete().BindUObject(this, &UPalabras::HandleListarPalabras);
    HttpRequest->SetVerb("GET");
    FString fullURL = API_URL;
    fullURL += TEXT("palabras");
    HttpRequest->SetURL(fullURL);
    HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
    HttpRequest->SetHeader(TEXT("Accept"), TEXT("application/json"));
    GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, *fullURL);
    HttpRequest->ProcessRequest();
}

void UPalabras::HandleListarPalabras(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    FPalabrasResponse lista;
    if (!bWasSuccessful)
    {
        lista.message = TEXT("Error de red: Revise conexión, DNS, Firewall");
        if (RespuestaListando.IsBound())
            RespuestaListando.Broadcast(lista);
        return;
    }

    if (!Response || Response->GetResponseCode() != 200)
    {
        lista.message = TEXT("Error de respuesta del API");
        if (RespuestaListando.IsBound())
            RespuestaListando.Broadcast(lista);
        return;
    }

    FString ResponseCall = Response->GetContentAsString();
    if (!FJsonObjectConverter::JsonObjectStringToUStruct(ResponseCall, &lista, 0, 0))
    {
        lista.message = TEXT("Estructura recibida del API no es JSON o es incompatible");
        if (RespuestaListando.IsBound())
            RespuestaListando.Broadcast(lista);
        return;
    }

    if (lista.data.Num() == 0)
    {
        lista.success = false;
        lista.message = TEXT("Ninguna cadena fué devuelta");
        if (RespuestaListando.IsBound())
            RespuestaListando.Broadcast(lista);
        return;
    }

    lista.message = TEXT("Listado de palabras");
    lista.success = true;
    RespuestaListando.Broadcast(lista);
}

/*
   También existe la posibilidad de parsear el JSON manualmente usando FJsonSerializer::Deserialize()
 y acceder a cada campo uno por uno con JsonObject->GetStringField(), JsonObject->GetBoolField(), etc.
 Esta alternativa es más flexible (por ejemplo, para validar o transformar datos antes de asignarlos),
 pero también es más laboriosa y compleja de mantener, por lo que solo la recomendamos en casos donde
 el JSON tenga una estructura muy irregular o cuando necesites un control muy fino sobre la deserialización.
 Necesita además otros includes:
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
*/