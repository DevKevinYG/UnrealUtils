// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/KismetSystemLibrary.h"
#include "NVTraceHelper.generated.h"

/**
 * This class contains custom traces like the ability to perform capsule traces with rotation
 */
UCLASS()
class CRAFTINGGAME_API UNVTraceHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()


public:
	/**
	* Custom capsule trace collision that uses Center and Rotation as inputs.
	* 
	* @param WorldContext	World context
	* @param Center			The center where this capsule will spawn.
	* @param Rotation		Rotation of the capsule
	* @param Radius		Radius of the capsule to sweep
	* @param HalfHeight	Distance from center of capsule to tip of hemisphere endcap.
	* @param ObjectTypes	Array of Object Types to trace 
	* @param bTraceComplex	True to test against complex collision, false to test against simplified collision.
	* @param OutHit		Properties of the trace hit.
	* @return				True if there was a hit, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, Category="Helper", meta=(bIgnoreSelf="true", WorldContext="WorldContextObject", AutoCreateRefTerm="ActorsToIgnore", DisplayName = "CapsuleTraceForObjects(Rotation)", AdvancedDisplay="TraceColor,TraceHitColor,DrawTime", Keywords="sweep"))
	static bool CustomCapsuleTraceSingleForObjects(const UObject* WorldContextObject, const FVector Center, const FRotator Rotation, float Radius, float HalfHeight, const TArray<TEnumAsByte<EObjectTypeQuery> > & ObjectTypes,
		bool bTraceComplex, const TArray<AActor*>& ActorsToIgnore, EDrawDebugTrace::Type DrawDebugType, FHitResult& OutHit, bool bIgnoreSelf, FLinearColor TraceColor = FLinearColor::Red, FLinearColor TraceHitColor = FLinearColor::Green, float DrawTime = 5.0f);
	
	/**
	* Custom capsule multitrace collision that uses Center and Rotation as inputs.
	* 
	* @param WorldContext	World context
	* @param Center			The center where this capsule will spawn.
	* @param Rotation		Rotation of the capsule
	* @param Radius		Radius of the capsule to sweep
	* @param HalfHeight	Distance from center of capsule to tip of hemisphere endcap.
	* @param ObjectTypes	Array of Object Types to trace 
	* @param bTraceComplex	True to test against complex collision, false to test against simplified collision.
	* @param OutHits		A list of hits, sorted along the trace from start to finish.  The blocking hit will be the last hit, if there was one.
	* @return				True if there was a hit, false otherwise.
	*/
	UFUNCTION(BlueprintCallable, Category="Helper", meta=(bIgnoreSelf="true", WorldContext="WorldContextObject", AutoCreateRefTerm="ActorsToIgnore", DisplayName = "MultiCapsuleTraceForObjects(Rotation)", AdvancedDisplay="TraceColor,TraceHitColor,DrawTime", Keywords="sweep"))
	static bool CustomCapsuleTraceMultiForObjects(const UObject* WorldContextObject, const FVector Center, const FRotator Rotation, float Radius, float HalfHeight, const TArray<TEnumAsByte<EObjectTypeQuery> > & ObjectTypes, bool bTraceComplex,
		const TArray<AActor*>& ActorsToIgnore, EDrawDebugTrace::Type DrawDebugType, TArray<FHitResult>& OutHits, bool bIgnoreSelf, FLinearColor TraceColor = FLinearColor::Red, FLinearColor TraceHitColor = FLinearColor::Green, float DrawTime = 5.0f);

private:

	static FCollisionQueryParams CustomConfigureCollisionParams(FName TraceTag, bool bTraceComplex, const TArray<AActor*>& ActorsToIgnore, bool bIgnoreSelf, const UObject* WorldContextObject);

	static FCollisionObjectQueryParams CustomConfigureCollisionObjectParams(const TArray<TEnumAsByte<EObjectTypeQuery> > & ObjectTypes);
	
};
