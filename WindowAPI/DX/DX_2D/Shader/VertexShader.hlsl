// 시멘틱(sementic) : 변수 정보를 어떻게 사용할지에 대해 이름을 붙이는 것.

//이 시멘틱은이미 시스템에서 예약되어있는 이름
// 정확한 시멘틱으로 선언을 해주고 사용해줘야만 제대로 동작

struct VertexInput // 정점 셰이더에서 사용될 자료형에 대한 정의
{
    float4 pos : POSITION; // 반환형에 대한 시멘틱
    float4 color : COLOR;
};

struct PixelInput // 픽셀 셰이더에서 사용될 자료형에 대한 정의
{
    float4 position : SV_Position; // 지금은 사용되지 않지만, 후일 픽셀 셰이더에서 좌표에 따라 다른 처리를 해야 하는 경우엔 이 데이터를 사용
    float4 color : COLOR;
};

PixelInput VS(VertexInput input)
//System Value(SV) : 시스템으로 넘기는 값. VS에선 Resterizer State(RS)를 의미.
{
    PixelInput output;
    output.position = input.pos;
    output.color = input.color;
    return output;
}
// Vertex Shader : 입력받은 정점 데이터들을 우리가 원하는 식으로 그래픽을 처리할 수 있도록 적절히 변환해 주는 단계
//  - 3차원 공간 좌표에 지정된 각 정점을 VS를 통해 화면에 맞는 좌표로 변환

float4 PS(PixelInput input) : SV_Target // SV -> OM, Target을 백 버퍼에 넘기는 과정
{
    //지금은 input의 position을 사용하지 않았지만
    // 나중엔 이 position의 값을 이용해서 전체 구간 중 특정 구간에만 보정을 주는 것이 가능하다
    // 이걸 이용해서 각종 영상 필터링이 가능

    return input.color;
}
// Pixel Shader : Vertex Shader와 Tesselation, Rasterizer를 거쳐 출력할 데이터가 완성이 되었으면
// 그 데이터를 모니터의 각 픽셀에 맞는 형태로 변환해주는 형태
// 그 과정에서 색처리 보정 가능

// 위 경우 어떤 정점이 들어와도 float4로 선언한 색상값을 출력하도록 선언한 것. 각 픽셀마다 다르게 출력할 수 있음

// VS, PS를 분리거나 둘 이상의 VS, PS를 운용할 예정

// hlsl 파일이 프로젝트에 포함된 경우,
// 자세한 설명은 생략하지만 프로젝트 자체가 이 파일의 main 함수를 찾다가 오류가 발생하는 일이 많음
// 어차피 우리는 메인 코드에서 이 파일을 파일채로 가져와 쓰는 코드를 사용하기 때문에
// 그냥 이 파일을 프로젝트에서 제외시키는 것으로 해당 오류를 막을 수 있음

// 그 외에도 추가로 설정해둬야 할 것이 있는데
// 이 셰이더 파일을 프로젝트에서 제외하기 전에
// 솔루션 탐색기에서 우클릭->속성으로 들어가서 이거저거 설정해줘야 하긴 하나

// 지금은 어차피 제외되는 순간 해당 속성들이 날아가기에 무시해도 무방
// 이건 다음에 다른 셰이더를 다룰 때 설명