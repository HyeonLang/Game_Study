#include "stdafx.h"
#include "MainGame.h"

MainGame::MainGame()
{
	Init();
}

MainGame::~MainGame()
{
}

void MainGame::Init()
{
	map.clear();
	map.shrink_to_fit();

	map.assign(map_size_y, std::vector<block>());

	for (auto& line : map)
		line.assign(map_size_x, block{false, true, -1});



	{
		WINSIZE_X = map_size_x * 50;
		WINSIZE_Y = map_size_y * 50;
		int resolution_x = GetSystemMetrics(SM_CXSCREEN);
		int resolution_y = GetSystemMetrics(SM_CYSCREEN);

		int win_pos_x = resolution_x / 2 - WINSIZE_X / 2;
		int win_pos_y = resolution_y / 2 - WINSIZE_Y / 2;

		RECT rt = { win_pos_x, win_pos_y, win_pos_x + WINSIZE_X, win_pos_y + WINSIZE_Y };
		AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
		MoveWindow(
			g_hwnd,
			win_pos_x,
			win_pos_y,
			rt.right - rt.left,
			rt.bottom - rt.top,
			TRUE
		);
	}

	HDC hdc = GetDC(g_hwnd);

	HBITMAP bit_map = (HBITMAP)(CreateCompatibleBitmap)(hdc, WINSIZE_X, WINSIZE_Y);
	auto prev_bit_map = SelectObject(g_hdc, bit_map);
	DeleteObject(prev_bit_map);

	int cur_mine = 0;
	for(int y = 0; y < map_size_y; y++)
		for (int x = 0; x < map_size_x; x++)
		{
			map[y][x].is_hide = true;
			map[y][x].around_mines = -1;

			if (cur_mine < mine_count)
			{
				cur_mine++;
				map[y][x].is_mine = true;
			}
			else
				map[y][x].is_mine = false;
		}

	for (int i = 0; i < (map_size_x + map_size_y) * 10; i++)
	{
		int x1 = rand() % map_size_x;
		int x2 = rand() % map_size_x;
		int y1 = rand() % map_size_y;
		int y2 = rand() % map_size_y;

		bool is_mine = map[x1][y1].is_mine;
		map[x1][y1].is_mine = map[x2][y2].is_mine;
		map[x2][y2].is_mine = is_mine;
	}

	comp = map_size_x * map_size_y - mine_count;
	comp_count = 0;
}

void MainGame::Update()
{
}

void MainGame::Render()
{
	PAINTSTRUCT ps; 
	HDC hdc = BeginPaint(g_hwnd, &ps);
	PatBlt(g_hdc, 0, 0, WINSIZE_X, WINSIZE_Y, WHITENESS);

	{
		for (int i = 0; i < map_size_x; i++)
		{
			MoveToEx(g_hdc, 50 * i, 0, nullptr);
			LineTo(g_hdc, 50 * i, WINSIZE_Y);
		}

		for (int i = 0; i < map_size_y; i++)
		{
			MoveToEx(g_hdc, 0, 50 * i, nullptr);
			LineTo(g_hdc, WINSIZE_X, 50 * i);
		}

		for (int y = 0; y < map_size_y; y++)
			for (int x = 0; x < map_size_x; x++)
			{
				int pos_x = x * 50 + 20;
				int pos_y = y * 50 + 20;

				wstring str;
				if (map[y][x].is_hide == false)
				{
					if (map[y][x].is_mine == false)
						str += to_wstring(map[y][x].around_mines);
					else
						str += L"※";
				}
				else if(map[y][x].is_mine)
					str += L"※";

				TextOut(g_hdc, pos_x, pos_y, str.c_str(), str.size());
			}
	}

	BitBlt(hdc, 0, 0, WINSIZE_X, WINSIZE_Y, g_hdc, 0, 0, SRCCOPY);
	EndPaint(g_hwnd, &ps);
}

void MainGame::Click()
{
	int x = mouse.x / 50;
	int y = mouse.y / 50;

	if (x < 0 || y < 0)
		return;

	if (x >= map_size_x || y >= map_size_y || x < 0 || y < 0)
		return;

	if (map[y][x].is_hide == false)
		return;

	if (CheckMap(y, x) == false)
	{
		MessageBox(g_hwnd, L"지뢰를 밟았습니다 패배!", L"패배", MB_OK);

		PostQuitMessage(0);
	}
	else if(comp == comp_count)
	{
		InvalidateRect(g_hwnd, nullptr, true);

		auto input = MessageBox(g_hwnd, L"지뢰를 모두 찾았습니다 다시 하겠습니까?", L"승리", MB_YESNO);

		if (input == IDYES)
		{
			map_size_x += map_size_x * 0.3;
			map_size_y += map_size_y * 0.3;
			mine_count += mine_count * 0.5;

			Init();
		}
		else
			PostQuitMessage(0);
	}
}

bool MainGame::CheckMap(int row, int col)
{
	if (col >= map_size_x || row >= map_size_y || col < 0 || row < 0)
		return true;

	if (map[row][col].is_hide == false)
		return true;

	if (map[row][col].is_mine == true)
		return false;

	comp_count++;
	map[row][col].is_hide = false;

	int mine_count = 0;
	if (CheckMine(row + 1, col)) mine_count++;
	if (CheckMine(row + 1, col - 1)) mine_count++;
	if (CheckMine(row + 1, col + 1)) mine_count++;
	if (CheckMine(row, col - 1)) mine_count++;
	if (CheckMine(row, col + 1)) mine_count++;
	if (CheckMine(row - 1, col)) mine_count++;
	if (CheckMine(row - 1, col - 1)) mine_count++;
	if (CheckMine(row - 1, col + 1)) mine_count++;

	map[row][col].around_mines = mine_count;

	if (mine_count == 0)
	{
		CheckMap(row + 1, col);
		CheckMap(row + 1, col - 1);
		CheckMap(row + 1, col + 1);
		CheckMap(row, col - 1);
		CheckMap(row, col + 1);
		CheckMap(row - 1, col);
		CheckMap(row - 1, col - 1);
		CheckMap(row - 1, col + 1);
	}

	return true;
}

bool MainGame::CheckMine(int row, int col)
{
	if (col >= map_size_x || row >= map_size_y || col < 0 || row < 0)
		return false;

	if (map[row][col].is_mine == true) 
		return true;
	else 
		return false;
}
