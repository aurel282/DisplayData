#include "General_Function.h"

int GetTotal(list<int> Data, int size)
{
	int total = 0;
	list<int>::iterator itint;

	for (itint = Data.begin(); itint != Data.end(); itint++)
	{
		total += *itint;
	}

	return total;
}

bool Check_Again()
{
	bool again;
	bool first_step = true;
	char Temp[] = "";
	while (Temp[0] != char(121) && Temp[0] != char(110))
	{
		if (first_step)
		{
			cout << "Etes-vous sur de vouloir quitter? (y/n)" << endl;
			first_step = false;
		}
		else
		{
			cout << "=====================================================================================================================" << endl;
			cout << "!!!Entré incorrecte!!!" << endl;
			cout << "Etes-vous sur de vouloir quitter? (y/n)" << endl;
		}

		cin >> Temp[0];
	}


	if (Temp[0] == 'y')
	{
		again = false;
	}
	else
	{
		again = true;
	}
	return again;
}
void Read_CSV(list<Data> &Templst)											// Fonction qui complète une liste de Data à l'aide d'un csv
{

	Data Temp;

	int month;
	int day;
	int year;
	double value;
	double volume;
	double open;
	double high;
	double low;
	double Adjusted_Value;

	ifstream inFile("C:\\temp\\file.csv");
	string line;

	int linenum = 0;
	while (getline(inFile, line))
	{
		istringstream linestream(line);
		string item;
		int itemnum = 0;
		if (linenum > 0)
		{
			while (getline(linestream, item, ','))
			{

				switch (itemnum)
				{
				case 0:
					ConvertStringDateToIntYMD(item, year, month, day);
					break;
				case 1:
					open = stod(item);
					break;
				case 2:
					high = stod(item);
					break;
				case 3:
					low = stod(item);
					break;
				case 4:
					value = stod(item);
					break;
				case 5:
					volume = stod(item);
					break;
				case 6:
					Adjusted_Value = stod(item);
					break;
				default:

					break;

				}
				itemnum++;
			}

			Temp = Data(month, day, year, value, volume, open, high, low, Adjusted_Value);
			Templst.push_back(Temp);
		}

		linenum++;
	}


}

bool Yes_No(char temp)
{
	if (temp == 'y')
	{
		return true;
	}
	else
	{
		return false;
	}
}

void ConvertStringDateToIntYMD(string Date, int &year, int &month, int &day)	// fonction qui converti un string de date en 3 int -> Année, mois, jour
{
	string temp;
	int pos;
	int temp_size;

	pos = Date.find("-");
	year = stoi(Date.substr(0, pos));
	temp_size = Date.size();
	temp = Date.substr(pos + 1, temp_size - 1);

	pos = temp.find("-");
	month = stoi(temp.substr(0, pos));
	temp_size = temp.size();
	temp = temp.substr(pos + 1, temp_size - 1);

	day = stoi(temp.substr(0, temp_size - 1));


}

void Clear_Lst(list<Data> &Templst)													// Fonction qui vide une liste de Data
{
	Templst.clear();
}

void Show_Lst(list<Data> Templst)													// Fonction qui affiche une liste de Data
{
	list<Data>::iterator itc;
	int i = 0;
	Data tempInst;

	for (itc = Templst.begin(); itc != Templst.end(); itc++)
	{
		i++;
		cout << endl;
		cout << "Elément : " << i << endl;
		(*itc).Show_Data();
	}
}

