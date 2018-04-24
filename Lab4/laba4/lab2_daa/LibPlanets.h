#pragma once
#include "CMATRIX.H"

struct CMyPen
{
	int PenStyle;
	int PenWidth;
	COLORREF color;
	CMyPen()
	{
		PenStyle = PS_SOLID;
		PenWidth = 1;
		color = RGB(0, 0, 0);
	}

	void Set(int PS, int PW, COLORREF col)
	{
		PenStyle = PS; // стиль пера
		PenWidth = PW; // толщина пера
		color = col; // цвет
	}
};
struct CSizeD
{
	double cx;
	double cy;
};
class CRectD // Прямоугольник области в МСК
{
public:
	double top, bottom, left, right;
	CRectD()
	{
		top = bottom = left = right = 0;
	}
	CRectD(double t, double b, double l, double r)
	{
		top = t;
		bottom = b;
		left = l;
		right = r;
	};
	void SetRectD(double l, double t, double r, double b);
	CSizeD SizeD();
};

CMatrix SpaceToWindow(CRectD& rs, CRect& rw);
// Возвращает матрицу пересчета координат из мировых в оконные
// rs - область в мировых координатах - double
// rw - область в оконных координатах - int

void SetMyMode(CDC& dc, CRect& RW, CRectD& RS);
// Устанавливает режим отображения MM_ANISOTROPIC и его параметры
// dc - ссылка на класс CDC MFC
// RS -  область в мировых координатах 
// RW -	 Область в оконных координатах - int 

const double pi = 3.14;

CMatrix CreateTranslate2D(double dx, double dy);
// Формирует матрицу для преобразования координат объекта при его смещении 
// на dx по оси X и на dy по оси Y в фиксированной системе координат

CMatrix CreateRotate2D(double fi);
// Формирует матрицу для преобразования координат объекта при его повороте
// на угол fi (при fi>0 против часовой стрелки) в фиксированной системе координат

class CSunSystem
{
	CRect Sun;		      // Прямоугольник Солнца
	CRect Earth;          // Прямоугольник Земли
	CRect Moon;		      // Прямоугольник Луны
	CRect EarthOrbit;     // Прямоугольник, описанный вокруг орбиты Земли
	CRect MoonOrbit;      // Прямоугольник, описанный вокруг орбиты Луны
	CRect Planet51;       // Прямоугольник Марса
	CRect Planet51Orbit;  // Прямоугольник, описанный вокруг орбиты Марса
	CMatrix ECoords;      // Текущие координаты Земли в СК Солнца ( x,y,1)
	CMatrix MCoords;      // Текущие координаты Луны в СК Земли ( x,y,1)
	CMatrix VCoords;
	CRect RW;		      // Прямоугольник в окне
	CRectD RS;		      // Прямоугольник области в МСК
	double wEarth;		  // Угловая скорость Земли относительно Солнца, град./сек.
	double wMoon;		  // Угловая скорость Луны относительно Солнца, град./сек.
	double wPlanet51;     // Угловая скорость Марса относительно Солнца, град./сек.
	double fiE;			  // Угловое положение Земли в системе кординат Солнца, град
	double fiM;			  // Угловое положение Луны в системе кординат Земли, град
	double fiV;           // Угловое положение Марса в системе кординат Земли, град
	double dt;			  // Интервал дискретизации, сек.
public:
	CSunSystem();
	void SetDT(double dtx) // Установка интервала дискретизации
	{
		dt = dtx;
	};
	void SetNewCoords();     // Вычисляет новые координаты планет
	void GetRS(CRectD& RSX); // Возвращает область графика в мировой СК
	CRect GetRW() 
	{ 
		return RW;           // Возвращает область графика в окне	
	};	   
	void Draw(CDC& dc);		 // Рисование без самостоятельного пересчета координат
};
