#include <vector>
#include <Windows.h>
#pragma once
using namespace std;

////////////// === ОПРЕДЕЛЕНИЕ ТИПОВ === /////////////////////////////////

typedef vector<CMatrix> CVecMatrix;
typedef vector<CVecMatrix> CMasMatrix;

typedef vector<CPoint> CVecPoint;
typedef vector<CVecPoint> CMatrPoint;

double Function1(double x, double y);
double Function2(double x, double y);
double Function3(double x, double y);

class CPlot3D
// для изображения поверхности z=f(x,y)
{
	pfunc2 pFunc; // указатеь на функцию f(x,y), описывающую поверхность
	CRectD SpaceRect; // Прямоугольная область, на которую опирается поверхность в мировой СК
	CMasMatrix MatrF; // Матрица для хранения координат точек (x,y,z,1) поверхности в мировой СК
	CMasMatrix MatrView; // Матрица для хранения координат точек (x,y,1) проекции поверхности на плоскость ХУ видовой СК
	CRectD ViewRect; // Прямоугольная область, охватывающая проекцию поверхности на плоскость ХУ видовой СК
	CRect WinRect; // Прямоугольная область в оконной системе координат для рисования
	CMatrix ViewPoint; // Вектор (3х1) - координаты точки наблюдения в мировой
	                   // сферической систме координат (r,fi(град.), q(град.))
	CMatrPoint MatrWindow; // Матрица для хранения оконных координат Р(xi,yi) точек изображения 

public:
	CPlot3D();
	~CPlot3D(){ pFunc = NULL; };
	void SetFunction(pfunc2 pF, CRectD RS, double dx, double dy); // Устанавливает функцию f(x,y)
	void SetViewPoint(double r, double fi, double q); // Устанавливает положение точки наблюдения в МИРОВОЙ СК
	CMatrix GetViewPoint(); // Возвращает вектор ViewPoin
	void SetWinRect(CRect Rect); // Устанавливает область в окне для рисования
	void CreateMatrF(double dx, double dy);// Заполняет матрицу MatrF координатами точек поверхности
	void CreateMatrView(); // Заполняет матрицу MatrView координатами точек проекции поверхности на плоскость XY видовой СК
	void CreateMatrWindow(); // Заполняет матрицу MatrWindow 
	//int GetNamberRegion();  //Определяет номер овласти  для  рисования.
	void Draw(CDC& dc);
};
//r-модуль радиус-вектора
//fi-азимут от оси оХ против часовой стрелки 0-360
//q-угол от оси Z по часовой стрелке 0-180