void Complete_Data(list<Data> &List_Data)											// Fonction qui complète une liste de Data pour éviter les 0 dans les valeurs
{
	list<Data>::iterator itc, Temp, end, begin;
	int i = 0;
	bool Continue;

	end = List_Data.end();
	end--;
	begin = List_Data.begin();
	begin++;

	for (itc = List_Data.begin(); itc != List_Data.end(); itc++)
	{
		if ((*itc).HasEmptyField())
		{
			if (itc.operator==(end))
			{
				Temp = itc;
				Continue = true;
				while ((*Temp--).HasEmptyField() == true && Continue == true)
				{
					if (Temp == List_Data.begin())
					{
						Continue = false;
					}
				}

				Temp++;

			}
			else
			{
				Temp = itc;
				Continue = true;
				while ((*Temp++).HasEmptyField() == true && Continue == true)
				{
					if (Temp.operator==(end))
					{
						Continue = false;
					}
				}

				Temp--;


				if ((*Temp).HasEmptyField())
				{
					Temp = itc;
					Continue = true;
					while ((*Temp--).HasEmptyField() == true && Continue == true)
					{
						if (Temp == begin)
						{
							Continue = false;
						}
					}


					Temp++;

				}

			}

			if ((*Temp).HasEmptyField() == false)
			{
				(*itc).Complete_Empty_Field(*Temp);
			}

		}
	}
}

list<int> GetNbDataPerCicrcle(list<double> radius, int NbValue, int nbround)					// Fonction qui calcule le nombre de données par cercle
{
	int i;
	double TotalRadius = 0;
	list<int> NbDataCircle;
	list<int>::iterator itint, itintend;
	list<double>::iterator itc;

	itc = radius.begin();
	itc++;

	for (itc = radius.begin(); itc != radius.end(); itc++)
	{
		TotalRadius += *itc;
	}

	for (itc = radius.begin(); itc != radius.end(); itc++)
	{
		NbDataCircle.push_back((int)((*itc / TotalRadius) * NbValue));
	}

	itint = NbDataCircle.begin();
	itintend = NbDataCircle.end();
	while (NbValue > GetTotal(NbDataCircle, nbround))
	{
		(*itint)++;
		itint++;
		if (itint == itintend)
		{
			itint = NbDataCircle.begin();
		}
	}

	return NbDataCircle;
}

list<int> GetNbDataPerCicrcleOptimised(list<double> radius, int NbMinValuePerCircle, int nbround)	// Fonction qui calcule le nombre de données par cercle avec un nombre minimum de données
{
	int i;
	double TotalRadius = 0;
	list<int> NbDataCircle;
	list<double>::iterator itc, itend;

	itc = radius.begin();
	itc++;
	itend = radius.end();
	itend--;

	for (itc = radius.begin(); itc != radius.end(); itc++)
	{
		TotalRadius += *itc;
	}

	for (i = nbround; i >= 0; i--)
	{
		if (i == nbround)
		{
			NbDataCircle.push_back(NbMinValuePerCircle);
		}
		else
		{
			NbDataCircle.push_back((int)((*itc / *itend) * NbMinValuePerCircle));
			itc++;
		}
	}
	return NbDataCircle;
}

list<double> Getradius(double DistBewteenCircle, int nbround, double MaxRadius, double MaxCylindreRadius)					// Fonction qui calcule les rayons de chaque cercles
{
	list<double> radius;
	int i;
	double TempRadius;


	for (i = 0; i < nbround; i++)
	{
		radius.push_back((MaxRadius - ((i)* (DistBewteenCircle + MaxCylindreRadius))) + (MaxRadius - ((i + 1) * (DistBewteenCircle + MaxCylindreRadius))) / 2);
	}
	return radius;
}

int GetWhichCircle(int DataNumber, list<int> NbDataCircle, int nbround)
{
	int MaxTotal;
	int MinTotal;

	list<int>::iterator itc, ittemp, itend;
	itend = NbDataCircle.end();
	itend--;

	for (itc = NbDataCircle.begin(); itc != NbDataCircle.end(); itc++)
	{
		if (itc.operator==(itend))
		{
			return *itc;
		}
		else
		{
			MaxTotal = *itc;
			MinTotal = 0;

			for (ittemp = NbDataCircle.begin(); ittemp.operator!=(itc); ittemp++)
			{

				MaxTotal += *ittemp;
				MinTotal += *ittemp;

			}


			if (DataNumber >= MinTotal && DataNumber < MaxTotal)
			{
				return *itc;
			}
		}
	}
}


double GetAngleVariation(double Radius, double Distbetweencircle)
{
	double Variation;
	double Circonference;

	Circonference = 2 * Radius * M_PI;
	Variation = (asin(Distbetweencircle / Circonference) * 180 / M_PI);

	return Variation;
}