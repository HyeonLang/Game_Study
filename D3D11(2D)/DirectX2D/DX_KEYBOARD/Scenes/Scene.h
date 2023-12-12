#pragma once
class Scene
{
protected:

public:
	virtual ~Scene() {};

	virtual void Update(DWORD* deltatime) = 0;
	virtual void Render() = 0;
};
// Scene : 사전적인 의미로 따지면 "장면"이란 뜻
// 게임 프로그래밍에서는 "최소 하나의 게임 진행이 이뤄지는 공간"이라는 의미로 사용됨
// 설정이나 게임을 막 켰을 때의 메인 화면 등도 하나의 Scene으로 취급
// -> 게임 프로그래밍은 기본적으로 여러 Scene을 만들어서 
// 각각의 Scene이 게임의 특정 단계를 맡도록 설계하고,
// 필요에 따라 그 Scene을 교체해서 사용하여 게임을 진행시키는 식으로 만드는 형식

// 이 Scene이라는 클래스는 그런 Scene을 만들 때 사용할 인터페이스를 만든 것
