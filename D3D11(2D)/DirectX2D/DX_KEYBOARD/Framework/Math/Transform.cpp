#include "pch.h"

Transform::Transform(Float2 p, Float2 s, float a, Matrix* parent)
	: pos(p), scale(s), angle(a), parent(parent)
{
	//Matrix S = XMMatrixScaling(scale.x, scale.y, 1.0f);
	//// 오브젝트의 스케일(크기)을 행렬에 저장
	//// 원래는 3차원 공간에서 사용될 것이라 z값까지 총 3종을 사용하지만,
	//// 우리는 2D공간이라 z축을 고려할 필요가 없으니 z값은 1.0f로 고정

	//// 위 함수는 다음과 같은 행렬을 반환
	///* scale.x = a, scale.y = b, scale.z = c
	//( a 0 0 0 )
	//( 0 b 0 0 )
	//( 0 0 c 0 )
	//( 0 0 0 1 )
	//*/
	//Matrix R = XMMatrixRotationZ(angle);
	//// 오브젝트의 회전도를 행렬에 저장
	//// 마찬가지로 원래는 X축, Y축, Z축 각각에 대한 회전을 계산해야 하지만
	//// 여긴 2D이므로 우리가 화면을 보는 방향, 즉 Z축의 회전만 계산하면 됨

	///* angle = a
	//( cos(a) -sin(a) 0 0 )
	//( sin(a) cos(a)  0 0 )
	//(   0       0    1 0 )
	//(   0       0    0 1 )
	//*/
	//Matrix T = XMMatrixTranslation(pos.x, pos.y, 0.0f);
	//// 오브젝트의 투영을 행렬에 저장
	//// 그냥 좌표에 따른 이동을 이 행렬을 통해 저장한다고 보면 무방
	///* pos.x = a, pos.y = b, pos.z = c
	//( 1 0 0 0 )
	//( 0 1 0 0 )
	//( 0 0 1 0 )
	//( a b c 1 )
	//*/

	//// 이 과정에서 어떤 행렬이 구해지는지를 알아둘 필요가 있긴 함
	//// 더 자세한 수학적 설명은 https://pjnull.tistory.com/6 등의 타 사이트의 설명을 참조

	//world = S * R * T;

	world = XMMatrixIdentity();	// world를 정의하는 부분은 worldUpdate쪽에서 진행

}

Transform::~Transform()
{
}

void Transform::WorldTransform(Matrix* parent)
// 월드의 기준점 설정 및 업데이트
// 이 오브젝트가 다른 오브젝트의 위치에 의존하는 오브젝트일 경우
// 그 의존하고 있는 오브젝트를 "부모"로서 판단하여 "부모"의 월드 변환행렬을
// 이 트랜스폼의 월드 행렬에 곱해서 적용시키는 것

// 월드의 기준점을 무엇으로 잡냐에 따라서 3차원 공간의 물체의 좌표는 서로 다르게 표현할 수 있는데
// 그 기준점에 따라서 상대 좌표가 아닌 실제 좌표를 구하는 과정이라고 봐도 무방
{
	Matrix S = XMMatrixScaling(scale.x, scale.y, 1.0f);
	Matrix R = XMMatrixRotationZ(angle);
	Matrix T = XMMatrixTranslation(pos.x, pos.y, 0.0f);

	world = S * R * T;
	// 여기까지는 생성자에서처럼 패러미터들을 통해 이 트랜스폼의 변환 행렬을 구한 것


	// 만약 부모가 존재하는 트랜스폼이라면
	if (parent != NULL)
		world *= *parent;
	// 부모의 SRT 월드 변환 행렬을 이 트랜스폼에 적용해서 실제 공간에서의 좌표값을 계산
}

void Transform::WorldUpdate()
{
	S = XMMatrixScaling(scale.x, scale.y, 1.0f);
	R = XMMatrixRotationZ(angle);
	T = XMMatrixTranslation(pos.x, pos.y, 0.0f);

	P = XMMatrixTranslation(pivot.x, pivot.y, 0.0f);	// pivot의 데이터를 통해 SRT 변환 행렬을 계산하기 위해 만든 행렬
	IP = XMMatrixInverse(NULL, P);	// 입력된 행렬의 역함수

	world = IP * S * R * T * P;
	// 피벗 사용시 역행렬과 행렬을 앞뒤에 곱해주어야 한다.
	if (parent != NULL)
		world *= *parent;
}
