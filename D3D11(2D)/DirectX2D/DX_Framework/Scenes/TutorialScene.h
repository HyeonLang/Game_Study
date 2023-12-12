#pragma once
class TutorialScene : public Scene
{
private:
	Triangle* list_triangle;
	Triangle* list_rect;
	Hexagon* list_hexagon[10] = {};
	Hexagon* line_hexagon;

public:
	TutorialScene();
	~TutorialScene();


	// Scene��(��) ���� ��ӵ�
	virtual void Update() override;

	virtual void Render() override;

};