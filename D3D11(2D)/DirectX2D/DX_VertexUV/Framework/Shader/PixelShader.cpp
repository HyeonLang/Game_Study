#include "pch.h"

PixelShader::PixelShader(LPCWSTR file_loc, DWORD flags)
{
    ID3DBlob* pixelBlob;
    D3DCompileFromFile(file_loc, nullptr, nullptr, "PS",
        "ps_5_0", flags, 0, &pixelBlob, nullptr);

    Device::Get()->GetDevice()->CreatePixelShader(pixelBlob->GetBufferPointer(),
        pixelBlob->GetBufferSize(), nullptr, &PS);
    pixelBlob->Release();
}

PixelShader::~PixelShader()
{
	Release();
}

void PixelShader::Release()
{
	PS->Release();
}

void PixelShader::Set()
{
    DVC->PSSetShader(PS, nullptr, 0);
}
