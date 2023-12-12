#include "stdafx.h"
#include "MainGame.h"
#include "Player.h"
#include "Monsters.h"

MainGame::MainGame()
{
    player = new Player;
    monsters = new Monsters;
}

MainGame::~MainGame()
{
}

void MainGame::Init()
{
	level = 0;
	score = 0;

    if (player != nullptr) player->Init();
    if (monsters != nullptr) monsters->Init();
}

void MainGame::Update()
{
    // 화면 갱신 함수
    // 특정 영역을 지정해 화면을 갱신한다.
    InvalidateRect(g_hWnd, NULL, false);

    level = 1 + score / 10;
    if (monsters != nullptr) monsters->SetLevel(level);

    if(player != nullptr) player->Update();
    if(monsters != nullptr) monsters->Update();
    
    for (auto iter = monsters->GetBoxes().begin();
        iter != monsters->GetBoxes().end()
        ;)
	{
        RECT rt;
        RECT iter_box = iter->box;

        if (iter_box.top > WINSIZE_Y)
        {
            iter = monsters->GetBoxes().erase(iter);
            score++;
        }
        else if (IntersectRect(&rt, &iter_box, &player->GetBox()))
        {
            iter = monsters->GetBoxes().erase(iter);
            score -= 5;
        }
        else if (PtInRect(&iter_box, g_mouse_pos))
        {
            iter = monsters->GetBoxes().erase(iter);
            score++;
        }
        else
            iter++;
    }

}

void MainGame::Render()
{
    PAINTSTRUCT ps;

    /*
        dc
        - Device Context
        - 출력을 위한 모든 데이터를 가지는 구조체
    */
    HDC hdc = BeginPaint(g_hWnd, &ps);

    // TODO: Add any drawing code that uses hdc here...

    // 백버퍼 초기화
    PatBlt(g_hDC, 0, 0, WINSIZE_X, WINSIZE_Y, WHITENESS);

    if (player != nullptr) player->Render();
    if (monsters != nullptr) monsters->Render();

    wstring score_str(to_wstring(score).c_str());
    TextOut(g_hDC, 10, 30, score_str.c_str(), score_str.length());

    wstring level_str(to_wstring(level).c_str());
    TextOut(g_hDC, 10, 10, level_str.c_str(), level_str.length());

    BitBlt(hdc, 0, 0, WINSIZE_X, WINSIZE_Y, g_hDC, 0, 0, SRCCOPY);

    EndPaint(g_hWnd, &ps);
}
