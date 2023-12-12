#pragma once

class TutorialScene : public Scene
{
private:
	Triangles* list_rect;


public:
	TutorialScene();
	~TutorialScene();

	virtual void Update() override;
	virtual void Render() override;

};