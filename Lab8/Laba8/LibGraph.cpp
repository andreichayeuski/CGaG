#include "stdafx.h"

CRectD::CRectD(double l, double t, double r, double b)
{
	left = l;
	top = t;
	right = r;
	bottom = b;
}

void CRectD::SetRectD(double l, double t, double r, double b)
{
	left = l;
	top = t;
	right = r;
	bottom = b;
}

CSizeD CRectD::SizeD()
{
	CSizeD cz;
	cz.cx = fabs(right - left);	// Ширина прямоугольной области
	cz.cy = fabs(top - bottom);	// Высота прямоугольной области
	return cz;
}

CMatrix SpaceToWindow(CRectD& RS, CRect& RW)
// Возвращает матрицу пересчета координат из мировых в оконные
// RS - область в мировых координатах - double
// RW - область в оконных координатах - int
{
	CMatrix M(3, 3);
	CSize sz = RW.Size();	 // Размер области в ОКНЕ
	int dwx = sz.cx;	     // Ширина
	int dwy = sz.cy;	     // Высота
	CSizeD szd = RS.SizeD(); // Размер области в МИРОВЫХ координатах

	double dsx = szd.cx;    // Ширина в мировых координатах
	double dsy = szd.cy;    // Высота в мировых координатах

	double kx = (double)dwx / dsx;   // Масштаб по x
	double ky = (double)dwy / dsy;   // Масштаб по y


	M(0, 0) = kx;  M(0, 1) = 0;    M(0, 2) = (double)RW.left - kx*RS.left;
	M(1, 0) = 0;   M(1, 1) = -ky;  M(1, 2) = (double)RW.bottom + ky*RS.bottom;
	M(2, 0) = 0;   M(2, 1) = 0;    M(2, 2) = 1;
	return M;
}

CMatrix VectorMult(CMatrix& V1, CMatrix& V2)
// Вычисляет векторное произведение векторов V1 и V2
{
	CMatrix W(3);
	W(0) = V1(1)*V2(2) - V1(2)*V2(1);
	W(1) = -(V1(0)*V2(2) - V1(2)*V2(0));
	W(2) = V1(0)*V2(1) - V1(1)*V2(0);
	return W;
}

double ScalarMult(CMatrix& V1, CMatrix& V2)
// Вычисляет скалярное произведение векторов V1 и V2
{
	double p = V1(0)*V2(0) + V1(1)*V2(1) + V1(2)*V2(2);
	return p;
}

double ModVec(CMatrix& V)
// Вычисляет модуль вектора V
{
	double q = sqrt(V(0)*V(0) + V(1)*V(1) + V(2)*V(2));
	return q;
}

double CosV1V2(CMatrix& V1, CMatrix& V2)
// Вычисляет КОСИНУС угла между векторами V1 и V2
{
	double modV1 = ModVec(V1);
	double modV2 = ModVec(V2);
	double cos_f = ScalarMult(V1, V2) / (modV1*modV2);
	return cos_f;
}

CMatrix CreateViewCoord(double r, double fi, double q)
// Создает матрицу пересчета (4x4) точки из мировой системы координат в видовую
// (r,fi,q)- координата ТОЧКИ НАБЛЮДЕНИЯ(начало видовой системы координат)
// в мировой сферической системе координат( углы fi и q в градусах)
{
	double fg = fmod(fi, 360.0);
	double ff = (fg / 180.0)*pi; 
	fg = fmod(q, 360.0);
	double qq = (fg / 180.0)*pi; 

	CMatrix VM(4, 4);
	VM(0, 0) = -sin(ff);   VM(0, 1) = cos(ff);
	VM(1, 0) = -cos(qq)*cos(ff);	VM(1, 1) = -cos(qq)*sin(ff);	VM(1, 2) = sin(qq);
	VM(2, 0) = -sin(qq)*cos(ff);	VM(2, 1) = -sin(qq)*sin(ff);	VM(2, 2) = -cos(qq); VM(2, 3) = r;
	VM(3, 3) = 1;
	return VM;
}

CMatrix SphereToCart(CMatrix& PView)
// Преобразует сферические координаты PView  точки в декартовы
// PView(0) - r
// PView(1) - fi - азимут(отсчет от оси X), град.
// PView(2) - q - угол(отсчетот оси Z), град.
// Результат: R(0)- x, R(1)- y, R(2)- z	
{
	CMatrix R(3);
	double r = 60;
	double fi = PView(1);						// Градусы
	double q = PView(2);						// Градусы
	double fi_rad = (fi / 180.0)*pi;	// Перевод fi в радианы
	double q_rad = (q / 180.0)*pi;		// Перевод q в радианы
	R(0) = r * sin(q_rad)*cos(fi_rad);	// x- координата точки наблюдения
	R(1) = r * sin(q_rad)*sin(fi_rad);	// y- координата точки наблюдения
	R(2) = r * cos(q_rad);							// z- координата точки наблюдения
	return R;
}