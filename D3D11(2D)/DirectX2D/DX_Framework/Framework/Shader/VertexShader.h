#pragma once

class VertexShader
	// �� �״�� ���� ���̴��� ����� Ŭ����
{
private:
	ID3D11VertexShader* VS;
	ID3D11InputLayout* input_layout;

public:
	VertexShader(LPCWSTR file_loc, DWORD flags);
	// �Ű� ������ ���ڿ��� ���̴� ������ �ʿ��� �÷��׸� �޴´�
	~VertexShader();

	void Release();
	ID3D11InputLayout* GetInputLayout() { return input_layout; }
	ID3D11VertexShader* GetVertexShader() { return VS; }
};