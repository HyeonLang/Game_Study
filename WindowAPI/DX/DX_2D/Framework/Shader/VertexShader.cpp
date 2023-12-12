#include "pch.h"
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
    // 정확히는 정점의 정보를 저장할 공간을 만드는 동시에,
    // 셰이더에 이 값을 넘길 때 정보의 범위와 종류를 명시하는 가이드라인을 같이 명시하는 부분
    // 셰이더는 C++처럼 자료형을 알아서 판단하지 못하기 때문에 직접 자료형 그 자체를 알려줄 필요가 있음

    D3D11_INPUT_ELEMENT_DESC layouts[] =
    {
        {"POSITION",                    // 시멘틱 입력 공각
        0, 
        DXGI_FORMAT_R32G32B32_FLOAT,    // 시멘틱에 들어갈 자료형 명시 : R32G32B32 = 4byte 씩 3개의 FLOAT 할당
        // DXGI_FORMAT : 사실 모든 형식의 데이터가 가능한 건 아니고 사전에 이미 지정된 형식들만 사용 가능
        // 그래서 그 사용 가능한 것들을 하나의 열거형에 모아뒀다는 의미(그 열거형의 이름이 DXGI_FORMAT)
        0, 
        0,                              // 전체 데이터(바이트) 중 데이터의 시작점 명시
        D3D11_INPUT_PER_VERTEX_DATA, 0},
        // 시멘틱 "POSITION"에 해당하는 데이터는 위와 같은 구조임을 시스템에 알리는 구성

        {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12,
        D3D11_INPUT_PER_VERTEX_DATA, 0}
        // 시멘틱 "COLOR"에 해당하는 데이터는 위와 같은 구조임을 시스템에 알리는 구성

        // 이 부분은 셰이더에 데이터를 넘길 때 "이렇게 구성되어 있는 데이터를 넘길 예정입니다"라고 알린다는 의미
        // Shader에서 지정된 시멘틱에 해당하는 데이터가 어디부터 어디까지인지를 위 코드를 통해 명시

        // 앞으로 입력될 정점들은 위 정보를 토대로 정점에 입력됨.
        // 위 구조와 셰이더에서 입력을 요구하는 정보가 정확히 들어맞지 않을 경우 밑의 CreateInputLayout이 아예 작동하지 않음
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
