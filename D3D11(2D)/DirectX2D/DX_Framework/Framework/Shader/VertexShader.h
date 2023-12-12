#pragma once

class VertexShader
	// 말 그대로 정점 셰이더를 담당할 클래스
{
private:
	ID3D11VertexShader* VS;
	ID3D11InputLayout* input_layout;

public:
	VertexShader(LPCWSTR file_loc, DWORD flags);
	// 매개 변수로 문자열과 셰이더 설정에 필요한 플래그를 받는다
	~VertexShader();

	void Release();
	ID3D11InputLayout* GetInputLayout() { return input_layout; }
	ID3D11VertexShader* GetVertexShader() { return VS; }
};