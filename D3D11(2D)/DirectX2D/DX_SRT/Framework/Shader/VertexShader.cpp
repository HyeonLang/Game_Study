#include "pch.h"
// 미리 컴파일된 헤더에 해당 헤더를 미리 등록해뒀다면
// 이후 코드 파일을 자동 생성했을 때 알아서 미리 컴파일된 헤더가 포함됨

VertexShader::VertexShader(LPCWSTR file_loc, DWORD flags)
{
    ID3DBlob* vertexBlob;

    D3DCompileFromFile(file_loc, nullptr, nullptr, "VS",
        "vs_5_0", flags, 0, &vertexBlob, nullptr);
    // 기존에 직접 주소를 입력했던 것과는 달리,
    // 이제는 매개변수를 통해 셰이더 파일의 위치를 직접 입력받는다

    Device::Get()->GetDevice()->CreateVertexShader(vertexBlob->GetBufferPointer(),
        vertexBlob->GetBufferSize(), nullptr, &VS);
    // 기존에는 메인의 전역 변수로 선언됐던 것을 사용했던 코드를
    // 이번 프레임워크에 걸맞는 형태로 변환
    // 상세히는 device가 이젠 singleton 객체를 통해서 접근해야 하니 그에 맞게 고쳐주고,
    // VertexShader 객체가 이제는 본 클래스의 멤버 변수인 VS를 이용하게 됐으므로 그에 맞게 변경

    D3D11_INPUT_ELEMENT_DESC layouts[] =
    {
        {"POSITION", // 셰이더에 데이터가 입력될 때, 지금 다루는 부분의 데이터는
        // 이 이름을 가진 시멘틱에 들어갈 것이다
        0, // 시멘틱 인덱스 - 당장은 쓸 일이 없으니 추후 사용할 일이 생겼을 때 설명
        // 그 전까지는 0으로 고정
        DXGI_FORMAT_R32G32B32_FLOAT, 
        // "이 시멘틱엔 이 형식의 자료가 들어갈 예정"이라고 알려주는 부분,
        // 이게 실제 데이터와 일치하지 않으면 정상적으로 작동하지 않음
        // 이것 때문에 에러가 나는 경우가 굉장히 많으므로 신경써서 일치시켜줘야 함

        // 위 포맷의 뜻은
        // R, G, B 총 3가지의 자료를 사용한다는 의미
        // + 이 3가지 자료는 각각 32비트 / 32비트 / 32비트만큼의 데이터를 사용함
        // 그리고 이 데이터들은 실수(float)다

        // 지원하는 데이터의 형식엔 한도가 있으며,
        // 그 내용은 정의를 찾아가서 열거형의 내용을 보며 확인해볼 것
        0, // 어느 "슬롯"에 넣을지를 결정하는 부분
        // 이 슬롯에 대한 개념은 추후 직접 다루게 됐을 때 설명, 지금 당장은 사용하지 않는 개념
        0, // 전체 데이터(바이트) 중 어디에서부터 이 데이터가 시작되는지 그 인덱스를 명사
        // 인덱스를 명시하는 것이니 0부터 시작
        D3D11_INPUT_PER_VERTEX_DATA, 0} // 2D를 공부하는 동안엔 다룰 일 없는 변수들이므로 패스

        // 정점 셰이더의 시멘틱 "POSITION"에는 이런 구조의 데이터가 들어간다고
        // 시스템에 알리는 부분

        ,{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12,
        D3D11_INPUT_PER_VERTEX_DATA, 0}
        // 시멘틱 "COLOR"에 들어갈 데이터의 포맷
        // 12의 경우, 위쪽에서 선언되었던 첫번쨰 데이터의 포맷이
        // R32G32B32 = 총 12바이트이므로
        // 이 12바이트가 끝나고 난 뒤 13번째 바이트(=인덱스 12)부터 이 포맷의 데이터를 가리킨다
        // 라고 알려주는 내용

        // 이렇게 정의된 데이터들이
        // 정점 셰이더에 입력된다는 것을 시스템에 알리는 것이 layouts의 역할
    };

    UINT layoutSize = ARRAYSIZE(layouts);
    // 그렇게 규격을 지정한 layouts의 총 용량을 계산
    // 바로 밑의 CreateInputLayout 함수에서 layouts의 총 용량을 직접 계산하지 못하기 때문에,
    // 우리가 미리 계산해서 알려줄 필요가 있기 때문

    Device::Get()->GetDevice()->CreateInputLayout(layouts, layoutSize, vertexBlob->GetBufferPointer(),
        vertexBlob->GetBufferSize(), &input_layout);
    vertexBlob->Release();
}

VertexShader::~VertexShader()
{
    Release();
}

void VertexShader::Set()
{
    DVC->IASetInputLayout(input_layout);
    DVC->VSSetShader(VS, nullptr, 0);
}

void VertexShader::Release()
{
    VS->Release();
    input_layout->Release();
}
