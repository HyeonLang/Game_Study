#include "framework.h"
#include "VertexShader.h"

VertexShader::VertexShader(LPCWSTR file_loc, DWORD flags)
{
    // 이하 내용은 InitDevice() 내용을 복사 후 수정
    
    //hlsl 파일을 로드하여 셰이더를 DirectX 개체에 설치하는 과정
    ID3DBlob* vertexBlob;
    //1. 파일을 불러올때 직접 입력이 아닌 매개변수로 입력
    D3DCompileFromFile(file_loc, nullptr, nullptr, "VS",
        "vs_5_0", flags, 0, &vertexBlob, nullptr);

    // 설치과정 2
    // 2. Device 싱글톤 객체를 불러오는 방식으로 변경
    Device::Get()->GetDevice()->CreateVertexShader(vertexBlob->GetBufferPointer(),
        vertexBlob->GetBufferSize(), nullptr, &VS);

    // 그렇게 설치한 셰이더를 통해 그림을 그릴 좌표가 지정되면 그 값을 가져와 저장할 공간을 만든다.
    D3D11_INPUT_ELEMENT_DESC layouts[] =
    {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
        D3D11_INPUT_PER_VERTEX_DATA, 0}
    };

    UINT layoutSize = ARRAYSIZE(layouts);   // 저장된 총량을 여기서 계산

    // 여기 까지를 통해 실제로 기리기 위해 필요한 데이터를 저장해둘 공간을 마련, 이를 DirectX 객체에 등록
    // 등록과정에서 잠시 사용했던 blob은 할당 해제
    Device::Get()->GetDevice()->CreateInputLayout(layouts, layoutSize, vertexBlob->GetBufferPointer(),
        vertexBlob->GetBufferSize(), &inputLayout);
    vertexBlob->Release();
}

VertexShader::~VertexShader()
{
    Release();
}

void VertexShader::Release()
{
    VS->Release();
    inputLayout->Release();
}
