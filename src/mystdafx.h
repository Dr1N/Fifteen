#pragma once
#include <Windows.h>
#include <WindowsX.h>
#include <ctime>
#include <vector>
#include <CommCtrl.h>
#include "resource.h"
#pragma comment(lib, "comctl32") 

#define START_ID		10000
#define BUTTON_WIDTH	40
#define BUTTON_HEIGTH	40
#define SIZE			4
#define COUNT			SIZE * SIZE
#define OFFSET			20
#define TIME			300
#define SHUFFLE			100

enum DIRECTION {TOP = 1, RIGHT, DOWN, LEFT};