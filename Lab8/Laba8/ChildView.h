// ChildView.h : interface of the CChildView class
//
#pragma once

#define DROW1 1
#define SURFACE1 2
#define LIGHT 3
#define DIFFUZE 4
#define ZERKALO 5

class CChildView : public CWnd
{

public:
	CChildView();

public:
	CRect WinRect;	
	CMatrix PView;	
	CMatrix PLight;
	int Index;

	// Пирамида
	CMatrix VA, VB, VC, VD;	// Координаты вершин A,B,C,D пирамиды
//	CMatrix PView;          // Координаты точки наблюдения
	CRect RS, RW;            // Область в мировых и оконных координатах - int
	int IsData, Rezult, IsRotateX, IsRotateY, IsRotateZ;
	double fx, fy, fz, dfi, dT, f0;      // Для вращения вокруг осей X, Y, Z
										 // Поверхность
	POINT **MasPOINT;
	int Nx, Ny;
	CRectD RD;
	//  Сфера
	double Radius;
	CMatrix PSourceLight;
	double Ks;
	COLORREF Color;
	int TypeModel;

protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

public:
	virtual ~CChildView();

protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
public:
	afx_msg void OnSphere_Mirror();
	afx_msg void OnSphere_Diffuse();
};

