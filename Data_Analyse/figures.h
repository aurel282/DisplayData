#include <iostream>
#include <list>
#include "General_Function.h"
#include "Data.h"
#include <cmath>

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define M_PI 3.14159265358979323846										// Définition du nombre pi

#pragma once

class point																// Class de point 3D
{
public :
	double X;
	double Y;
	double Z;

	point(double x, double y, double z);
	point();

	~point();

	void SetY(double y);

	

	double GetX();
	double GetY();
	double GetZ();
};

class ExportPointValue
{
public:
	double X;
	double Y;
	double Z;
	double rotateX;
	double rotateY;
	double rotateZ;

	double radius;
	double height;

	ExportPointValue(double x, double y, double z,double RotX, double RotY, double RotZ, double Rad, double Hgt);
	ExportPointValue();
	~ExportPointValue();

	double GetX();
	double GetY();
	double GetZ();
	double GetRotX();
	double GetRotY();
	double GetRotZ();
	double GetRadius();
	double GetHeight();

};


int GetNbValue(list<point> Act_point);
double DistXZBetweenTwoPoints(point a, point b);						// Obtention de la distance XY entre deux points
double DistXYZBetweenTwoPoints(point a, point b);						// Obtention de la distance totale entre deux points
list<point> GetCoordCircle(int nbround, int nbvalue, double ExtRadius, double IntRadius, double MaxHeight, double SecureDistBetweenCircles);        // Fonction de génération de colimaçon 2D de manière basique
list<point> GetCoordCircle2(int nbround, int nbvalue, double ExtRadius, double IntRadius, double MaxHeight, double SecureDistBetweenCircles);       // Fonction de génération de colimaçon 2D de manière plus complexe
void GetYCoordCircle(list<Data> Lst_Data, list<point> &Lst_Point, double MinValue, double MaxValue, int MaxY);				// Fonction complète le Y d'une liste de point en fonction des données à traiter
void GetPreciseYCoordCircle(list<double> Lst_Data, list<point> &Lst_Point, double MinValue, double MaxValue, int MaxY);				// Fonction complète le Y d'une liste de point en fonction des données déja traitées et optimisées
list<ExportPointValue> ComputeDatatoExport(list<point> Act_Data, int NbRound, double Recover, double SecuritySize, double DistBetweenCircle, double CylinderRadius, double CylinderMaxRadius, double CylinderDefaultSize);// Fonction qui calcule et crée une liste des Data pour la création de STL