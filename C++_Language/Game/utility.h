#pragma once

#define WIN32_LEAN_AND_MEAN //Windows.h ���� �ʿ���� ��� ����

//Macro Function
#define SAFE_DELETE(p) {if(p) { delete (p); (p) = nullptr; }}
#define SAFE_DELETE_ARRAY(p) {if(p) { delete[] (p); (p) = nullptr; }}

#include<Windows.h>
#include<iostream>
#include<conio.h>
#include<random>
#include<time.h>
#include<stdlib.h>


void gotoxy(int x, int y);
