// Fill out your copyright notice in the Description page of Project Settings.


#include "TestProtobuf.h"
#include "DGProtobufWrapper.h"

// Sets default values
ATestProtobuf::ATestProtobuf()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	
}

// Called when the game starts or when spawned
void ATestProtobuf::BeginPlay()
{
	Super::BeginPlay();
	
	Protocol::C_LoginReq loginReq;
	loginReq.set_authtoken("testToken");
	loginReq.set_transfertoken("testToken");
	
	int Size = loginReq.ByteSizeLong();
	
	TArray<uint8> PacketData;
	PacketData.SetNumUninitialized(Size);
	
	if (loginReq.SerializeToArray(PacketData.GetData(), Size))
	{
		// --------------------------------------------------------
		// 역직렬화 테스트
		Protocol::C_LoginReq NewMsg;
        
		// [수정 포인트 3] ParseFromArray 사용
		if (NewMsg.ParseFromArray(PacketData.GetData(), PacketData.Num()))
		{
			UE_LOG(LogTemp, Warning, TEXT("[Protobuf] Auth: %s"), UTF8_TO_TCHAR(NewMsg.authtoken().c_str()));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[Protobuf] Serialization Failed!"));
	}
}

// Called every frame
void ATestProtobuf::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

