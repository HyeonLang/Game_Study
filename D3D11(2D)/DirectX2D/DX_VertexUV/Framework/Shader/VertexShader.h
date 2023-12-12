#pragma once

class VertexShader
	// �� �״�� ���� ���̴��� ����� Ŭ����
{
private:
	ID3D11VertexShader* VS;
	ID3D11InputLayout* input_layout;

public:
	VertexShader(LPCWSTR file_loc, 
		DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG,
		UINT type = 0);
	// �Ű� ������ ���ڿ��� ���̴� ������ �ʿ��� �÷��׸� �޴´�
	~VertexShader();

	void Set();

	void Release();
	ID3D11InputLayout* GetInputLayout() { return input_layout; }
	ID3D11VertexShader* GetVertexShader() { return VS; }
};