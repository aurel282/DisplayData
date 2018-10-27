#include <iostream>
#include <list>
#include<string>
#include "General_Function.h"
#include "Data.h"
#include "figures.h"
#include "TxtGestion.h"
#include <cmath>
#include <ctype.h>

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define BUFSIZE 512
#define M_PI 3.14159265358979323846										// Définition du nombre pi

GLuint selectBuf[BUFSIZE];

											// Variable utile au dessin

int W = 1800, H = 1000;

						
int MaxYCircle = 100;								// Variable qui definit la hauteur max
const int NbRound = 5;								// Variable qui définit le nombre de tour
int Precision = 5;									// Variable qui définit la précision pour la génération 3
float Cylindersize = 10;							// Variable qui définit la longueur du cylindre pour la génération 1
float CylinderTopRadius = 10;						// Variable qui définit le rayon supérieur du cylindre pour génération 1-2-3
float CylinderBaseRadius = 10;						// Variable qui définit le rayon inférieur du cylindre pour génération 1-2-3
float CylinderMaxRadius = 10;						// Variable qui définit le rayon Max du cylindre pour génération 1-2-3-4
double DistBetweenCircle = 5;						// Variable qui définit la distance minimale entre les surfaces de 2 cylindres pour génération 1-2-3-4
double ExtRadius = 200;								// Variable qui definit le rayon exterieur max
double IntRadius = 0;								// Variable qui definit le rayon interieur max
double Recover = 0.1;								// Variable qui définit le pourcentage qui sera recouvert entre cylindre pour la généaration 3-4
double SecuritySize = 5;							// Variable qui sert de sécurité lors de la vérif de la taille du cylindre pour la génération 2-3-4

list<point> Act_Pos;						// Liste des points centres de génération de cylindres

											// Variable d'affichage

double ViewRotateAngleX = -90;								// Angle de Rotation de la vue selon l'axe X
double ViewRotateAngleY = 0;								// Angle de Rotation de la vue selon l'axe Y
double ViewRotateAngleZ = 0;								// Angle de Rotation de la vue selon l'axe Z

float LightPosX = 1;										// Position de la lumiere selon X
float LightPosY = 1;										// Position de la lumiere selon Y
float LightPosZ = 0;										// Position de la lumiere selon Z


double ScaleRef = 0.005;										// Echelle de la fénétre
double MoveSpeed = 4;											// Vitesse mouvement


using namespace std;

								// Mise en place des fonctions d'affichage

