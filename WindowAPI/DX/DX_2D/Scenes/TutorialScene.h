#pragma once

class TutorialScene : public Scene
{
private:
	Triangles* list_rect;
	Triangles* strip_rect;
	Hexagons* hexagon;

public:
	TutorialScene();
	~TutorialScene();

	virtual void Update() override;
	virtual void Render() override;

};