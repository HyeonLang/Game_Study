#include "stdafx.h"
#include "Monsters.h"

Monsters::Monsters()
{
}

Monsters::~Monsters()
{
}

void Monsters::Init()
{
	spawn_delay = 0;
}

void Monsters::Update()
{
    // 雌切 持失
    if (spawn_delay >= 1500)
    {
        Box box;

        box.box.left = rand() % (WINSIZE_X - 15);
        box.box.right = box.box.left + 30;
        box.box.top = -30;
        box.box.bottom = 0;

        box.speed = 1;

        boxes.push_back(box);

        spawn_delay = rand() % 40;
    }
    else
        spawn_delay += level;

    // 雌切 馬悪
    for (auto iter = boxes.begin(); iter != boxes.end();  iter++)
    {
        iter->box.top += iter->speed;
        iter->box.bottom += iter->speed;
    }
}

void Monsters::Render()
{
    for (int i = 0; i < boxes.size(); i++)
        RECT_DRAW(boxes[i].box);
}
