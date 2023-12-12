#pragma once

class Device
{
private:
	ID3D11Device* device;                       // cpu ����, ���ҽ� �ε� �� ��� �� �ٸ� ��ɵ��� ���������� �ϴ� �⺻ ��ġ
	ID3D11DeviceContext* deviceContext;         // gpu ���� ���

	IDXGISwapChain* swapChain;                  // ������۸��� ���Ǵ� ��ü
	ID3D11RenderTargetView* renderTargetView;   // �ĸ� ���ۿ��� ����� �޸�

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

// �ؾ��� �� ����
/*
	1. �� ������Ʈ ���� �� �����ڵ�, framework.h ��� ���� ����
	2. ������Ʈ�� �������� ���� ������� ����
		1) c/c++�� �⺻���� �߰� ���͸� ������ ./
		2) �̸� ������ �� ����� ����� ����
	3. framework.cpp �����(������ #include "framework.h" ����), framework.cpp �Ӽ����� �̸� �����ϵ� ����� ������ ����
	4. Framework, Program, Scenes 3�� ���� ����, Framework ���� �ȿ� System ���� ����
	5. System ���� Device.cpp, Decvice.h ����
	6. Device.h �ȿ� Device Ŭ������ �����, ���� ���Ͽ��� �������� ������ �����ߴ� ���� 4���� ��������

		D3D11Device* device;                       // cpu ����, ���ҽ� �ε� �� ��� �� �ٸ� ��ɵ��� ���������� �ϴ� �⺻ ��ġ
		ID3D11DeviceContext* deviceContext;         // gpu ���� ���

		IDXGISwapChain* swapChain;                  // ������۸��� ���Ǵ� ��ü
		ID3D11RenderTargetView* renderTargetView;   // �ĸ� ���ۿ��� ����� �޸�
		
	7. Device Ŭ������ �̱��� �������� ����
*/