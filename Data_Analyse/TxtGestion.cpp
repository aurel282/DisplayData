#include "TxtGestion.h"


const double PI = 3.14159265358979323846;

ofstream  TxtCreation()
{
	string path("C:\\temp\\OpenScad.scad");
	ofstream o(path);
	o << "echo(version=version());" << endl << endl << endl << endl;
	return o;
}

void TxtCreate(list<ExportPointValue> Act_Data, ofstream &textFile)
{
	list<ExportPointValue>::iterator itc;
	for (itc = Act_Data.begin(); itc != Act_Data.end(); itc++)											// Dessin de tous les cylindres de la génération première étape
	{
		textFile << "translate([" << (*itc).GetX() << "," << (*itc).GetY() + (*itc).GetRadius() / 2 << "," << (*itc).GetZ()  << "])" << endl;
		textFile << "\t" << "rotate([" << (*itc).GetRotX() << "," << (*itc).GetRotY() << "," << (*itc).GetRotZ() << "])" << endl;
		textFile << "\t" << "linear_extrude(height = " << (*itc).GetHeight() << ")" << endl;
		textFile << "\t" << "circle(" << (*itc).GetRadius() / 2 << ");" << endl;
		textFile << endl;

		double ARot = (*itc).GetRotY() / 180 * PI;

		textFile << "translate([" << (*itc).GetX() - cos(ARot) * (*itc).GetRadius() / 2 << "," << (*itc).GetY() / 4  << "," << (*itc).GetZ() + sin(ARot) * (*itc).GetRadius() / 2 << "])" << endl;
		textFile << "\t" << "rotate([" << (*itc).GetRotX() << "," << (*itc).GetRotY() << "," << (*itc).GetRotZ() << "])" << endl;
		textFile << "\t" << "linear_extrude(height = " << (*itc).GetHeight() << ")" << endl;
		textFile << "\t" << "square([" << (*itc).GetRadius()  << "," << ((*itc).GetY()  / 2)*1.5 + (*itc).GetRadius() / 2  << "]);" << endl;
		textFile << endl;

		/*	
										//  Code OpenSquad Exemple
		translate([5, 0, 15])
			linear_extrude(height = 10)
			rotate([45, 45, 00])
			circle(10);
		*/
	}

}