#include "TestFlatbuffer.h"
#include "Protocol_generated.h"

// Sets default values
ATestFlatbuffer::ATestFlatbuffer()
{
    // Tick을 안 쓴다면 꺼두는 게 성능에 좋습니다.
    PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATestFlatbuffer::BeginPlay()
{
    Super::BeginPlay(); // 부모 클래스 호출 필수

    // ==========================================
    // 1. 직렬화 (Serialization) - 보내는 쪽
    // ==========================================
    flatbuffers::FlatBufferBuilder builder(1024);
    
    // 1-1. 내부 데이터(Struct/Table) 생성
    Protocol::Vec3 pos(10.0f, 20.0f, 30.0f);
    auto c_move = Protocol::CreateC_Move(builder, &pos);

    // 1-2. 껍데기(Packet) 생성 - Union 사용
    // 두 번째 인자: "이 안에 들어있는 건 C_Move야" (타입)
    // 세 번째 인자: 실제 C_Move 데이터 (내용물)
    auto packet = Protocol::CreatePacket(builder, Protocol::PacketData_C_Move, c_move.Union());

    builder.Finish(packet);

    // 1-3. 언리얼 버퍼로 복사 (네트워크 전송 시뮬레이션)
    TArray<uint8> PacketData;
    PacketData.Append(builder.GetBufferPointer(), builder.GetSize());


    // ==========================================
    // 2. 역직렬화 (Deserialization) - 받는 쪽
    // ==========================================
    
    // 2-1. 루트 패킷(껍데기) 열기
    auto recvPacket = Protocol::GetPacket(PacketData.GetData());

    // 2-2. 타입 확인 및 캐스팅
    switch (recvPacket->data_type())
    {
    case Protocol::PacketData_C_Move:
        {
            // C_Move로 형변환 (Zero-Copy)
            auto move_data = recvPacket->data_as_C_Move();
            
            UE_LOG(LogTemp, Warning, TEXT("[Flatbuffer Recv] Type: C_Move, Pos: %f, %f, %f"), 
                move_data->pos()->x(), 
                move_data->pos()->y(), 
                move_data->pos()->z());
            break;
        }
        
    case Protocol::PacketData_S_Move:
        {
            auto move_data = recvPacket->data_as_S_Move();
            UE_LOG(LogTemp, Warning, TEXT("[Flatbuffer Recv] Type: S_Move, PlayerID: %d"), move_data->player_id());
            break;
        }
        
    default:
        UE_LOG(LogTemp, Error, TEXT("[Flatbuffer Recv] Unknown Packet Type!"));
        break;
    }
}

void ATestFlatbuffer::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}