#pragma once

class Device
{
private:
	ID3D11Device* device;                       // cpu 연산, 리소스 로딩 등 출력 외 다른 기능들을 종합적으로 하는 기본 장치
	ID3D11DeviceContext* deviceContext;         // gpu 연산 담당

	IDXGISwapChain* swapChain;                  // 더블버퍼링에 사용되는 객체
	ID3D11RenderTargetView* renderTargetView;   // 후면 버퍼에서 사용할 메모리

	static Device* instance;

	Device();
	~Device();

public:
	static Device* Get()
	{
		if (instance == nullptr)
			instance = new Device();

		return instance;
	}

	static void Delete() { delete instance; }

	void CreateDeviceAndSwapChain();
	void CreateBackBuffer();
	void SetViewPoint();

	void Clear();
	void Present();

	ID3D11Device* GetDevice() { return device; }
	ID3D11DeviceContext* GetDeviceContext() { return deviceContext; }

};

// 해야할 일 정리
/*
	1. 새 프로젝트 생성 후 메인코드, framework.h 모든 내용 복사
	2. 프로젝트의 설정에서 다음 내용들을 수정
		1) c/c++의 기본에서 추가 디렉터리 설정에 ./
		2) 미리 컴파일 된 헤더를 사용을 변경
	3. framework.cpp 만들고(내용은 #include "framework.h" 한줄), framework.cpp 속성에서 미리 컴파일된 헤더를 만들기로 설정
	4. Framework, Program, Scenes 3개 폴더 생성, Framework 폴더 안에 System 폴더 생성
	5. System 폴더 Device.cpp, Decvice.h 생성
	6. Device.h 안에 Device 클래스를 만들고, 메인 파일에서 전역변수 구간에 선언했던 다음 4개를 가져오기

		D3D11Device* device;                       // cpu 연산, 리소스 로딩 등 출력 외 다른 기능들을 종합적으로 하는 기본 장치
		ID3D11DeviceContext* deviceContext;         // gpu 연산 담당

		IDXGISwapChain* swapChain;                  // 더블버퍼링에 사용되는 객체
		ID3D11RenderTargetView* renderTargetView;   // 후면 버퍼에서 사용할 메모리
		
	7. Device 클래스를 싱글톤 패턴으로 구성
*/