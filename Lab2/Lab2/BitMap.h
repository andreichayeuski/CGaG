#pragma once
#include <Windows.h>

#define def_X 2
#define def_Y 2

int ShowBitMap(HWND hWnd, HANDLE hBit, int x, int y);	// функция для отображения изображения в формате BMP
int ClientToBmp(HWND hwnd, RECT& r, char* name);		// функция для сохранения изображения в формате BMP