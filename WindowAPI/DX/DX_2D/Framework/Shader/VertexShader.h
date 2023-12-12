#pragma once
class VertexShader
{
private:
	ID3D11VertexShader* VS;
	ID3D11InputLayout* inputLayout;             // CPU에서 처리된 각 정점에 대한 정보를 GPU에 넘길 때 필요한 객체

public:
	VertexShader(LPCWSTR file_loc, DWORD flags);
	~VertexShader();

	void Release();
	ID3D11InputLayout* GetInputLayout() { return inputLayout; }
	ID3D11VertexShader* GetVertexShader() { return VS; }
};

