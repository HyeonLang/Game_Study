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
	Scene : ���ӿ��� �ϳ��� ȭ���� ����� ��ü
	������ ��� ������ Scene�̶�� �Ѵ�.

	������ �⺻������ ���� ������ Scene�� �غ�, ��Ȳ�� �°� ȭ�鿡 ����Ѵ�.
	�� Scene�� �´� �Է°� �ý����� �̿��Ͽ� ��ü���� ������ �س����� ��.

*/