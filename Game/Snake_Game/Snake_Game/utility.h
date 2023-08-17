#pragma once

#define WIN32_LEAN_AND_MEAN //Windows.h 에서 필요없는 헤더 제외

//Macro Function
#define SAFE_DELETE(p) {if(p) { delete (p); (p) = nullptr; }}
#define SAFE_DELETE_ARRAY(p) {if(p) { delete[] (p); (p) = nullptr; }}
#define MAP_SIZE 25;

#include<Windows.h>
#include<iostream>
#include<conio.h>
#include<random>
#include<time.h>
#include<stdlib.h>
#include<vector>
#include<list>


void gotoxy(int x, int y, const char* string);

void ScreenInit();
void ScreenFlipping();
void ScreenClear();
void ScreenRelease();
void ScreenPrint(int x, int y, const char* string);
void Render();
void Release();