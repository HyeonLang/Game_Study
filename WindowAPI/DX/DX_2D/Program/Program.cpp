#include "pch.h"	
// 미리 컴파일된 헤더 사용시 그 헤더에 포함된 내용들 중 하나라도 필요한 파일에서 경로 상관없이 해당 파일을 포함하겠다 include 하면
// 편집기에선 에러가 발생 할 수 있지만 실제로는 에러가 발생하지 않는다.

Program::Program()
{
	Create();	// Device를 초기화
	scene = new TutorialScene();	// 이 프로그램이 사용할 Scene을 미리 정의

	// 여기에 새로만든 Scene을 할당 혹은 Scene을 여러개 만든 뒤 이를 교체하는 시스템을 구현하여 사용
}

Program::~Program()
{
	delete scene;
}

void Program::Update()	// API에서 루프문 돌릴 때 메세지가 있으면 처리했던 것들을 여기서 처리
{
	scene->Update();	// 각 Scene에 업데이트 
}

void Program::Render()	// 프로그램 화면 출력 담당
{
	//Device::Get()->Clear();	// 먼저 디바이스를 불러서 화면 초기화 
	scene->Render();		// Scene에서 화면출력과 관련된 내용을 실행시키도록 명령
	Device::Get()->Present();	// 디바이스에서 이중 버퍼링을 실행 요청
}

void Program::Create()	// 프로그램 최초 생성 시 초기화 할 것들을 정리 
{						// 정확히는 초기화하면서 시스템상으로 중요한 객체 중 새 객체가 생성되는 것들을 모음.

	Device::Get();	// 최초로 싱글톤인 Device를 호출하여 Device 객체 생성
					// 이후 Device 싱글톤에 접근시 Device::Get을 이용하여 접근
}

void Program::Delete()
{
	Device::Delete();	// 디바이스 할당 해제
}

/*
	DX의 프로그림 구동 방식
	1. 프로그램의 실행에 필요한 각종 장치 초기화
	2. 프로그램을 초기화 하면서 프로그램에 사용될 Scene을 정의 및 초기화
	3. 프로그램이 루프를 동면서 디바이스와 Scene의 루프를 제어

	즉 모든게 프로그램을 기준으로 돌아간다.
	프로그램이 각종 요소들을 제어하는 허브로서 기능.
*/
