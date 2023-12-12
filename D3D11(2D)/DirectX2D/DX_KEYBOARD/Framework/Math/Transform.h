#pragma once
class Transform
	// DirectX3d 등을 넘어서 2D 혹은 3D 공간에서 하나의 오브젝트를 관리하는 기본 단위
	// 표현을 위해 쓰이는 단위인 폴리곤과는 다른 개념

	// 프로그램에서 객체(인스턴스)라고 부르는 개념을
	// 3D 공간에서 오브젝트 하나를 만들 때 이 Transform 기본 단위로 한다.
	// 모든 오브젝트는 하나의 Transform를 가진다.

	// 3D 공간(우리의 경우 2D 공간)에서 하나의 오브젝트가 어느 위치에 어느 방향으로 어느 크기를 가지고 있는지를
	// 이 Transform을 이용해서 관리
{
protected:
	Float2 pos; // 오브젝트의 위치
	Float2 scale; // 오브젝트의 크기(원본 크기를 1.0으로 했을 때 비율을 유지하면서 얼마나 크게 만들 것인지)
	Float3 rot;	// 각 x y z 축에 회전한 정도, 밑 함수들에 호환시키기 위해 Float3 형태로 이용해야할 필요 있음.
	float angle; // 오브젝트가 바라보고 있는 각도
	// 3D였다면 angle도 Float3로 만들어야 했겠지만 여긴 2D니 상관없음

	Matrix world;	// 오브젝트가 속한 월드의 행렬
					// 오브젝트를 만들 때 어디를 기준점으로 할 것인지를 월드 행렬의 형태로 지정해 저장하는 역할

	Vector2 pivot;	// 오브젝트와 연결된 다른 오브젝트가 회전해야 할 경우 사용
					// 여러개를 생성해야 할 경우 여럿 생성해야 한다.
					// 자기자신은 그대로 있으면서 pivot을 사용하는 오브젝트가 구심점으로 사용한다.

	Matrix* parent;	// 오브젝트가 위치 등을 의존하고 있는 부모 오브젝트
	Matrix S, R, T, P, IP;	// SRT 변환 행렬 계산시 데이터 낭비를 막기위해 만들어두고 사용

public:
	Transform(Float2 p, Float2 s, float a, Matrix* parent = NULL );
	~Transform();

	float GetAngle() { return angle; }
	void SetAngle(float a) 
	{ 
		angle = a; 
		rot.z = a;
	}

	void SetPos(Float2 p)
	{
		pos = p;
	}
	void AddAngle(float a)
	{
		angle += a;
		rot.z = angle;
	}

	void WorldTransform(Matrix* parent = NULL);
	// 이 오브젝트의 월드(기준점)를 설정. 기본값은 NULL
	void WorldUpdate();

	Matrix* GetWorld() 
	{
		return &world;
	}

};