// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CanvasPanel.h"
#include "GameMenuCanvas.generated.h"

/**
 * 
 */
UCLASS()
class THEESCAPER_API UGameMenuCanvas : public UCanvasPanel
{
	GENERATED_BODY()

public:
	int GetCanvasIndex() const { return index; }

private:
	UPROPERTY(EditDefaultsOnly, Category = "Value")
	int index;
	
};
