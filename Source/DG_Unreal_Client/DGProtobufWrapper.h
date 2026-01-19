// ProtocolImpl.cpp

// 1. 언리얼 필수 헤더 (PCH)
#include "DG_Unreal_Client.h" 

// 2. 윈도우/언리얼 매크로 충돌 방지 처리
#if PLATFORM_WINDOWS
	#include "Windows/AllowWindowsPlatformTypes.h"
#endif

// [중요] 충돌나는 언리얼 매크로들을 잠시 해제합니다.
#pragma push_macro("check")
#undef check
#pragma push_macro("verify")
#undef verify
#pragma push_macro("TEXT")
#undef TEXT

// 3. 경고 무시 설정 (Protobuf 내부 경고 무시)
#pragma warning(push)
#pragma warning(disable: 4800) // int -> bool performance warning
#pragma warning(disable: 4668) // undefined macro
#pragma warning(disable: 4125) // decimal digit terminates octal escape sequence
#pragma warning(disable: 4647) 
#pragma warning(disable: 4100) // unreferenced formal parameter

// 4. 진짜 Protobuf 소스 코드 포함 (확장자 바꾼 파일)
// 경로는 실제 파일 위치에 맞춰주세요. 
// 예: 현재 파일과 같은 폴더에 있다면 바로 적고, 아니라면 상대 경로 입력
#include "Protocol.pb.cc_" 

// 5. 경고 및 매크로 복구
#pragma warning(pop)

#pragma pop_macro("TEXT")
#pragma pop_macro("verify")
#pragma pop_macro("check")

#if PLATFORM_WINDOWS
	#include "Windows/HideWindowsPlatformTypes.h"
#endif