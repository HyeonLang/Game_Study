#pragma once
class VertexShader
{
private:
	ID3D11VertexShader* VS;
	ID3D11InputLayout* inputLayout;             // CPU���� ó���� �� ������ ���� ������ GPU�� �ѱ� �� �ʿ��� ��ü

public:
	VertexShader(LPCWSTR file_loc, DWORD flags);
	~VertexShader();

	void Release();
	ID3D11InputLayout* GetInputLayout() { return inputLayout; }
	ID3D11VertexShader* GetVertexShader() { return VS; }
};

