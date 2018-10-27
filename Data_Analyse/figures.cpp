#include "figures.h"


point::point(double x, double y, double z)
{
	X = x;
	Y = y;
	Z = z;
}
point::point()
{}

point::~point()
{

}

void point::SetY(double y)
{
	Y = y;
}



double point::GetX()
{
	return X;
}
double point::GetY()
{
	return Y;
}
double point::GetZ()
{
	return Z;
}

double DistXZBetweenTwoPoints(point a, point b)						// Obtention de la distance XY entre deux points
{
	double dist;

	dist = sqrt((a.X - b.X) * (a.X - b.X) + (a.Z - b.Z) * (a.Z - b.Z));

	return dist;
}
double DistXYZBetweenTwoPoints(point a, point b)						// Obtention de la distance totale entre deux points
{
	double dist;

	dist = sqrt((a.X - b.X) * (a.X - b.X) + (a.Y - b.Y) * (a.Y - b.Y) + (a.Z - b.Z) * (a.Z - b.Z));

	return dist;
}
list<point> GetCoordCircle(int nbround, int nbvalue, double ExtRadius, double IntRadius, double MaxHeight, double SecureDistBetweenCircles)        // Fonction de génération de colimaçon 2D de manière basique
{
	int NbValuesForARound;
	NbValuesForARound = nbvalue / nbround;
	list<point> Act_Lst_Pt;
	point p;

	double DistBetweenCircle, DistBetweenPos;

	DistBetweenCircle = MaxHeight * 2 + SecureDistBetweenCircles;


	double x, z, y;



	for (int i = 0; i < nbvalue; i++)
	{

		z = (ExtRadius - MaxHeight - (float)((float)((float)i / (float)NbValuesForARound)  * DistBetweenCircle)) *  sin(i * ((2 * M_PI) / (float)NbValuesForARound));
		x = (ExtRadius - MaxHeight - (float)((float)((float)i / (float)NbValuesForARound)  * DistBetweenCircle)) *  cos((float)i * ((2 * M_PI) / (float)NbValuesForARound));
		y = 0;
		p = point(x, y, z);
		Act_Lst_Pt.push_back(p);
	}

	return Act_Lst_Pt;
}

list<point> GetCoordCircle2(int nbround, int nbvalue, double ExtRadius, double IntRadius, double MaxHeight, double SecureDistBetweenCircles)        // Fonction de génération de colimaçon 2D de manière plus complexe
{
	list<int>  NbValuesForARound;

	int NbValueForThisCircle = 0;

	double DistBetweenCircle, DistBetweenPos, AngleVariation;
	DistBetweenCircle = MaxHeight * 2 + SecureDistBetweenCircles;

	list<double>  Radius;
	Radius = Getradius(DistBetweenCircle, nbround, ExtRadius - MaxHeight, MaxHeight);
	NbValuesForARound = GetNbDataPerCicrcle(Radius, nbvalue, nbround);

	list<point> Act_Lst_Pt;
	point p;

	int i;
	double x, z, y;


	for (i = 0; i < nbvalue; i++)
	{
		NbValueForThisCircle = GetWhichCircle(i, NbValuesForARound, nbround);
		z = (ExtRadius - MaxHeight - (float)((float)((float)i / (float)NbValueForThisCircle)  * DistBetweenCircle)) *  sin(i * ((2 * M_PI) / (float)NbValueForThisCircle));
		x = (ExtRadius - MaxHeight - (float)((float)((float)i / (float)NbValueForThisCircle)  * DistBetweenCircle)) *  cos((float)i * ((2 * M_PI) / (float)NbValueForThisCircle));
		y = 0;
		p = point(x, y, z);
		Act_Lst_Pt.push_back(p);

	}

	return Act_Lst_Pt;
}


void GetYCoordCircle(list<Data> Lst_Data, list<point> &Lst_Point, double MinValue, double MaxValue, int MaxY)				// Fonction complète le Y d'une liste de point en fonction des données à traiter
{
	list<point>::iterator itPoint;
	list<Data>::iterator itData;

	int i = 0;
	double Yval;
	double TempValue = MaxValue - MinValue;

	itData = Lst_Data.end();
	itData--;

	for (itPoint = Lst_Point.begin(); itPoint != Lst_Point.end(); itPoint++)
	{
		if (itData.operator!=(Lst_Data.begin()))
		{
			Yval = (*itData).GetAdjVal() - MinValue;
			Yval = (Yval / TempValue) * MaxY;
			(*itPoint).SetY(Yval);
			itData--;
		}
	}
}