void
drawfirststep(void)						// Fonction dessin de la première génération
{
	list<point>::iterator itc;	
	
	
	GLUquadricObj *quadratic;
	quadratic = gluNewQuadric();

	int NbVal = GetNbValue(Act_Pos);
	int ValPerRound = NbVal / NbRound;
	double DegreePerVal = (360.0 / (float)ValPerRound);

	int i = 0;


	for (itc = Act_Pos.begin(); itc != Act_Pos.end(); itc++)											// Dessin de tous les cylindres de la génération première étape
	{
		glTranslatef((*itc).GetX(), (*itc).GetY() - 2, (*itc).GetZ() -1);				// Mise en place du décalage du centre du cylindre
		glRotatef( -(i *DegreePerVal), 0.0f, 1.0f, 0.0f);											// Rotation du cylindre
		gluCylinder(quadratic, CylinderBaseRadius, CylinderTopRadius, Cylindersize, 32, 32);
		glRotatef((i *DegreePerVal), 0.0f, 1.0f, 0.0f);										// Annulation des décalage du cylindre pour repartir en base nulle
		glTranslatef( -(*itc).GetX() , -(*itc).GetY() + 2, -(*itc).GetZ() + 1);
		i++;
	}
}
void
drawSecondStep(void)						// Fonction dessin pour les génération à partir de 2
{
	list<point>::iterator itc,itcmore, itend;																		

	GLUquadricObj *quadratic;
	quadratic = gluNewQuadric();

	int NbVal = GetNbValue(Act_Pos);
	int ValPerRound = NbVal / NbRound;
	double DegreePerVal = (360.0 / (float)ValPerRound);
	double lenght;
	double radius, anglevariation, anglevariationperval;

	int i = 0;
	
	itend = Act_Pos.end();
	itend--;
	itcmore = Act_Pos.begin();
	itcmore++;

	for (itc = Act_Pos.begin(); itc != Act_Pos.end(); itc++)											// Dessin de tous les cylindres de la génération première étape
	{
		if (itc.operator==(itend))
			{
				glTranslatef((*itc).GetX(), (*itc).GetY(), (*itc).GetZ());				// Mise en place du décalage du centre du cylindre
				glRotatef(-(i *DegreePerVal), 0.0f, 1.0f, 0.0f);													// Rotation du cylindre
				gluCylinder(quadratic, CylinderBaseRadius, CylinderTopRadius, lenght, 32, 32);
				glRotatef((i *DegreePerVal), 0.0f, 1.0f, 0.0f);										// Annulation des décalage du cylindre pour repartir en base nulle
				glTranslatef(-(*itc).GetX(), -(*itc).GetY(), -(*itc).GetZ());
				i++;
			}
		else
		{
			lenght = DistXZBetweenTwoPoints(*itc, *itcmore) * (double)(1 + Recover);										// Obtention de la longueur entre deux cylindre + Calcul longueur du cylindre à afficher
			if (lenght > SecuritySize)																			// Correction en cas d'erreur de longueur
			{
				lenght = Cylindersize;
			}

																												// Calcul de la variation d'angle du au fait que le rayon du cercle diminue
			radius = sqrt((*itc).GetX() * (*itc).GetX() + (*itc).GetZ() *(*itc).GetZ());
			anglevariation = GetAngleVariation(radius, (DistBetweenCircle + CylinderMaxRadius * 2));
			anglevariationperval = (anglevariation / (float)ValPerRound);

			glTranslatef((*itc).GetX(), (*itc).GetY(), (*itc).GetZ());				// Mise en place du décalage du centre du cylindre
			glRotatef(-(i * DegreePerVal) - ( anglevariationperval * (float)(i%ValPerRound)) , 0.0f, 1.0f, 0.0f);													// Rotation du cylindre
			gluCylinder(quadratic, CylinderBaseRadius, CylinderTopRadius, lenght, 32, 32);
			glRotatef((i *DegreePerVal) + (anglevariationperval * (i%ValPerRound)), 0.0f, 1.0f, 0.0f);										// Annulation des décalage du cylindre pour repartir en base nulle
			glTranslatef(-(*itc).GetX(), -(*itc).GetY(), -(*itc).GetZ());
			i++;

			itcmore++;
			
		}
	}
}
void
drawThirdStep(void)						// Fonction dessin pour les génération à partir de 4
{
	list<point>::iterator itc, itcmore, itend;

	GLUquadricObj *quadratic;
	quadratic = gluNewQuadric();

	int NbVal = GetNbValue(Act_Pos);
	int ValPerRound = NbVal / NbRound;
	double DegreePerVal = (360.0 / (float)ValPerRound);
	double lenght;
	double radius, anglevariation, anglevariationperval;
	double angle, HeightAngle, HeightAngleRadd, angleRad;
	double HeightDifference;


	int i = 0;

	itend = Act_Pos.end();
	itend--;
	itcmore = Act_Pos.begin();
	itcmore++;

	for (itc = Act_Pos.begin(); itc != Act_Pos.end(); itc++)											// Dessin de tous les cylindres de la génération première étape
	{
		if (itc.operator==(itend))
		{
			glTranslatef((*itc).GetX(), (*itc).GetY(), (*itc).GetZ());				// Mise en place du décalage du centre du cylindre
			glRotatef(-(i *DegreePerVal) + 180, 0.0f, 1.0f, 0.0f);													// Rotation du cylindre
			gluCylinder(quadratic, CylinderBaseRadius, CylinderTopRadius, lenght, 32, 32);
			glRotatef(-180.0f + (i *DegreePerVal), 0.0f, 1.0f, 0.0f);										// Annulation des décalage du cylindre pour repartir en base nulle
			glTranslatef(-(*itc).GetX(), -(*itc).GetY(), -(*itc).GetZ());
			i++;
		}
		else
		{
			lenght = DistXZBetweenTwoPoints(*itc, *itcmore) * (double)(1 + Recover);										// Obtention de la longueur entre deux cylindre + Calcul longueur du cylindre à afficher
			if (lenght > SecuritySize)																			// Correction en cas d'erreur de longueur
			{
				lenght = Cylindersize;
			}

			// Calcul de la variation d'angle du au fait que le rayon du cercle diminue
			radius = sqrt((*itc).GetX() * (*itc).GetX() + (*itc).GetZ() *(*itc).GetZ());
			anglevariation = GetAngleVariation(radius, (DistBetweenCircle + CylinderMaxRadius * 2));
			anglevariationperval = (anglevariation / (float)ValPerRound);

			angle = (-(i * DegreePerVal) - (anglevariationperval * (float)(i%ValPerRound)));				// Calcul de l'angle à modifier selon l'axe Y
			angleRad = ((angle / 180) * M_PI);																	// Transformation de cet angle en Radian
			HeightDifference = (*itcmore).GetY() - (*itc).GetY();
			HeightAngleRadd = atan(HeightDifference / (DistXZBetweenTwoPoints(*itc, *itcmore)));
			HeightAngle = HeightAngleRadd / M_PI * 180;

			glTranslatef((*itc).GetX(), (*itc).GetY(), (*itc).GetZ());				// Mise en place du décalage du centre du cylindre
			glRotatef(angle, 0.0f, 1.0f, 0.0f);													// Rotation du cylindre selon l'axe Y
			glRotatef(-HeightAngle, cos(angleRad), 0.0f, sin(angleRad));													// En fonction de la différence de hauteur des deux points;
			gluCylinder(quadratic, CylinderBaseRadius, CylinderTopRadius, lenght, 32, 32);
			glRotatef(HeightAngle, cos(angleRad), 0.0f, sin(angleRad));
			glRotatef(-angle, 0.0f, 1.0f, 0.0f);										// Annulation des décalage du cylindre pour repartir en base nulle
			glTranslatef(-(*itc).GetX(), -(*itc).GetY(), -(*itc).GetZ());
			i++;

			itcmore++;

		}
	}
}
void
myortho(void)
{
	if (W <= H)
		glOrtho(-2.5, 2.5, -2.5 * (GLfloat)H / (GLfloat)W,
			2.5 * (GLfloat)H / (GLfloat)W, -10.0, 10.0);
	else
		glOrtho(-2.5 * (GLfloat)W / (GLfloat)H,
			2.5 * (GLfloat)W / (GLfloat)H, -2.5, 2.5, -10.0, 10.0);
}
void
displayfirststep(void)															// Fonction d'affichage de la première génération
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawfirststep();

	glPushAttrib(GL_ENABLE_BIT);
	glDisable(GL_DEPTH_TEST);
		

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 3000, 0, 3000);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopAttrib();

	glutSwapBuffers();
}
void
displaySecondStep(void)															// Fonction d'affichage des génération à partir de 2
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawSecondStep();

	glPushAttrib(GL_ENABLE_BIT);
	glDisable(GL_DEPTH_TEST);



	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 3000, 0, 3000);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopAttrib();

	glutSwapBuffers();
}
void
displayThirdStep(void)															// Fonction d'affichage des génération à partir de 4
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawThirdStep();

	glPushAttrib(GL_ENABLE_BIT);
	glDisable(GL_DEPTH_TEST);



	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 3000, 0, 3000);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopAttrib();

	glutSwapBuffers();
}
void
myReshape(int w, int h)
{
	W = w;
	H = h;
	glViewport(0, 0, W, H);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	myortho();
	glMatrixMode(GL_MODELVIEW);
}
void
myinit(void)
{
	GLfloat light_ambient[] =
	{ 0.2, 0.2, 0.2, 1.0 };
	GLfloat light_diffuse[] =
	{ 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] =
	{ 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_position[] =
	{ 1.0, 1.0, 1.0, 0.0 };

	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position);

	glEnable(GL_LIGHT1);
	glDepthFunc(GL_LESS);
	glEnable(GL_LIGHTING);

																				// Création source de lumière																		
	GLfloat LightPos[] = { 0, LightPosX, LightPosY, LightPosZ };
	glLightfv(GL_LIGHT0, GL_POSITION, LightPos);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glDisable(GL_LINE_SMOOTH);

	glSelectBuffer(BUFSIZE, selectBuf);

}
void processSpecialKeys(int key, int xx, int yy) {

	double RadY;
	switch (key) 
	{
	case GLUT_KEY_LEFT:
		ViewRotateAngleY -= MoveSpeed;
		glRotatef(-MoveSpeed, 0.0, 1.0, 0.0);
		break;
	case GLUT_KEY_RIGHT:
		ViewRotateAngleY += MoveSpeed;
		glRotatef(MoveSpeed, 0.0, 1.0, 0.0);
		break;
	case GLUT_KEY_UP:
		RadY = ViewRotateAngleY / 180 * M_PI;
		RadY += (M_PI / 2);
		ViewRotateAngleZ = ViewRotateAngleZ - MoveSpeed * cos(RadY);
		ViewRotateAngleX = ViewRotateAngleX + MoveSpeed * sin(RadY);
		glRotatef(-MoveSpeed, -sin(RadY), 0.0, cos(RadY));
		break;
	case GLUT_KEY_DOWN:
		RadY = ViewRotateAngleY / 180 * M_PI;
		RadY += (M_PI / 2);
		ViewRotateAngleZ = ViewRotateAngleZ + MoveSpeed * cos(RadY);
		ViewRotateAngleX = ViewRotateAngleX - MoveSpeed * sin(RadY);
		glRotatef(MoveSpeed, - sin(RadY), 0.0, cos(RadY));
		break;
	}
	glutPostRedisplay();
}


												// Fonction Main
