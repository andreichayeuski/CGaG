#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы

class CLab2App : public CWinApp
{
public:
	CLab2App();
	int index;
	HBITMAP hBit;   // hBit - дескриптор рисунка
	HWND hwnd;      // hWnd - дескриптор окна, куда выводится изображение
	CPoint From;
	CPoint To;

// Переопределение
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Реализация

public:
	void LoadImageBMP(CPoint point);	// загрузка изображения
	void SaveArea();	// сохранить выделенную область окна
	DECLARE_MESSAGE_MAP()
};

extern CLab2App theApp;
