
#include "stdafx.h"
#include "CMatrix.h"
#include "LibGraph.h"
#include "LibSurface.h"
#include "math.h"
#include "float.h"

double Function1(double x, double y)/////////
{
	return x * x + y * y; // первый график 
};

double Function2(double x, double y)///////
{
	return x * x - y * y; // 2-й график 
};

double Function3(double x, double y)///////
{
	double r = 1 - x * x - y * y; // 3-й график
	double z;
	if (r < 0)
	{
		z = 0;
	}
	else
	{
		z = sqrt(r);
	}
	return z;

	//double r = sqrt(x*x + y * y);
	/*double z;
	if (r < 0.001) z = 10;
	else z = 10 * sin(r) / r;
	return z;*/
};

CPlot3D::CPlot3D()///////////////
{
	pFunc = NULL;
	ViewPoint.RedimMatrix(3); // координаты точки наблюдения
	WinRect.SetRect(0, 0, 200, 200); // область для рисования 
	ViewPoint(0) = 10, ViewPoint(1) = 30;
	ViewPoint(2) = 45;
};

void CPlot3D::SetFunction(pfunc2 pF, CRectD RS, double dx, double dy)//////////
  // Устанавливает ф-ю f(x,y)
  // pFunc - указатель на ф-ю f(x,y) - воверхность для построения
  // RS - область в МСК (xmin,ymax,xmax,ymin) для расчета значений f(x) 
  // dx, dy - шаги для расчет значений f(x) по x и y 
  // VP - координаты точки наблюдения (r,fi,q) в сферической МСК  
  // RW - область в окне для рисования 
{
	pFunc = pF;
	// поверхность на которую опирается поверхность в мировой
	SpaceRect.SetRectD(RS.left, RS.top, RS.right, RS.bottom);
	MatrF.clear(); // очистить матрицу для хранения координат в МСК
	MatrView.clear(); // очистить м-цу для хранения к-т точек проекции
	// поверхности на пл-ть ХУ в ВСК
	MatrWindow.clear(); // очистить м-цу для хранения оконных к-т Р(xi,yi)
	// точек изображения
	CreateMatrF(dx, dy);    //коорд функции
	CreateMatrView();      //матрица видимости
	CreateMatrWindow();      //из мир в окон
}

void CPlot3D::SetViewPoint(double r, double fi, double q)////////////
// Устанавливает положение точки наблюдения в МИРОВОЙ СК - 
// -заполняет матрицу ViewPoint
// r - модуль радиус-вектора
// fi - азимут (от оси OX против часовой стрелки, 0-360), град.
// q  - угол (от оси Z по часовой стрелке, 0-180), град.

{
	ViewPoint(0) = r, ViewPoint(1) = fi;
	ViewPoint(2) = q;
	MatrView.clear();
	CreateMatrView();
	MatrWindow.clear();
	CreateMatrWindow();
}

CMatrix CPlot3D::GetViewPoint()//возвращает вектор
{
	CMatrix P = ViewPoint;
	return P;
}

void CPlot3D::SetWinRect(CRect Rect)//////
//устанавливает область в окне для рисования
// Rect - новая область
{
	WinRect = Rect;
	MatrWindow.clear();
	CreateMatrWindow(); // из мировых в оконные
}

void CPlot3D::CreateMatrF(double dx, double dy)//////////////заполняет матрицу MatrF координатами точек поверхности
// Заполняет матрицу MatrF координатами точек поверхности
// dx - шаг для расчета значений функции f(x,y) оси x
// dy - шаг для расчета значений функции f(x,y) оси y
{
	double xL = SpaceRect.left;
	double xH = SpaceRect.right;
	double yL = SpaceRect.bottom;
	double yH = SpaceRect.top;
	CVecMatrix VecMatrix;
	CMatrix V(4);
	V(3) = 1;
	double max = 0, maxx = 0, maxy = 0;
	for (double x = xL; x <= xH; x += dx)
	{
		VecMatrix.clear(); //очищаем вектор
		for (double y = yL; y <= yH; y += dy)
		{
			V(0) = x;
			V(1) = y;
			V(2) = pFunc(x, y); // указатель на ф-ю
			if (V(2) > max)
			{
				max = V(2);
				maxx = x;
				maxy = y;
			}
			VecMatrix.push_back(V);
		}
		MatrF.push_back(VecMatrix);
	}
	double left = 0, right = 0;
	left = maxx - xL;
	right = maxy - yL;
}

