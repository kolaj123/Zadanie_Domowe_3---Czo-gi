#include <iostream>

#include <GL/freeglut.h>

const double g = 9.81;
bool ruch = true;
bool migotanie = true;
double kolor = 1.0;
double kolor2 = 0.3;
double kolor3 = 0.4;
double kolora = 0.8;
class Czolg
{
public:
	double x;
	double osy;
	double osx;
	double kolor;
	int angle;
	Czolg()
	{
		tank.x = 0.0;
		tank2.x = 0.0;
		tank.osx = 0.6;
		tank.osy = 0.35;
		tank2.osx = 0.9;
		tank2.osy = 0.34;
		angle = 0;
	}
	void DrawRectangle(double width, double height)
	{
		glPushMatrix();
		glColor3d(0.0, 0.5, 0.0);
		glBegin(GL_POLYGON);
		{
			glVertex3d(-width / 2, height / 2, 0);
			glVertex3d(width / 2, height / 2, 0);
			glVertex3d(width / 2, -height / 2, 0);
			glVertex3d(-width / 2, -height / 2, 0);
		}
		glEnd();
		glPopMatrix();
	}
	void draw(double osx, double osy)
	{
		glPushMatrix();
		DrawRectangle(osx,osy);
		glTranslated(0.0,0.25, 0.0);
		DrawRectangle(osx*0.6, osy*0.65);
		glRotated(3+angle, 0.0, 0.0, 1.0);
		glTranslated(0.3, 0.0, 0.0);
		DrawRectangle(osx*0.6, osy*0.3);
		glPopMatrix();
	}
}tank, tank2;
int stopnarad(int x)
{
	double Pi = 3.14;
	double radiany;
	radiany = (Pi*x) / 180;
	return radiany;
}
class Pocisk
{
public:
	double v;
	double t;
	double x, y;
	double Osx;
	double Osy;
	Pocisk()
	{
		pierwszy.x = 0;
		pierwszy.y = 0;
		drugi.x = 0;
		drugi.y = 0;
		pierwszy.t = 0;
		drugi.t = 0;
		pierwszy.Osx = 0.027;
		pierwszy.Osy = 0.027;
		drugi.Osx = 0.027;
		drugi.Osy = 0.027;
		pierwszy.v = 8;
		drugi.v =8;
	}
	void rysuj(double width,double height)
	{
		glPushMatrix();
		glColor3d(0.0, 0.0, 0.0);
		glBegin(GL_POLYGON);
		{
			for (int i = 0; i < 360; i += 10)
			{
				glVertex3d(width*cos(stopnarad(i)), height*sin(stopnarad(i)), 0);
			}
		}
		glEnd();
		glPopMatrix();
	}
	void lot(double a, double b)
	{
		double radiany;
		double Pi = 3.14; 
		radiany = (Pi*tank.angle) / 180;
		glPushMatrix();
		glRotated(tank.angle*0.9, 0.0, 0.0, 1.0);
		glPopMatrix();
		glPushMatrix();
		pierwszy.x = pierwszy.v*pierwszy.t*cos(radiany);
		pierwszy.y = pierwszy.v*pierwszy.t*sin(radiany) - ((g*pierwszy.t*pierwszy.t) / 2);
		glTranslated(pierwszy.x, pierwszy.y, 0);
		rysuj(a, b);
		glPopMatrix();
	}
	void lot2(double a, double b)
	{
		double radiany;
		double Pi = 3.14;
		radiany = (Pi*tank2.angle) / 180;
		glPushMatrix();
		glRotated(tank2.angle, 0.0, 0.0, 1.0);
		glPopMatrix();
		glPushMatrix();
		glTranslated(-0.47, 0.3, 0.);
		drugi.x = drugi.v*drugi.t*cos(radiany);
		drugi.y = drugi.v*drugi.t*sin(radiany) - ((g*drugi.t*drugi.t) / 2);
		glTranslated(drugi.x, drugi.y, 0);
		rysuj(a, b);
		glPopMatrix();
	}
}pierwszy,drugi;
void tlo(double width, double height)
{
	glPushMatrix();
	glColor3d(kolor2, kolor, kolor3);
	glBegin(GL_POLYGON);
	{
		glVertex3d(-width / 2, height / 2, 0);
		glVertex3d(width / 2, height / 2, 0);
		glVertex3d(width / 2, -height / 2, 0);
		glVertex3d(-width / 2, -height / 2, 0);
	}
	glEnd();
	glPopMatrix();
}
void koniec(int value)//  Nie do konca zrobilem zmiane tla jesli uderzy :/ 
{
	if (migotanie == true)
	{
			kolor = 0.0;
			kolor2 = 1.0;
			kolor3 = 0.0;
			migotanie = false;
	}
	else if (migotanie == false)
	{
		migotanie = true;
		for (int i = 0; i <= 20; i++)
		{
			kolor = 1.0;
			kolor2 = 0.3;
			kolor3 = 0.3;
			if (i = 20)
			{
				migotanie = false;
			}
		}
		
	}
	glutTimerFunc(10, koniec, 0);
}
void lotk(int value)
{
	pierwszy.t += 0.01;
	if (pierwszy.x+tank.x+tank2.x > 4.70+tank.x+tank2.x && pierwszy.x+tank.x+tank2.x<5.6+tank.x+tank2.x && pierwszy.y>-0.15 && pierwszy.y < 0.15)
	{
		migotanie = true;
		glutTimerFunc(10, koniec, 0);
		pierwszy.y = 0;
		pierwszy.x = 0;
	}
	glutTimerFunc(1, lotk, 0);
}
void lotk2(int value)
{
	drugi.t += 0.01;
	if (drugi.x + tank.x + tank2.x > -4.70 + tank.x + tank2.x && drugi.x + tank.x + tank2.x<-5.6 + tank.x + tank2.x && drugi.y>-0.1 && drugi.y < 0.1)
	{
		migotanie = true;
		glutTimerFunc(10, koniec, 0);
		drugi.y = 0;
		drugi.x = 0;
	}
	glutTimerFunc(1, lotk2, 0);
}
static void resize(int width, int height)
{
	const float ar = (float)width / (float)height;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
	gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

static void idle(void)
{
	glutPostRedisplay();
};

void glutKeyboardFunc(void *func);
void klawiatura(unsigned char key, int x, int y)
{
	if (ruch == true)
	{
		switch (key)
		{
		case 27:
		{
				   exit(0);
		}
		case 32:
		{
				   if (pierwszy.y > -0.5)
				   {
					   glutTimerFunc(1, lotk, 0);
				   }
				   else
				   {
					   pierwszy.t = 0.0;
					   pierwszy.x = 0;
					   pierwszy.y = 0;
				   }
				   ruch = false;
				   break;
		}
		case 'w':
		{
					tank.angle += 2;
					if (tank.angle > 42)
					{
						tank.angle = 41;
					}
					break;
		}
		case 's':
		{
					tank.angle -= 2;
					if (tank.angle < -5)
					{
						tank.angle = -4;
					}
					break;
		}
		case 'a':
		{
					tank.x -= 0.1;
					break;
		}
		case 'd':
		{
					tank.x += 0.1;
					break;
		}
		}
	}
	if (ruch == false)
	{
		switch (key)
		{
		case 27:
		{
				   exit(0);
		}
		case 'p'://wystrzal pocisku dla 2 playera
		{
					 if (drugi.y > -0.5)
					 {
						 glutTimerFunc(1, lotk2, 0);
					 }
					 else
					 {
						 drugi.t = 0.0;
						 drugi.x = 0;
						 drugi.y = 0;	 
					 }
					 ruch = true;
					 break;
		}
		case 'k':
		{
					tank2.angle += 2;
					if (tank2.angle > 179)
					{
						tank2.angle = 178;
					}
					break;
		}
		case 'i':
		{
					tank2.angle -= 2;
					if (tank2.angle < 136)
					{
						tank2.angle = 135;
					}
					break;
		}
		case 'j':
		{
					tank2.x -= 0.1;
					break;
		}
		case 'l':
		{
					tank2.x += 0.1;
					break;
		}
		}
	}
}
static void display(void)
{
	// clear the scene
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glPushMatrix();
	glTranslated(0.0, -1.5, 0.0);
	tlo(800, 2.9);
	glPopMatrix();
	glTranslated(-2.5, 0.0, 0.0);
	glTranslated(tank.x, 0.0, 0.0);
	tank.draw(tank.osx,tank.osy);
	glPopMatrix();
	glPushMatrix();
	glTranslated(2.75, 0.0, 0.0);
	glTranslated(tank2.x, 0.0, 0.0);
	tank2.draw(tank2.osx,tank2.osy);
	glPopMatrix();
	glPushMatrix();
	glTranslated(-2.4, 0.28, 0.0);
	glTranslated(tank.x, 0.0, 0.0);
	pierwszy.lot(pierwszy.Osx, pierwszy.Osy);
	glPopMatrix();
	glPushMatrix();
	glTranslated(3.1, -0.05, 0.0);
	glTranslated(tank2.x, 0.0, 0.0);
	drugi.lot2(drugi.Osx, drugi.Osy);
	glPopMatrix();
	glutSwapBuffers();
}  

int main(int argc, char *argv[])
{
	tank2.angle = 174;
	
	// it's still possible to use console to print messages
	printf("\t\t\t     Witaj w grze Czolgi!\n\n");
	printf("\t\t\t\t Sterowanie\n\n");
	printf("\t\t\t  ESC - wyjscie z gry\n");
	printf("\t\t\t    Pierwszy Gracz\n\n");
	printf("\t\t\t W - podnoszenie lufy\n");
	printf("\t\t\t S - opadanie lufy\n");
	printf("\t\t\t A - ruch czolgu w lewo\n");
	printf("\t\t\t D - ruch czolgu w prawo\n");
	printf("\t\t\t Spacja - wystrzal pocisku\n\n\n");
	printf("\t\t\t     Drugi Gracz \n\n");
	printf("\t\t\t I - podnoszenie lufy\n");
	printf("\t\t\t K - opadanie lufy\n");
	printf("\t\t\t J - ruch czolgu w lewo\n");
	printf("\t\t\t L - ruch czolgu w prawo\n");
	printf("\t\t\t P - wystrzal pocisku\n\n");
	printf("\t\t\t Ruch odbywa sie naprzemiennie\n");
	printf("\t\t\t Zaczyna gracz z lewej strony");
	// the same can be done with cout / cin

	glutInitWindowSize(800, 600);
	glutInitWindowPosition(40, 40);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

	glutCreateWindow("OpenGLUT Shapes");

	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutKeyboardFunc(*klawiatura);

	// set white as the clear colour
	glClearColor(kolor2, kolor3, kolor, 1);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	glutMainLoop();

	return 0;
}