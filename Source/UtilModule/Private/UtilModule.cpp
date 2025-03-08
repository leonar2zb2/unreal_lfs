// Fill out your copyright notice in the Description page of Project Settings.

#include "UtilModule.h"
#include "Modules/ModuleManager.h"

void FUtilModule::StartupModule()
{
    UE_LOG(LogTemp, Warning, TEXT("Módulo iniciado"));
}

void FUtilModule::ShutdownModule()
{
    UE_LOG(LogTemp, Warning, TEXT("Módulo finalizado"));
}

IMPLEMENT_MODULE(FUtilModule, UtilModule);
