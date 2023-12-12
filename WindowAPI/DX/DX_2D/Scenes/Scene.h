#pragma once

#ifndef SCENE
#define SCENE

class Scene
{
protected:
	VertexShader* VS;
	PixelShader* PS;

public:
	virtual ~Scene() {}

	virtual void Update() = 0;
	virtual void Render() = 0;

};
#endif

/*
	Scene : 게임에서 하나의 화면을 담당할 객체
	게임의 장면 각각을 Scene이라고 한다.

	게임은 기본적으로 여러 종류의 Scene을 준비, 상황에 맞게 화면에 출력한다.
	그 Scene에 맞는 입력과 시스템을 이용하여 전체적인 진행을 해나가는 식.

*/