#pragma once

#include "CoreMinimal.h"
#include "Response.generated.h"

/**
 * Estructura básica con campos comunes a cualquier respuesta del API
 *
 */
USTRUCT(BlueprintType, Category = "Estructura API|Estructura matriz")
struct FResponseAPI
{
    GENERATED_USTRUCT_BODY()
    /**
     * Resultado de la operación: true => ok, false => error.
     */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (ToolTip = "Resultado de la operación: true => ok, false => error"))
    bool success = false;

    /**
     * Mensaje descriptivo de la operación.
     */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (ToolTip = "Mensaje descriptivo de la operación"))
    FString message;

    /**
     * Lista de errores en caso de fallo.
     */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (ToolTip = "Lista de errores en caso de fallo"))
    TArray<FString> errors;
};

USTRUCT(BlueprintType, Category = "Estructura API|Respuesta lista palabras")
struct FPalabrasResponse : public FResponseAPI
{
    GENERATED_USTRUCT_BODY()
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TArray<FString> data;
};