int main(int argc, char **argv)
{
	

	list<Data> Act_Data;
	list<ExportPointValue> DatatoExport;

	bool again = true;
	bool first_step = true;

	int NbValue;

	string entry;

	while (again)
	{
		int WTD = 0;
		first_step = true;

		cout << "=====================================================================================================================" << endl;
		cout << "1 -> Importer et afficher CSV" << endl;
		cout << "2 -> Importer,traiter et afficher CSV" << endl;
		cout << "3 -> Importer,traiter et premiere etape de la generation 3D"  << endl;
		cout << "4 -> Importer,traiter et deuxieme etape de la generation 3D" << endl;
		cout << "5 -> Importer,traiter et Troisieme etape de la generation 3D" << endl;
		cout << "6 -> Importer,traiter et Quatrieme etape de la generation 3D" << endl;
		cout << "7 -> Importer,traiter et premiere etape de la generation 3D + TxtOpenScad" << endl;
		cout << "8 -> Importer,traiter et deuxieme etape de la generation 3D + TxtOpenScad" << endl;
		cout << "9 -> Importer,traiter et Troisieme etape de la generation 3D + TxtOpenScad" << endl;
		cout << "10 -> Importer,traiter et Quatrieme etape de la generation 3D + TxtOpenScad" << endl;
		cout << "99 -> Quitter" << endl;
		cout << "=====================================================================================================================" << endl;



		while (WTD > 99 || WTD < 1)
		{
			if (first_step)
			{
				cout << "Que voulez vous faire?" << endl;
			}
			else
			{
				cout << "=====================================================================================================================" << endl;
				cout << "=======================================CE QUE VOUS AVEZ ENTRE EST INCORRECT==========================================" << endl;
				cout << "=====================================================================================================================" << endl;
				cout << "=====================================================================================================================" << endl;
				cout << "1 -> Importer et afficher CSV" << endl;
				cout << "2 -> Importer,traiter et afficher CSV" << endl;
				cout << "3 -> Importer,traiter et premiere etape de la generation 3D" << endl;
				cout << "4 -> Importer,traiter et deuxieme etape de la generation 3D" << endl;
				cout << "5 -> Importer,traiter et Troisieme etape de la generation 3D" << endl;
				cout << "6 -> Importer,traiter et Quatrieme etape de la generation 3D" << endl;
				cout << "7 -> Importer,traiter et premiere etape de la generation 3D + TxtOpenScad" << endl;
				cout << "8 -> Importer,traiter et deuxieme etape de la generation 3D + TxtOpenScad" << endl;
				cout << "9 -> Importer,traiter et Troisieme etape de la generation 3D + TxtOpenScad" << endl;
				cout << "10 -> Importer,traiter et Quatrieme etape de la generation 3D + TxtOpenScad" << endl;
				cout << "99 -> Quitter" << endl;
				cout << "=====================================================================================================================" << endl;
				cout << "Que voulez vous faire?" << endl;
			}

			getline(cin, entry);
			bool isNumber = true;
			for (string::const_iterator k = entry.begin(); k != entry.end(); ++k)
			{
				if (!isdigit(*k))
				{
					isNumber = false;
				}
			}
			if (isNumber)
				WTD = stoi(entry);
			else
				WTD = 0;

			first_step = false;
		}
		

		if (WTD == 1)
		{
			Clear_Lst(Act_Data);
			Read_CSV(Act_Data);
			Show_Lst(Act_Data);
		}
		else if (WTD == 2)
		{
			Clear_Lst(Act_Data);
			Read_CSV(Act_Data);
			Complete_Data(Act_Data);
			Show_Lst(Act_Data);	
		}
		else if (WTD == 3)
		{
			
			double MinValue;
			double MaxValue;

			
											// Lecture et traitement des données
			Clear_Lst(Act_Data);
			Read_CSV(Act_Data);
			Complete_Data(Act_Data);


											// Bases pour la création graphique  -> Traitement des valeurs
			
			NbValue = GetNbValue(Act_Data);
			MinValue = GetMinValue(Act_Data);
			MaxValue = GetMaxValue(Act_Data);

			Act_Pos = GetCoordCircle(NbRound, NbValue, ExtRadius, IntRadius, Cylindersize , DistBetweenCircle);
			GetYCoordCircle(Act_Data, Act_Pos, MinValue, MaxValue, MaxYCircle);

											// Dessin Graphique

			glutInit(&argc, argv);
			glutInitWindowSize(W, H);
			glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
			glutCreateWindow(argv[0]);
			myinit();
			glutDisplayFunc(displayfirststep);
			glScalef(ScaleRef, ScaleRef, ScaleRef);																			// Choix de la vue
			glRotatef(ViewRotateAngleX, 1.0, 0.0, 0.0);
			glRotatef(ViewRotateAngleY, 0.0, 1.0, 0.0);
			glRotatef(ViewRotateAngleZ, 0.0, 0.0, 1.0);
			glutSpecialFunc(processSpecialKeys);
			glEnable(GL_DEPTH_TEST);
			glutMainLoop();
		}
		else if (WTD == 4)
		{
			double MinValue;
			double MaxValue;


			// Lecture et traitement des données
			Clear_Lst(Act_Data);
			Read_CSV(Act_Data);
			Complete_Data(Act_Data);


			// Bases pour la création graphique  -> Traitement des valeurs

			NbValue = GetNbValue(Act_Data);
			MinValue = GetMinValue(Act_Data);
			MaxValue = GetMaxValue(Act_Data);

			Act_Pos = GetCoordCircle(NbRound, NbValue, ExtRadius, IntRadius, Cylindersize, DistBetweenCircle);
			GetYCoordCircle(Act_Data, Act_Pos, MinValue, MaxValue, MaxYCircle);

			// Dessin Graphique

			glutInit(&argc, argv);
			glutInitWindowSize(W, H);
			glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
			glutCreateWindow(argv[0]);
			myinit();
			glutDisplayFunc(displaySecondStep);
			glScalef(ScaleRef, ScaleRef, ScaleRef);																			// Choix de la vue
			glRotatef(ViewRotateAngleX, 1.0, 0.0, 0.0);
			glRotatef(ViewRotateAngleY, 0.0, 1.0, 0.0);
			glRotatef(ViewRotateAngleZ, 0.0, 0.0, 1.0);
			glutSpecialFunc(processSpecialKeys);
			glutMainLoop();
		}
		else if (WTD == 5)
		{
			double MinValue;
			double MaxValue;
			list<double> PreciseValues;

			// Lecture et traitement des données
			Clear_Lst(Act_Data);
			Read_CSV(Act_Data);
			Complete_Data(Act_Data);


			// Bases pour la création graphique  -> Traitement des valeurs

			NbValue = GetNbValue(Act_Data);
			MinValue = GetMinValue(Act_Data);
			MaxValue = GetMaxValue(Act_Data);

			NbValue = (NbValue - 1) * Precision;																		// Le nombre de valeur est multiplié par la précision sauf pour la dernière -> -1
																														// Plus d'info voir code de GetMorePreciseValues

			Act_Pos = GetCoordCircle(NbRound, NbValue, ExtRadius, IntRadius, CylinderMaxRadius, DistBetweenCircle);
			PreciseValues = GetMorePreciseValues(Act_Data, Precision);
			GetPreciseYCoordCircle(PreciseValues, Act_Pos, MinValue, MaxValue, MaxYCircle);


			// Dessin Graphique

			glutInit(&argc, argv);
			glutInitWindowSize(W, H);
			glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
			glutCreateWindow(argv[0]);
			myinit();
			glutDisplayFunc(displaySecondStep);
			glScalef(ScaleRef, ScaleRef, ScaleRef);																			// Choix de la vue
			glRotatef(ViewRotateAngleX, 1.0, 0.0, 0.0);
			glRotatef(ViewRotateAngleY, 0.0, 1.0, 0.0);
			glRotatef(ViewRotateAngleZ, 0.0, 0.0, 1.0);
			glutSpecialFunc(processSpecialKeys);
			glutMainLoop();
		}
		else if (WTD == 6)
		{
			double MinValue;
			double MaxValue;
			list<double> PreciseValues;

			// Lecture et traitement des données
			Clear_Lst(Act_Data);
			Read_CSV(Act_Data);
			Complete_Data(Act_Data);


			// Bases pour la création graphique  -> Traitement des valeurs

			NbValue = GetNbValue(Act_Data);
			MinValue = GetMinValue(Act_Data);
			MaxValue = GetMaxValue(Act_Data);

			NbValue = (NbValue - 1) * Precision;																		// Le nombre de valeur est multiplié par la précision sauf pour la dernière -> -1
																														// Plus d'info voir code de GetMorePreciseValues

			Act_Pos = GetCoordCircle(NbRound, NbValue, ExtRadius, IntRadius, CylinderMaxRadius, DistBetweenCircle);
			PreciseValues = GetMorePreciseValues(Act_Data, Precision);
			GetPreciseYCoordCircle(PreciseValues, Act_Pos, MinValue, MaxValue, MaxYCircle);


			// Dessin Graphique

			glutInit(&argc, argv);
			glutInitWindowSize(W, H);
			glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
			glutCreateWindow(argv[0]);
			myinit();
			glutDisplayFunc(displayThirdStep);
			glScalef(ScaleRef, ScaleRef, ScaleRef);																			// Choix de la vue
			glRotatef(ViewRotateAngleX, 1.0, 0.0, 0.0);
			glRotatef(ViewRotateAngleY, 0.0, 1.0, 0.0);
			glRotatef(ViewRotateAngleZ, 0.0, 0.0, 1.0);
			glutSpecialFunc(processSpecialKeys);
			glutMainLoop();
		}
		else if (WTD == 7)
		{

			double MinValue;
			double MaxValue;


			// Lecture et traitement des données
			Clear_Lst(Act_Data);
			Read_CSV(Act_Data);
			Complete_Data(Act_Data);


			// Bases pour la création graphique  -> Traitement des valeurs

			NbValue = GetNbValue(Act_Data);
			MinValue = GetMinValue(Act_Data);
			MaxValue = GetMaxValue(Act_Data);

			Act_Pos = GetCoordCircle(NbRound, NbValue, ExtRadius, IntRadius, Cylindersize, DistBetweenCircle);
			GetYCoordCircle(Act_Data, Act_Pos, MinValue, MaxValue, MaxYCircle);

			// Export Fichier .txt

			ofstream ActFile;
			ActFile = TxtCreation();
			DatatoExport = ComputeDatatoExport(Act_Pos, NbRound, Recover, SecuritySize, DistBetweenCircle, CylinderMaxRadius, CylinderMaxRadius, Cylindersize);
			TxtCreate(DatatoExport, ActFile);
			ActFile.close();

			// Dessin Graphique

			glutInit(&argc, argv);
			glutInitWindowSize(W, H);
			glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
			glutCreateWindow(argv[0]);
			myinit();
			glutDisplayFunc(displayfirststep);
			glScalef(ScaleRef, ScaleRef, ScaleRef);																			// Choix de la vue
			glRotatef(ViewRotateAngleX, 1.0, 0.0, 0.0);
			glRotatef(ViewRotateAngleY, 0.0, 1.0, 0.0);
			glRotatef(ViewRotateAngleZ, 0.0, 0.0, 1.0);
			glutSpecialFunc(processSpecialKeys);
			glutMainLoop();
		}
		else if (WTD == 8)
		{
			double MinValue;
			double MaxValue;


			// Lecture et traitement des données
			Clear_Lst(Act_Data);
			Read_CSV(Act_Data);
			Complete_Data(Act_Data);


			// Bases pour la création graphique  -> Traitement des valeurs

			NbValue = GetNbValue(Act_Data);
			MinValue = GetMinValue(Act_Data);
			MaxValue = GetMaxValue(Act_Data);

			Act_Pos = GetCoordCircle(NbRound, NbValue, ExtRadius, IntRadius, Cylindersize, DistBetweenCircle);
			GetYCoordCircle(Act_Data, Act_Pos, MinValue, MaxValue, MaxYCircle);

			// Export Fichier .txt

			ofstream ActFile;
			ActFile = TxtCreation();
			DatatoExport = ComputeDatatoExport(Act_Pos, NbRound, Recover, SecuritySize, DistBetweenCircle, CylinderMaxRadius, CylinderMaxRadius, Cylindersize);
			TxtCreate(DatatoExport, ActFile);
			ActFile.close();

			// Dessin Graphique

			glutInit(&argc, argv);
			glutInitWindowSize(W, H);
			glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
			glutCreateWindow(argv[0]);
			myinit();
			glutDisplayFunc(displaySecondStep);
			glScalef(ScaleRef, ScaleRef, ScaleRef);																			// Choix de la vue
			glRotatef(ViewRotateAngleX, 1.0, 0.0, 0.0);
			glRotatef(ViewRotateAngleY, 0.0, 1.0, 0.0);
			glRotatef(ViewRotateAngleZ, 0.0, 0.0, 1.0);
			glutSpecialFunc(processSpecialKeys);
			glutMainLoop();
		}
		else if (WTD == 9)
		{
			double MinValue;
			double MaxValue;
			list<double> PreciseValues;

			// Lecture et traitement des données
			Clear_Lst(Act_Data);
			Read_CSV(Act_Data);
			Complete_Data(Act_Data);


			// Bases pour la création graphique  -> Traitement des valeurs

			NbValue = GetNbValue(Act_Data);
			MinValue = GetMinValue(Act_Data);
			MaxValue = GetMaxValue(Act_Data);

			NbValue = (NbValue - 1) * Precision;																		// Le nombre de valeur est multiplié par la précision sauf pour la dernière -> -1
																														// Plus d'info voir code de GetMorePreciseValues

			Act_Pos = GetCoordCircle(NbRound, NbValue, ExtRadius, IntRadius, CylinderMaxRadius, DistBetweenCircle);
			PreciseValues = GetMorePreciseValues(Act_Data, Precision);
			GetPreciseYCoordCircle(PreciseValues, Act_Pos, MinValue, MaxValue, MaxYCircle);

			// Export Fichier .txt

			ofstream ActFile;
			ActFile = TxtCreation();
			DatatoExport = ComputeDatatoExport(Act_Pos, NbRound, Recover, SecuritySize, DistBetweenCircle, CylinderMaxRadius, CylinderMaxRadius, Cylindersize);
			TxtCreate(DatatoExport, ActFile);
			ActFile.close();

			// Dessin Graphique

			glutInit(&argc, argv);
			glutInitWindowSize(W, H);
			glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
			glutCreateWindow(argv[0]);
			myinit();
			glutDisplayFunc(displaySecondStep);
			glScalef(ScaleRef, ScaleRef, ScaleRef);																			// Choix de la vue
			glRotatef(ViewRotateAngleX, 1.0, 0.0, 0.0);
			glRotatef(ViewRotateAngleY, 0.0, 1.0, 0.0);
			glRotatef(ViewRotateAngleZ, 0.0, 0.0, 1.0);
			glutSpecialFunc(processSpecialKeys);
			glutMainLoop();
		}
		else if (WTD == 10)
		{
			double MinValue;
			double MaxValue;
			list<double> PreciseValues;

			// Lecture et traitement des données
			Clear_Lst(Act_Data);
			Read_CSV(Act_Data);
			Complete_Data(Act_Data);


			// Bases pour la création graphique  -> Traitement des valeurs

			NbValue = GetNbValue(Act_Data);
			MinValue = GetMinValue(Act_Data);
			MaxValue = GetMaxValue(Act_Data);

			NbValue = (NbValue - 1) * Precision;																		// Le nombre de valeur est multiplié par la précision sauf pour la dernière -> -1
																														// Plus d'info voir code de GetMorePreciseValues

			Act_Pos = GetCoordCircle(NbRound, NbValue, ExtRadius, IntRadius, CylinderMaxRadius, DistBetweenCircle);
			PreciseValues = GetMorePreciseValues(Act_Data, Precision);
			GetPreciseYCoordCircle(PreciseValues, Act_Pos, MinValue, MaxValue, MaxYCircle);

			// Export Fichier .txt

			ofstream ActFile;
			ActFile = TxtCreation();
			DatatoExport = ComputeDatatoExport(Act_Pos, NbRound, Recover, SecuritySize, DistBetweenCircle, CylinderMaxRadius, CylinderMaxRadius, Cylindersize);
			TxtCreate(DatatoExport, ActFile);
			ActFile.close();

			// Dessin Graphique

			glutInit(&argc, argv);
			glutInitWindowSize(W, H);
			glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
			glutCreateWindow(argv[0]);
			myinit();
			glutDisplayFunc(displayThirdStep);
			glScalef(ScaleRef, ScaleRef, ScaleRef);																			// Choix de la vue
			glRotatef(ViewRotateAngleX, 1.0, 0.0, 0.0);
			glRotatef(ViewRotateAngleY, 0.0, 1.0, 0.0);
			glRotatef(ViewRotateAngleZ, 0.0, 0.0, 1.0);
			glutSpecialFunc(processSpecialKeys);
			glutMainLoop();
		}
		else if (WTD == 99)
		{
			again = Check_Again();
		}
		else
		{
			cout << "=====================================================================================================================" << endl;
			cout << "=======================================CE QUE VOUS AVEZ ENTRE EST INCORRECT==========================================" << endl;
			cout << "=====================================================================================================================" << endl;
		}
	}

	return 0;
}


