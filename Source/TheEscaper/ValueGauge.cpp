// Fill out your copyright notice in the Description page of Project Settings.


#include "ValueGauge.h"
#include "Components/Image.h"

void UValueGauge::SetValue(float newValue, float delta, float max)
{
	valueImage->GetDynamicMaterial()->SetScalarParameterValue(ValueParamName, newValue / max);

}
