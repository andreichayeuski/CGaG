
#include "afxwin.h"						// MFC Основные и стандартные компоненты
#include "afxext.h"						// MFC Расширения
#include "resource.h"					// Идентификаторы ресурсов
#include "CMATRIX.H"
#include "LibPlanets.h"
#include "math.h"
#define IDR_MENU1		101

class CMainWnd : public CFrameWnd
{

public:
	CMainWnd();
	CSunSystem SunSystem; // Объект (конструктор по умолчанию)
	int dT_Timer;           // Интервал времени для таймера
	CRect RW;                            // Прямоугольник в окне
	CRectD RS;                           // Прямоугольник области в МСК
	bool Start;
	afx_msg void OnPaint();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	int OnCreate(LPCREATESTRUCT lpCreateStruct);
	void OnPlanetsModel();
	void MenuExit();
	~CMainWnd();
private:
	CMenu m_wndMenu;
	DECLARE_MESSAGE_MAP();
public:
	afx_msg void OnLabplanetsPlanets();
};

BEGIN_MESSAGE_MAP(CMainWnd, CFrameWnd)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDBLCLK()
	ON_WM_CREATE()
	ON_COMMAND(ID_FILE_OPEN, OnPlanetsModel)
	ON_COMMAND(ID_FILE_EXIT, MenuExit)
	ON_COMMAND(ID_LABPLANETS_PLANETS, &CMainWnd::OnLabplanetsPlanets)
END_MESSAGE_MAP()

void CMainWnd::OnPaint()
{
	//Установить размеры окна
	RECT rect;
	LPRECT prect = &rect;

	CWnd* m_hWnd = AfxGetApp()->GetMainWnd();

	m_hWnd->GetWindowRect(prect);

	(*prect).right = (*prect).left + 925;
	(*prect).bottom = (*prect).top + 700;

	m_hWnd->MoveWindow(prect);

	CPaintDC dc(this);
	if (Start == true)
	{
		SunSystem.GetRS(RS);    // солнечная система в мск
		RW = SunSystem.GetRW(); // солнечная система в окне
		SetMyMode(dc, RW, RS);  // Устанавливает режим отображения MM_ANISOTROPIC и его параметры
		SunSystem.Draw(dc);     // нарисовать солнечную систему
		dc.SetMapMode(MM_ANISOTROPIC); // Рисование выполнять в режиме MM_ANISOTROPIC
	}
}

void CMainWnd::OnLabplanetsPlanets()
{
	SunSystem.SetDT(0);       // Установка интервала дискретизации
	SunSystem.SetNewCoords(); // Вычисляет новые координаты планет
	SunSystem.SetDT(0.1);//Обновление координат через 0.1 сек.
	dT_Timer = 100; // Милисекунд
	Start = true;
	Invalidate();
}

void CMainWnd::OnTimer(UINT_PTR nIDEvent)
{
	SunSystem.SetNewCoords(); // новые к-ты
	Invalidate();             // перерисовка
}

void CMainWnd::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	SetTimer(1, dT_Timer, NULL); // запустить
	CWnd::OnLButtonDblClk(nFlags, point);
}

void CMainWnd::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	KillTimer(1); // остановить
	CWnd::OnRButtonDblClk(nFlags, point);
}

void CMainWnd::MenuExit() // выход из приложения
{
	DestroyWindow(); // закрыть окно
}

int CMainWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{

	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)  return -1;
	m_wndMenu.LoadMenu(IDR_MENU1);
	SetMenu(&m_wndMenu);
	Start = false;
	return 0;
}

CMainWnd::CMainWnd()
{
	Create(NULL, "Lab_4", (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU/* | WS_MINIMIZEBOX | WS_MAXIMIZEBOX*/) &~(WS_THICKFRAME), rectDefault, NULL, NULL);
}

CMainWnd::~CMainWnd()
{
}

class CMyApp : public CWinApp
{
public:
	CMyApp();
	virtual BOOL InitInstance();
};

CMyApp::CMyApp()
{}

BOOL CMyApp::InitInstance()
{
	m_pMainWnd = new CMainWnd();
	ASSERT(m_pMainWnd);
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
};

CMyApp theApp;

void CMainWnd::OnPlanetsModel()
{
	SunSystem.SetDT(0);
	SunSystem.SetNewCoords();
	SunSystem.SetDT(0.1);
	dT_Timer = 100;
	Start = true;
	Invalidate();
}