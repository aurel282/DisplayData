#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "figures.h"

using namespace std;

ofstream TxtCreation();													// Création d'un TXT 
void TxtCreate(list<ExportPointValue> Act_Data, ofstream &textFile);	// On modifie le txt pour y mettre les données voulues