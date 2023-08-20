// Copyright Shattered Realms Online All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "HttpModule.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/ListView.h"
#include "Components/TextBlock.h"
#include "Components/Throbber.h"
#include "Gameplay/Character/SROCharacterDetails.h"
#include "SSroCharacter/CharacterService.h"
#include "SSroGamebackend/ConnectionClient.h"
#include "SROCharacterSelectorWidget.generated.h"

/**
 * 
 */
UCLASS()
class SRO_API USROCharacterSelectorWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UCharacterServiceClient* CharacterServiceClient;

	UConnectionServiceClient* ConnectionServiceClient;
	
public:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Login", meta = (BindWidget))
	UButton* PlayButton;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Login", meta = (BindWidget))
	UButton* LogoutButton;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Login", meta = (BindWidget))
	UButton* CreateCharacterButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Login", meta = (BindWidget))
	UListView* CharacterList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Login", meta = (BindWidget))
	UTextBlock* ErrorText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Login", meta = (BindWidget))
	UThrobber* PlayThrobber;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Login")
	USROCharacterDetails* SelectedCharacterDetaeils;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Login")
	AActor* SelectedCharacterActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Login")
	FVector SelectedCharacterSpawnLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Login")
	FRotator SelectedCharacterSpawnRotator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Login")
	UClass* BaseActorClass;

	UFUNCTION(BlueprintCallable)
	void Logout();
	
	UFUNCTION(BlueprintCallable)
	void Reset();
	
	UFUNCTION(BlueprintCallable)
	void CreateCharacter();

	UFUNCTION(BlueprintCallable)
	void Play();
	
private:
	UFUNCTION()
	void OnConnectResponseReceived(FGrpcContextHandle Handle, const FGrpcResult& GrpcResult, const FGrpcSroGamebackendConnectGameServerResponse& Response);

	UFUNCTION()
	void OnGetCharactersReceived(FGrpcContextHandle Handle, const FGrpcResult& GrpcResult, const FGrpcSroCharacterCharactersDetails& Response);
};


