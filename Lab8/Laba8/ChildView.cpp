// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "Laba8.h"
#include "ChildView.h"
#include "MainFrm.h"
#include "LibLabs3D.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

COLORREF Color = RGB(255, 0, 0);
CChildView::CChildView()
{
	Index = 3;
	PView.RedimMatrix(3);
	PLight.RedimMatrix(3);

	PSourceLight.RedimMatrix(3);
	IsData = 0;
	MasPOINT = NULL;
}

CChildView::~CChildView()
{
}

BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_COMMAND(ID_32779, &CChildView::OnSphere_Mirror)
	ON_COMMAND(ID_32780, &CChildView::OnSphere_Diffuse)
END_MESSAGE_MAP()

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;
	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1), NULL);

	return TRUE;
}

void CChildView::OnPaint()
{
	CPaintDC dc(this); 
	if (Index == 0)	
		DrawLightSphere(dc, 1, PView, PLight, WinRect, RGB(40, 255, 0), Index);
	if (Index == 1)
		DrawLightSphere(dc, 1, PView, PLight, WinRect, RGB(40, 255, 0), Index);
}

void CChildView::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);
	WinRect.SetRect(50, 50, cx - 50, cy - 50);
}

void CChildView::OnSphere_Mirror()
{
	Index = 1;
	/*PView(0) = 100;
	PView(1) = 150;
	PView(2) = 120;*/
	Invalidate();
	//RW.SetRect(100, 50, 300, 250);					// ќбласть в окне
	//Radius = 20;
	PView(0) = 100;	PView(1) = 0;  PView(2) = 60;
	//PSourceLight(0) = 100;  PSourceLight(1) = 0; PSourceLight(2) = 0;
	//Color = RGB(255, 255, 0);
	//Ks = 1.0;
	//IsData = LIGHT;
	//TypeModel = 1;
	//InvalidateRect(NULL);
}

void CChildView::OnSphere_Diffuse()
{
	Index = 0;
	//PView(0) = 100;
	//PView(1) = 150;
	//PView(2) = 120;
	Invalidate();
	//RW.SetRect(100, 50, 300, 250);					// ќбласть в окне
	//Radius = 20;
	PView(0) = 100;	PView(1) = 0;  PView(2) = 60;
	//PSourceLight(0) = 100;  PSourceLight(1) = 0; PSourceLight(2) = 0;
	//Color = RGB(255, 0, 0);
	//Ks = 1.0;
	//IsData = LIGHT;
	//TypeModel = 0;
	//InvalidateRect(NULL);
}