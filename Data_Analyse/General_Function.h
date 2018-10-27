#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <list>
#include <cmath>

#include "data.h"
#define M_PI 3.14159265358979323846	


using namespace std;



int GetTotal(list<int> Data, int size);


bool Check_Again();
void Read_CSV(list<Data> &Templst);											// Fonction qui complète une liste de Data à l'aide d'un csv
bool Yes_No(char temp);
void ConvertStringDateToIntYMD(string Date, int &year, int &month, int &day);	// fonction qui converti un string de date en 3 int -> Année, mois, jour
void Clear_Lst(list<Data> &Templst);												// Fonction qui vide une liste de Data
void Show_Lst(list<Data> Templst);													// Fonction qui affiche une liste de Data
void Complete_Data(list<Data> &List_Data);											// Fonction qui complète une liste de Data pour éviter les 0 dans les valeurs
list<int> GetNbDataPerCicrcle(list<double> radius, int NbValue, int nbround);					// Fonction qui calcule le nombre de données par cercle
list<int> GetNbDataPerCicrcleOptimised(list<double> radius, int NbMinValuePerCircle, int nbround);	// Fonction qui calcule le nombre de données par cercle avec un nombre minimum de données
list<double> Getradius(double DistBewteenCircle, int nbround, double MaxRadius, double MaxCylindreRadius);					// Fonction qui calcule les rayons de chaque cercles
int GetWhichCircle(int DataNumber, list<int> NbDataCircle, int nbround);
double GetAngleVariation(double Radius, double Distbetweencircle);
