#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"

#include "Lab2.h"
#include "MainFrm.h"
#include "BitMap.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


BEGIN_MESSAGE_MAP(CLab2App, CWinApp)

END_MESSAGE_MAP()

void CLab2App::LoadImageBMP(CPoint point)
{
	CFileDialog fileDialog(true);	// объект класса выбора файла
	int result = fileDialog.DoModal();	// запустить диалоговое окно
	if (result == IDCANCEL) return;			// Если пользователь отказался от выбора
	CWnd *cwnd = AfxGetMainWnd();	// получить указатель на активное главное окно приложения
	hwnd = cwnd->GetSafeHwnd();				// Возвращает m_hWnd или NULL если указатель thisNULL.
	hBit = (HBITMAP)LoadImage(NULL, fileDialog.GetPathName().GetBuffer(), IMAGE_BITMAP,
		0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);	//загрузка изображения
	ShowBitMap(hwnd, hBit, point.x, point.y);	//вывод изображения
}

void CLab2App::SaveArea()
{
	CFileDialog fileDialog((BOOL)FALSE, NULL, L"SaveArea.bmp");	//объект класса выбора файла
	int result = fileDialog.DoModal();	//запустить диалоговое окно
	if (result == IDOK)	//если файл выбран
	{
		CWnd *cwnd = AfxGetMainWnd();
		HWND hwnd = cwnd->GetSafeHwnd();
		RECT r;  //r – область в окне, куда выводится изображение
		if (From.x < To.x)																
		{
			r.left = From.x;
			r.right = To.x;
			r.top = From.y;
			r.bottom = To.y;
		}
		else
		{
			r.left = To.x;
			r.right = From.x;
			r.top = To.y;
			r.bottom = From.y;
		}
		ClientToBmp(hwnd, r, (char*)fileDialog.GetPathName().GetBuffer());
	}
}

// Создание CLab2App

CLab2App::CLab2App()
{
	SetAppID(_T("Lab2.AppID.NoVersion"));
	index = 0;
}

CLab2App theApp;	// Единственный объект CLab2App

BOOL CLab2App::InitInstance()	// Инициализация CLab2App
{
	CWinApp::InitInstance();
	EnableTaskbarInteraction(FALSE);
	SetRegistryKey(_T("Локальные приложения, созданные с помощью мастера приложений"));

	// Чтобы создать главное окно, этот код создает новый объект окна
	// рамки, а затем задает его как объект основного окна приложения
	CMainFrame* pFrame = new CMainFrame;
	if (!pFrame)
		return FALSE;
	m_pMainWnd = pFrame;
	// создайте и загрузите рамку с его ресурсами
	pFrame->LoadFrame(IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL,
		NULL);

	// Одно и только одно окно было инициализировано, поэтому отобразите и обновите его
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();
	return TRUE;
}

int CLab2App::ExitInstance()
{
	//TODO: обработайте дополнительные ресурсы, которые могли быть добавлены
	return CWinApp::ExitInstance();
}


class CAboutDlg : public CDialogEx
{
public:

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()



//void CLab2App::SaveScreen()
//{
//	CFileDialog fileDialog((BOOL)FALSE, NULL, L"ScreenSave.bmp");	//объект класса выбора файла
//	int result = fileDialog.DoModal();	//запустить диалоговое окно
//	if (result == IDOK)	//если файл выбран
//
//	{
//		CWnd *cwnd = AfxGetMainWnd();
//		HWND hwnd = cwnd->GetSafeHwnd();
//
//		ClientToBmp(hwnd, (char*)fileDialog.GetPathName().GetBuffer());
//	}
//}