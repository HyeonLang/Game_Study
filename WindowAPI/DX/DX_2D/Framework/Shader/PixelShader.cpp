#include "pch.h"
#include "PixelShader.h"

PixelShader::PixelShader(LPCWSTR file_loc, DWORD flags)
{
	// 이 과정을 화면의 픽셀을 관리하는 셰이더에 대해서도 마찬가지로 처리
    // VertexShader의 생성자를 만들던 때와 동일
    ID3DBlob* pixelBlob;
    D3DCompileFromFile(file_loc, nullptr, nullptr, "PS",
        "ps_5_0", flags, 0, &pixelBlob, nullptr);

    Device::Get()->GetDevice()->CreatePixelShader(pixelBlob->GetBufferPointer(),
        pixelBlob->GetBufferSize(), nullptr, &PS);
    pixelBlob->Release();

    // DirectX에서 화면을 출력할 때는 이 셰이더라는것을 정점 셰이더, 픽셀셰이더 최소 2개를 필요로 한다.
}

PixelShader::~PixelShader()
{
	Release();
}

void PixelShader::Release()
{
	PS->Release();
}
