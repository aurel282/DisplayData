#pragma once

#include <iostream>
#include <list>
#include <string>




using std::count;
using namespace std;


class Data
{
public:

		int month;
		int day;
		int year;
		double value;
		double volume;
		double open;
		double high;
		double low;
		double Adjusted_Value;

														// Constructeurs

		Data();
		Data(int Act_Month, int Act_Day, int Act_Year, double Act_Value, double Act_Vol, double Act_Open, double Act_High, double Act_Low, double Act_Adj_Val);
		


		Data(const Data& temp);							// Constructeur copie 

		~Data();


		double GetAdjVal();
		double GetVol();
		void Show_Data();											// Fonction qui affiche une instance de la classe Data
		void setmonth(int data);
		bool HasEmptyField();											// Fonction qui vérifie si une instance de Data possède un élement égal à 0


		void Complete_Empty_Field(Data temp);								// Fonction qui complête une instance de Data avec une autre


};


list<double> GetMorePreciseValues(list<Data> Act_data, int precision);			//Obtention d'un plus grand nombre de valeur pour plus de précision
int GetNbValue(list<Data> Act_data);										    //Obtention du nombre de valeur
double GetMaxValue(list<Data> Act_data);									    //Obtention de la valeur Max
double GetMinValue(list<Data> Act_data);										//Obtention de la valeur min
int GetMaxVolume(list<Data> Act_data);											//Obtention du volume max
list<double> GetMorePreciseValues(list<Data> Act_data, int precision);			//Obtention d'un plus grand nombre de valeur pour plus de précision
