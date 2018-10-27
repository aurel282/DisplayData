#include "data.h";


Data::Data() {};

Data::Data(int Act_Month, int Act_Day, int Act_Year, double Act_Value, double Act_Vol, double Act_Open, double Act_High, double Act_Low, double Act_Adj_Val)
{
	month = Act_Month;
	day = Act_Day;
	year = Act_Year;
	value = Act_Value;
	volume = Act_Vol;
	open = Act_Open;
	high = Act_High;
	low = Act_Low;
	Adjusted_Value = Act_Adj_Val;
}
Data::Data(const Data& temp)							// Constructeur copie 
{
	month = temp.month;
	day = temp.day;
	year = temp.year;
	value = temp.value;
	volume = temp.volume;
	open = temp.open;
	high = temp.high;
	low = temp.low;
	Adjusted_Value = temp.Adjusted_Value;
}
Data::~Data(){}

double Data::GetAdjVal()
{
	return Adjusted_Value;
}

double Data::GetVol()
{
	return volume;
}

void Data::Show_Data()												// Fonction qui affiche une instance de la classe Data
{
	cout << "Date :" << year << "-" << month << "-" << day << endl;
	cout << "Valeur :" << value << endl;
	cout << "Valeur ajustée : " << Adjusted_Value << endl;
	cout << "Ouverture : " << open << endl;
	cout << "Maximum : " << high << endl;
	cout << "Minimum : " << low << endl;
	cout << "Volume : " << volume << endl;
}

void Data::setmonth(int data)
{
	month = data;
}

bool Data::HasEmptyField()											// Fonction qui vérifie si une instance de Data possède un élement égal à 0
{
	if (month == 0)
	{
		return true;
	}
	if (year == 0)
	{
		return true;
	}
	if (day == 0)
	{
		return true;
	}
	if (Adjusted_Value == 0)
	{
		return true;
	}
	if (high == 0)
	{
		return true;
	}
	if (low == 0)
	{
		return true;
	}
	if (open == 0)
	{
		return true;
	}
	if (value == 0)
	{
		return true;
	}
	if (volume == 0)
	{
		return true;
	}
	return false;
}

void Data::Complete_Empty_Field(Data temp)								// Fonction qui complête une instance de Data avec une autre
{
	if (month == 0)
	{
		month = temp.month;
	}
	if (year == 0)
	{
		year = temp.year;
	}
	if (day == 0)
	{
		day = temp.day;
	}
	if (Adjusted_Value == 0)
	{
		Adjusted_Value = temp.Adjusted_Value;
	}
	if (high == 0)
	{
		high = temp.high;
	}
	if (low == 0)
	{
		low = temp.low;
	}
	if (open == 0)
	{
		open = temp.open;
	}
	if (value == 0)
	{
		value = temp.value;
	}
	if (volume == 0)
	{
		volume = temp.volume;
	}
}

// ==================================================================================================================================================================

//																				FONCTION TRAITEMENT LISTE DE DATA

// ==================================================================================================================================================================


int GetNbValue(list<Data> Act_data)										// Obtention du nombre de valeur
{
	list<Data>::iterator itc;
	int i = 0;
	Data TempInst = Data();

	for (itc = Act_data.begin(); itc != Act_data.end(); itc++)
	{
		i++;
	}
	return i;
}



double GetMaxValue(list<Data> Act_data)									// Obtention de la valeur Max
{
	double i = 0;
	list<Data>::iterator itc;
	for (itc = Act_data.begin(); itc != Act_data.end(); itc++)
	{
		if (i < (*itc).GetAdjVal())
		{
			i = (*itc).GetAdjVal();
		}
	}
	return i;
}

double GetMinValue(list<Data> Act_data)									// Obtention de la valeur min
{
	double i = 99999999999;
	list<Data>::iterator itc;
	for (itc = Act_data.begin(); itc != Act_data.end(); itc++)
	{
		if (i > (*itc).GetAdjVal())
		{
			i = (*itc).GetAdjVal();
		}
	}
	return i;
}

int GetMaxVolume(list<Data> Act_data)									// Obtention du volume max
{
	double i = 0;
	list<Data>::iterator itc;
	for (itc = Act_data.begin(); itc != Act_data.end(); itc++)
	{
		if (i < (*itc).GetVol())
		{
			i = (*itc).GetVol();
		}
	}
	return i;
}

list<double> GetMorePreciseValues(list<Data> Act_data, int precision)				//Obtention d'un plus grand nombre de valeur pour plus de précision
{
	list<double> Values;

	double DataGap;


	list<Data>::iterator itc, itcmore, itend;
	itend = Act_data.end();
	itend--;
	itcmore = Act_data.begin();
	itcmore++;
	for (itc = Act_data.begin(); itc != itend; itc++)
	{
		DataGap = ((*itcmore).GetAdjVal() - (*itc).GetAdjVal()) / precision;

		for (int i = 0; i < precision; i++)
		{
			Values.push_back((*itc).GetAdjVal() + DataGap * i);
		}
		itcmore++;
	}
	return Values;
}