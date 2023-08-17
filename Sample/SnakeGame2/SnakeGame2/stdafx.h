#pragma once

#include<iostream>
#include<list>
#include<Windows.h>
#include<conio.h>
#include<stdlib.h>
#include<random>
#include<chrono>
#include<vector>
#include<cassert>

#include"Utility.h"
#include"Actor/Actor.h"
#include"Actor/Food.h"
#include"Actor/Snake.h"
#include"Actor/Wall.h"
#include"SnakeGame.h"


using namespace std;

constexpr int map_left = 10;
constexpr int map_top = 5;

constexpr int map_width = 40;
constexpr int map_height = 25;