void GetPreciseYCoordCircle(list<double> Lst_Data, list<point> &Lst_Point, double MinValue, double MaxValue, int MaxY)				// Fonction complète le Y d'une liste de point en fonction des données déja traitées et optimisées
{
	list<point>::iterator itPoint;
	list<double>::iterator itData;

	int i = 0;
	double Yval;
	double TempValue = MaxValue - MinValue;

	itData = Lst_Data.end();
	itData--;

	for (itPoint = Lst_Point.begin(); itPoint != Lst_Point.end(); itPoint++)
	{
		if (itData.operator!=(Lst_Data.begin()))
		{
			Yval = (*itData) - MinValue;
			Yval = (Yval / TempValue) * MaxY;
			(*itPoint).SetY(Yval);
			itData--;
		}
	}
}
int GetNbValue(list<point> Act_point)
{
	list<point>::iterator itc;
	int i = 0;

	for (itc = Act_point.begin(); itc != Act_point.end(); itc++)
	{
		i++;
	}
	return i;
}


ExportPointValue::ExportPointValue(double x, double y, double z, double RotX, double RotY, double RotZ, double Rad, double Hgt)
{
	X = x;
	Y = y;
	Z = z;
	rotateX = RotX;
	rotateY = RotY;
	rotateZ = RotZ;
	radius = Rad;
	height = Hgt;
}
ExportPointValue::ExportPointValue()
{}
ExportPointValue::~ExportPointValue()
{}

double ExportPointValue::GetX()
{
	return X;
}
double ExportPointValue::GetY()
{
	return Y;
}
double ExportPointValue::GetZ()
{
	return Z;
}
double ExportPointValue::GetRotX()
{
	return rotateX;
}
double ExportPointValue::GetRotY()
{
	return rotateY;
}
double ExportPointValue::GetRotZ()
{
	return rotateZ;
}
double ExportPointValue::GetRadius()
{
	return radius;
}
double ExportPointValue::GetHeight()
{
	return height;
}


list<ExportPointValue> ComputeDatatoExport(list<point> Act_Data, int NbRound, double Recover, double SecuritySize, double DistBetweenCircle, double CylinderRadius, double CylinderMaxRadius, double CylinderDefaultSize)
{
	list<ExportPointValue> Data_ToExport;
	list<point>::iterator itc, itcmore, itend;

	int NbVal = GetNbValue(Act_Data);
	int ValPerRound = NbVal / NbRound;
	double DegreePerVal = (360.0 / (float)ValPerRound);
	double lenght;
	double angle;
	double radius, anglevariation, anglevariationperval;
	int i = 0;

	itend = Act_Data.end();
	itend--;
	itcmore = Act_Data.begin();
	itcmore++;

	for (itc = Act_Data.begin(); itc != Act_Data.end(); itc++)											// Dessin de tous les cylindres
	{
		if (itc.operator==(itend))
		{
			Data_ToExport.push_back(ExportPointValue((*itc).GetX(), (*itc).GetY(), (*itc).GetZ(), 0, (i *DegreePerVal), 0, CylinderRadius, lenght));
			i++;
		}
		else
		{
			lenght = DistXZBetweenTwoPoints(*itc, *itcmore) * (double)(1 + Recover);										// Obtention de la longueur entre deux cylindre + Calcul longueur du cylindre à afficher
			if (lenght > SecuritySize)																			// Correction en cas d'erreur de longueur
			{
				lenght = CylinderDefaultSize;
			}

			// Calcul de la variation d'angle du au fait que le rayon du cercle diminue
			radius = sqrt((*itc).GetX() * (*itc).GetX() + (*itc).GetZ() *(*itc).GetZ());
			anglevariation = GetAngleVariation(radius, (DistBetweenCircle + CylinderMaxRadius * 2));
			anglevariationperval = (anglevariation / (float)ValPerRound);
			angle = (-(i * DegreePerVal) - (anglevariationperval * (float)(i%ValPerRound)));													// Calcul de l'angle à modifier selon l'axe Y

			Data_ToExport.push_back(ExportPointValue((*itc).GetX(), (*itc).GetY(), (*itc).GetZ(), 0, angle, 0, CylinderRadius, lenght));
			
			i++;
			itcmore++;

		}
	}
	return Data_ToExport;
}