void CPlot3D::CreateMatrView()
// Заполняет матрицу MatrView координатами точек проекции поверхности f(x,y)
// на плоскость XY видовой СК 
// !!! И !!!
// Определяет прямоугольная область ViewRect, охватывающая проекцию 
// поверхности на плоскость XY видовой СК
{
	CMatrix MV = CreateViewCoord(ViewPoint(0), ViewPoint(1), ViewPoint(2)); //Матрица(4x4) пересчета  
																		//в видовуюсистему координат 
	CVecMatrix VecMatrix;
	CMatrix VX(4), V(3);
	V(2) = 1;
	double xmin = DBL_MAX;  // DBL_MAX - максимальное из double
	double xmax = DBL_MIN;	// DBL_MIN - минимальное из double
	double ymin = DBL_MAX;
	double ymax = DBL_MIN;

	for (int i = 0; i < MatrF.size(); i++)
	{
		VecMatrix.clear();
		for (int j = 0; j < MatrF[i].size(); j++)    //пересчет оконных координат
		{
			VX = MatrF[i][j];
			VX = MV * VX;
			V(0) = VX(0); // x- координата проекции
			V(1) = VX(1);	// y- координата проекции
			VecMatrix.push_back(V);
			//------- Для определения области ViewRect --------------------------
			double x = V(0);
			double y = V(1);
			if (x < xmin)xmin = x;
			if (x > xmax)xmax = x;
			if (y < ymin)ymin = y;
			if (y > ymax)ymax = y;
			// ------------------------------------------------------------------
		}
		MatrView.push_back(VecMatrix);
	}
	ViewRect.SetRectD(xmin, ymax, xmax, ymin);	// Определяем область
}

void CPlot3D::CreateMatrWindow()/////////////из мировых в оконные
// Заполняет матрицу MatrWindow оконными координатами точек изображения
{
	CMatrix MW = SpaceToWindow(ViewRect, WinRect); // Матрица (3 на 3)пересчета 
												   //в оконную систему координат
	CVecPoint VecPoint;
	CMatrix  V(3);
	for (int i = 0; i < MatrView.size(); i++)
	{
		VecPoint.clear();
		for (int j = 0; j < MatrView[i].size(); j++)
		{
			V = MatrView[i][j];
			V = MW * V;
			CPoint P((int)V(0), (int)V(1));
			VecPoint.push_back(P);
		}
		MatrWindow.push_back(VecPoint);
	}
}

void CPlot3D::Draw(CDC& dc)//////
{
	if (MatrWindow.empty())
	{
		TCHAR* error = _T("Массив данных для рисования в окне пуст! ");
		MessageBox(NULL, error, _T("Ошибка"), MB_ICONSTOP);
		return;
	}
	CPoint pt[4];
	int k, d;
	int nRows = MatrWindow.size();
	int nCols = MatrWindow[0].size(); // Все строки одинаковой длины!!!
	for (int i = 0; i < nRows - 1; i++)
		for (int j = 0; j < nCols - 1; j++)
		{
			pt[0] = MatrWindow[i][j];
			pt[1] = MatrWindow[i][j + 1];
			pt[2] = MatrWindow[i + 1][j + 1];
			pt[3] = MatrWindow[i + 1][j];
			dc.Polygon(pt, 4);
		}
}