#include <GL/glut.h>
#include <stdlib.h>
#include <Windows.h>
#include <math.h>
#include <stdio.h>


#define PI 3.14159265
#define numberOfRotationTypes 3


static GLfloat lpos[] = { 0.0, 6.0, 8.0, 1.0 };
static GLfloat black[] = { 0.0, 0.0, 0.0, 1.0 };
static GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
static GLfloat red[] = { 1.0, 0.0, 0.0, 1.0 };
static GLfloat green[] = { 0.0, 1.0, 0.0, 1.0 };
static GLfloat blue[] = { 0.0, 0.0, 1.0, 1.0 };
static GLfloat yellow[] = { 1.0, 1.0, 0.0, 1.0 };
static GLfloat magenta[] = { 1.0, 0.0, 1.0, 1.0 };
static GLfloat cyan[] = { 0.0, 1.0, 1.0, 1.0 };
static GLfloat lightgreen[] = { 0.5, 1.0, 0.5, 1.0 };
static float alpha = 0.0;
static float beta = PI / 6.0;
static float zoom = 25.0;
static bool lightSource = true;

float numberOfTriangles = 1;
static GLdouble cpos[3];

static double fenceHeight = -0.5;
static int angle = 0;
static int angle__IN_RANGE = 0.0;
static double radian__IN_RANGE = 0.0;
static int arrayOfAnglesInRange[181];
static int id = 0;

static int speed = 1;
static int signal = 3;

static GLint window[2];
static int rotationType = 0;
static int duration = 0;

static int TotalNumberOfCabins = 4;
static int input1 = 100;
static int input2 = 3000;

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	/* since back "face" appears in wireframe mode */
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

void writemessage()
{
	printf("HW-3 - Computer Graphics - Professor Suzuki\n");
	printf("Seyedamirhossein Hesamian\n\n");
	printf(" X => x++ <= Move light source in direction of +X\n");
	printf(" Y => y++ <= Move light source in direction of +Y\n");
	printf(" Z => z++ <= Move light source in direction of +Z\n");
	printf("\n");
	printf("^X => x-- <= Move light source in direction of -X\n");
	printf("^Y => y-- <= Move light source in direction of -Y\n");
	printf("^Z => z-- <= Move light source in direction of -Z\n");
	printf("\n");
	printf(" ^ => Move camera up\n");
	printf(" > => Move camera right\n");
	printf(" < => Move camera left\n");
	printf(" down arrow => Move camera down\n");
	printf("\n");
	printf(" r => Increase number of cabins\n");
	printf(" f => Decrease number of cabins\n");
	printf("\n");
	printf("\n");
	printf(" n => Increase angle variable\n");
	printf(" m => Decrease angle variable\n");
	printf("\n");
	printf("\n");
	printf(" e => Increase fence height\n");
	printf(" d => Decrease fence height\n");
	printf("\n");
	printf(" left click of mouse => Increase rotation speed\n");
	printf(" right click of mouse => Decrease rotation speed\n");
	printf("\n");
	printf(" 0 => Toggling light source\n");
	printf("\n");
	printf(" w => Toggle to show wire frame mode\n");
	printf(" You can not move the light source when the light source is off !!!\n");

	printf("\nWarning --> If you increase and decrease the number of cabins (for example setting number of cabins to zero) the camera in cabin (second window) would not then work proporly");
}

void processAngle(){
	angle__IN_RANGE = arrayOfAnglesInRange[abs(angle) % 181];
}

void setRadian_IN_RANGE(){
	radian__IN_RANGE = ((float)angle__IN_RANGE / 180) * PI;
}

void fillArray(){
	int j = -45;
	for (int i = 0; i < 181; i++)
	{
		if (i < 90)
			arrayOfAnglesInRange[i] = j++;
		else
			arrayOfAnglesInRange[i] = j--;
	}

	//for (int i = 0; i < 182; i++)
	//{
	//	printf("%d\n", arrayOfAnglesInRange[i]);
	//}
}

void keepTrackOfID(){
	int tempAngle = angle;

	for (int i = 0; i < TotalNumberOfCabins; i++)
	{
		if (id % TotalNumberOfCabins == i)
			angle = angle + (i*30);
	}

	processAngle();
	setRadian_IN_RANGE();
	angle = tempAngle;
}


void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 0.01, 50.0);
	glMatrixMode(GL_MODELVIEW);
}

void DrawSticksArroundYard(){
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, red);
	glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, black);
	GLUquadricObj *quadObj;

	// Right-Line
	glPushMatrix();
	glTranslatef(6.8, 1.0 + fenceHeight, -7.0);
	quadObj = gluNewQuadric();
	gluCylinder(quadObj, 0.1, 0.1, 14.0, 10, 10);
	glPopMatrix();

	// Left-Line
	glPushMatrix();
	glTranslatef(-6.8, 1.0 + fenceHeight, -7.0);
	quadObj = gluNewQuadric();
	gluCylinder(quadObj, 0.1, 0.1, 14.0, 10, 10);
	glPopMatrix();

	// Back-Line
	glPushMatrix();
	glTranslatef(-6.8, 1.0 + fenceHeight, -7.0);
	glRotatef(90, 0, 1, 0);
	quadObj = gluNewQuadric();
	gluCylinder(quadObj, 0.1, 0.1, 13.7, 10, 10);
	glRotatef(-90, 0, 1, 0);
	glPopMatrix();

	// Front-Line
	glPushMatrix();
	glTranslatef(6.8, 1.0 + fenceHeight, 7.0);
	glRotatef(-90, 0, 1, 0);
	quadObj = gluNewQuadric();
	gluCylinder(quadObj, 0.1, 0.1, 13.7, 10, 10);
	glRotatef(90, 0, 1, 0);
	glPopMatrix();

	// Pin-Front-Right
	glPushMatrix();
	glTranslatef(6.8, 0, 7.0);
	glRotatef(-90, 1, 0, 0);
	quadObj = gluNewQuadric();
	gluCylinder(quadObj, 0.2, 0.1, 1.3 + fenceHeight, 10, 10);
	glRotatef(90, 1, 0, 0);
	glPopMatrix();

	// Pin-Front-Left
	glPushMatrix();
	glTranslatef(-6.8, 0, 7.0);
	glRotatef(-90, 1, 0, 0);
	quadObj = gluNewQuadric();
	gluCylinder(quadObj, 0.2, 0.1, 1.3 + fenceHeight, 10, 10);
	glRotatef(90, 1, 0, 0);
	glPopMatrix();

	// Pin-Back-Left
	glPushMatrix();
	glTranslatef(-6.8, 0, -7.0);
	glRotatef(-90, 1, 0, 0);
	quadObj = gluNewQuadric();
	gluCylinder(quadObj, 0.2, 0.1, 1.3 + fenceHeight, 10, 10);
	glRotatef(90, 1, 0, 0);
	glPopMatrix();

	// Pin-Back-Right
	glPushMatrix();
	glTranslatef(6.8, 0, -7.0);
	glRotatef(-90, 1, 0, 0);
	quadObj = gluNewQuadric();
	gluCylinder(quadObj, 0.2, 0.1, 1.3 + fenceHeight, 10, 10);
	glRotatef(90, 1, 0, 0);
	glPopMatrix();

	// Pin-Back-Center
	glPushMatrix();
	glTranslatef(0, 0, -7.0);
	glRotatef(-90, 1, 0, 0);
	quadObj = gluNewQuadric();
	gluCylinder(quadObj, 0.2, 0.1, 1.3 + fenceHeight, 10, 10);
	glRotatef(90, 1, 0, 0);
	glPopMatrix();

	// Pin-Front-Center
	glPushMatrix();
	glTranslatef(0, 0, 7.0);
	glRotatef(-90, 1, 0, 0);
	quadObj = gluNewQuadric();
	gluCylinder(quadObj, 0.2, 0.1, 1.3 + fenceHeight, 10, 10);
	glRotatef(90, 1, 0, 0);
	glPopMatrix();

	// Pin-Right-Center
	glPushMatrix();
	glTranslatef(6.8, 0, 0);
	glRotatef(-90, 1, 0, 0);
	quadObj = gluNewQuadric();
	gluCylinder(quadObj, 0.2, 0.1, 1.3 + fenceHeight, 10, 10);
	glRotatef(90, 1, 0, 0);
	glPopMatrix();

	// Pin-Left-Center
	glPushMatrix();
	glTranslatef(-6.8, 0, 0);
	glRotatef(-90, 1, 0, 0);
	quadObj = gluNewQuadric();
	gluCylinder(quadObj, 0.2, 0.1, 1.3 + fenceHeight, 10, 10);
	glRotatef(90, 1, 0, 0);
	glPopMatrix();
}

void DrawYardFloor(){
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, lightgreen);
	glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, lightgreen);
	glBegin(GL_POLYGON);
	glNormal3f(0, 1, 0);
	glVertex3f(-7.3, -0.005, -7.3);
	glVertex3f(-7.3, -0.005, 7.3);
	glVertex3f(7.3, -0.005, 7.3);
	glVertex3f(7.3, -0.005, -7.3);
	glEnd();
}

void DrawCenterPin(){
	glRotatef(-90, 1, 0, 0);
	GLUquadricObj *quadObj = gluNewQuadric();
	gluCylinder(quadObj, 0.2, 0.3, 7, 10, 10);
	glRotatef(90, 1, 0, 0);
}

void DrawBase(){
	glRotatef(-90, 1, 0, 0);
	GLUquadricObj *quadObj = gluNewQuadric();
	gluCylinder(quadObj, 0.3, 0.1, 2, 10, 10);
	glRotatef(90, 1, 0, 0);

}

void DrawTop(){
	glPushMatrix();
	glTranslatef(0, 7.0, 0);
	glRotatef(-90, 1, 0, 0);
	GLUquadricObj *quadObj = gluNewQuadric();
	gluCylinder(quadObj, 0.3, 0.0, 1.0, 10, 10);
	glRotatef(90, 1, 0, 0);
	glPopMatrix();
}


void DrawHorizontalStick(){

	// Front of Horizontal stick
	glNormal3f(0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(0.0, 7.0, 0.25);
	glVertex3f(0.0, 6.75, 0.25);
	glVertex3f(4.0 * cos(radian__IN_RANGE), 6.75 + 4.0 * sin(radian__IN_RANGE), 0.25);
	glVertex3f(4.0 * cos(radian__IN_RANGE), 7.0 + 4.0 * sin(radian__IN_RANGE), 0.25);
	glEnd();


	// Back of Horizontal stick
	glNormal3f(0.0, 0.0, -1.0);
	glBegin(GL_POLYGON);
	glVertex3f(0.0, 6.75, -0.25);
	glVertex3f(0.0, 7.0, -0.25);
	glVertex3f(4.0 * cos(radian__IN_RANGE), 7.0 + 4.0 * sin(radian__IN_RANGE), -0.25);
	glVertex3f(4.0 * cos(radian__IN_RANGE), 6.75 + 4.0 * sin(radian__IN_RANGE), -0.25);
	glEnd();


	// Top of Horizontal stick
	glNormal3f(-sin(radian__IN_RANGE), cos(radian__IN_RANGE), 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(0.0, 7.0, -0.25);
	glVertex3f(0.0, 7.0, 0.25);
	glVertex3f(4.0 * cos(radian__IN_RANGE), 7.0 + 4.0 * sin(radian__IN_RANGE), 0.25);
	glVertex3f(4.0 * cos(radian__IN_RANGE), 7.0 + 4.0 * sin(radian__IN_RANGE), -0.25);
	glEnd();


	// Buttom of Horizontal stick
	glNormal3f(sin(radian__IN_RANGE), -cos(radian__IN_RANGE), 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(0.0, 6.75, 0.25);
	glVertex3f(0.0, 6.75, -0.25);
	glVertex3f(4.0 * cos(radian__IN_RANGE), 6.75 + 4.0 * sin(radian__IN_RANGE), -0.25);
	glVertex3f(4.0 * cos(radian__IN_RANGE), 6.75 + 4.0 * sin(radian__IN_RANGE), 0.25);
	glEnd();


	// End of Horizontal stick
	glNormal3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(4.0 * cos(radian__IN_RANGE), 6.75 + 4.0 * sin(radian__IN_RANGE), -0.25);
	glVertex3f(4.0 * cos(radian__IN_RANGE), 7.0 + 4.0 * sin(radian__IN_RANGE), -0.25);
	glVertex3f(4.0 * cos(radian__IN_RANGE), 7.0 + 4.0 * sin(radian__IN_RANGE), 0.25);
	glVertex3f(4.0 * cos(radian__IN_RANGE), 6.75 + 4.0 * sin(radian__IN_RANGE), 0.25);
	glEnd();
}

void DrawVerticalStick(){
	glNormal3f(0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(4.0 * cos(radian__IN_RANGE) + 0.125, 7.0 + 4.0 * sin(radian__IN_RANGE), 0.25);
	glVertex3f(4.0 * cos(radian__IN_RANGE) - 0.125, 7.0 + 4.0 * sin(radian__IN_RANGE), 0.25);
	glVertex3f(4.0 * cos(radian__IN_RANGE) - 0.125, 7.0 + 4.0 * sin(radian__IN_RANGE) - 1, 0.25);
	glVertex3f(4.0 * cos(radian__IN_RANGE) + 0.125, 7.0 + 4.0 * sin(radian__IN_RANGE) - 1, 0.25);
	glEnd();

	glNormal3f(0.0, 0.0, -1.0);
	glBegin(GL_POLYGON);
	glVertex3f(4.0 * cos(radian__IN_RANGE) - 0.125, 7.0 + 4.0 * sin(radian__IN_RANGE), -0.25);
	glVertex3f(4.0 * cos(radian__IN_RANGE) + 0.125, 7.0 + 4.0 * sin(radian__IN_RANGE), -0.25);
	glVertex3f(4.0 * cos(radian__IN_RANGE) + 0.125, 7.0 + 4.0 * sin(radian__IN_RANGE) - 1, -0.25);
	glVertex3f(4.0 * cos(radian__IN_RANGE) - 0.125, 7.0 + 4.0 * sin(radian__IN_RANGE) - 1, -0.25);
	glEnd();

	glNormal3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(4.0 * cos(radian__IN_RANGE) + 0.125, 7.0 + 4.0 * sin(radian__IN_RANGE), -0.25);
	glVertex3f(4.0 * cos(radian__IN_RANGE) + 0.125, 7.0 + 4.0 * sin(radian__IN_RANGE), +0.25);
	glVertex3f(4.0 * cos(radian__IN_RANGE) + 0.125, 7.0 + 4.0 * sin(radian__IN_RANGE) - 1, +0.25);
	glVertex3f(4.0 * cos(radian__IN_RANGE) + 0.125, 7.0 + 4.0 * sin(radian__IN_RANGE) - 1, -0.25);
	glEnd();

	glNormal3f(-1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(4.0 * cos(radian__IN_RANGE) - 0.125, 7.0 + 4.0 * sin(radian__IN_RANGE), +0.25);
	glVertex3f(4.0 * cos(radian__IN_RANGE) - 0.125, 7.0 + 4.0 * sin(radian__IN_RANGE), -0.25);
	glVertex3f(4.0 * cos(radian__IN_RANGE) - 0.125, 7.0 + 4.0 * sin(radian__IN_RANGE) - 1, -0.25);
	glVertex3f(4.0 * cos(radian__IN_RANGE) - 0.125, 7.0 + 4.0 * sin(radian__IN_RANGE) - 1, +0.25);
	glEnd();

	glNormal3f(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(4.0 * cos(radian__IN_RANGE) + 0.125, 7.0 + 4.0 * sin(radian__IN_RANGE), +0.25);
	glVertex3f(4.0 * cos(radian__IN_RANGE) + 0.125, 7.0 + 4.0 * sin(radian__IN_RANGE), -0.25);
	glVertex3f(4.0 * cos(radian__IN_RANGE) - 0.125, 7.0 + 4.0 * sin(radian__IN_RANGE), -0.25);
	glVertex3f(4.0 * cos(radian__IN_RANGE) - 0.125, 7.0 + 4.0 * sin(radian__IN_RANGE), +0.25);
	glEnd();
}

void DrawCabin(){

	// Back
	glNormal3f(0.0, 0.0, -1.0);
	glBegin(GL_POLYGON);
	glVertex3f(0, 0, -1);
	glVertex3f(0, 1, -1);
	glVertex3f(2, 1, -1);
	glVertex3f(2, 0, -1);
	glEnd();

	glNormal3f(0.0, 0.0, -1.0);
	glBegin(GL_POLYGON);
	glVertex3f(0, 1.7, -1);
	glVertex3f(0, 2, -1);
	glVertex3f(2, 2, -1);
	glVertex3f(2, 1.7, -1);
	glEnd();

	glNormal3f(0.0, 0.0, -1.0);
	glBegin(GL_POLYGON);
	glVertex3f(0, 1, -1);
	glVertex3f(0, 1.7, -1);
	glVertex3f(0.2, 1.7, -1);
	glVertex3f(0.2, 1, -1);
	glEnd();

	glNormal3f(0.0, 0.0, -1.0);
	glBegin(GL_POLYGON);
	glVertex3f(1.8, 1, -1);
	glVertex3f(1.8, 1.7, -1);
	glVertex3f(2, 1.7, -1);
	glVertex3f(2, 1, -1);
	glEnd();


	// Front
	glNormal3f(0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(2, 0, 1);
	glVertex3f(2, 1, 1);
	glVertex3f(0, 1, 1);
	glVertex3f(0, 0, 1);
	glEnd();

	glNormal3f(0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(2, 1.7, 1);
	glVertex3f(2, 2, 1);
	glVertex3f(0, 2, 1);
	glVertex3f(0, 1.7, 1);
	glEnd();

	glNormal3f(0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(0.2, 1, 1);
	glVertex3f(0.2, 1.7, 1);
	glVertex3f(0, 1.7, 1);
	glVertex3f(0, 1, 1);
	glEnd();

	glNormal3f(0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(2, 1, 1);
	glVertex3f(2, 1.7, 1);
	glVertex3f(1.8, 1.7, 1);
	glVertex3f(1.8, 1, 1);
	glEnd();


	// Floor
	glNormal3f(0.0, -1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(2, 0, -1);
	glVertex3f(2, 0, 1);
	glVertex3f(0, 0, 1);
	glVertex3f(0, 0, -1);
	glEnd();


	// Top
	glNormal3f(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(2, 2, 1);
	glVertex3f(2, 2, -1);
	glVertex3f(0, 2, -1);
	glVertex3f(0, 2, 1);
	glEnd();

	// Right
	glNormal3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(2, 0, -1);
	glVertex3f(2, 1, -1);
	glVertex3f(2, 1, 1);
	glVertex3f(2, 0, 1);
	glEnd();

	glNormal3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(2, 1.7, -1);
	glVertex3f(2, 2, -1);
	glVertex3f(2, 2, 1);
	glVertex3f(2, 1.7, 1);
	glEnd();

	glNormal3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(2, 1, -1);
	glVertex3f(2, 1.7, -1);
	glVertex3f(2, 1.7, -0.8);
	glVertex3f(2, 1, -0.8);
	glEnd();

	glNormal3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(2, 1, 0.8);
	glVertex3f(2, 1.7, 0.8);
	glVertex3f(2, 1.7, 1);
	glVertex3f(2, 1, 1);
	glEnd();

	// Left
	glNormal3f(-1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(0, 0, -1);
	glVertex3f(0, 0, 1);
	glVertex3f(0, 1, 1);
	glVertex3f(0, 1, -1);
	glEnd();

	glNormal3f(-1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(0, 1.7, -1);
	glVertex3f(0, 1.7, 1);
	glVertex3f(0, 2, 1);
	glVertex3f(0, 2, -1);
	glEnd();

	glNormal3f(-1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(0, 1, -1);
	glVertex3f(0, 1, -0.8);
	glVertex3f(0, 1.7, -0.8);
	glVertex3f(0, 1.7, -1);
	glEnd();

	glNormal3f(-1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(0, 1, 0.8);
	glVertex3f(0, 1, 1);
	glVertex3f(0, 1.7, 1);
	glVertex3f(0, 1.7, 0.8);
	glEnd();
}

void darwCabin__FINAL(){
	glPushMatrix();
	glTranslatef(4.0 * cos(radian__IN_RANGE), 7.0 + 4.0 * sin(radian__IN_RANGE) - 3, 0.0);
	glRotatef(angle, 0, 1, 0);
	glPushMatrix();
	glTranslatef(-1, 0, 0);
	DrawCabin();
	glPopMatrix();
	glRotatef(-angle, 0, 1, 0);
	glPopMatrix();
}

void display(void)
{
	for (int i = 0; i < 2; i++) {
		glutSetWindow(window[i]); // set the current window to window[i]

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 64);

		if (i == 1) {
			gluLookAt(0.7, 0, 0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
			glRotatef(-angle, 0, 1, 0);
			glTranslatef(-4.0 * cos(radian__IN_RANGE), -5.4 + 4.0 * sin(radian__IN_RANGE), 0);
			glRotatef(-angle, 0, 1, 0);
		}
		else if (i == 0) {
			cpos[0] = zoom * cos(beta) * sin(alpha);
			cpos[1] = zoom * sin(beta);
			cpos[2] = zoom * cos(beta) * cos(alpha);
			gluLookAt(cpos[0], cpos[1], cpos[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
		}


		if (lightSource == true){
			glLightfv(GL_LIGHT0, GL_POSITION, lpos);
			glMaterialfv(GL_FRONT, GL_EMISSION, white);
			glPushMatrix();
			glTranslatef(lpos[0], lpos[1], lpos[2]);
			glutSolidSphere(0.1, 10, 8);
			glPopMatrix();
			glMaterialfv(GL_FRONT, GL_EMISSION, black);
		}

		DrawYardFloor();
		DrawSticksArroundYard();
		DrawCenterPin();
		DrawBase();
		DrawTop();

		glRotatef(angle, 0, 1, 0);
		for (int j = 0; j < TotalNumberOfCabins; j++){
			glMaterialfv(GL_FRONT, GL_SPECULAR, white);
			glMaterialf(GL_FRONT, GL_SHININESS, 64);
			
			if (id % TotalNumberOfCabins == 0)
			{
				glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, green);
				glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, black);
			}
			else if (id % TotalNumberOfCabins == 1)
			{
				glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blue);
				glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, black);
			}
			else if (id % TotalNumberOfCabins == 2)
			{
				glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
				glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, black);
			}
			else if (id % TotalNumberOfCabins == 3)
			{
				glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cyan);
				glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, black);
			}
			else if (id % TotalNumberOfCabins == 4)
			{
				glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, red);
				glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, black);
			}
			glPushMatrix();
			glRotatef(j * 360 / TotalNumberOfCabins, 0, 1, 0);
			keepTrackOfID();

			DrawHorizontalStick();
			DrawVerticalStick();
			darwCabin__FINAL();

			id++;
			glPopMatrix();
		}
		glRotatef(-angle, 0, 1, 0);
		glFlush();
		glutSwapBuffers();
	}
}


void keyboard(unsigned char key, int x, int y)
{
	static int polygonmode[2];

	switch (key) {
	case 27:
		exit(0);
		break;
	case 'x':
		if (lightSource == true)
			lpos[0] = lpos[0] + 0.2;
		glutPostRedisplay();
		break;
	case 'X':
		if (lightSource == true)
			lpos[0] = lpos[0] - 0.2;
		glutPostRedisplay();
		break;
	case 'y':
		if (lightSource == true)
			lpos[1] = lpos[1] + 0.2;
		glutPostRedisplay();
		break;
	case 'Y':
		if (lightSource == true)
			lpos[1] = lpos[1] - 0.2;
		glutPostRedisplay();
		break;
	case 'z':
		if (lightSource == true)
			lpos[2] = lpos[2] + 0.2;
		glutPostRedisplay();
		break;
	case 'Z':
		if (lightSource == true)
			lpos[2] = lpos[2] - 0.2;
		glutPostRedisplay();
		break;

	case '+':
		if (zoom != 1.5)zoom = zoom - 0.5;
		glutPostRedisplay();
		break;
	case '-':
		if (zoom != 30)zoom = zoom + 0.5;
		glutPostRedisplay();
		break;
	case '0':
		if (lightSource == true){
			glDisable(GL_LIGHT0);
			lightSource = false;
		}
		else{
			glEnable(GL_LIGHT0);
			lightSource = true;
		}
		glutPostRedisplay();
		break;

	case 'e':
		if (fenceHeight < 2)
			fenceHeight += 0.5;
		glutPostRedisplay();
		break;
	case 'd':
		if (fenceHeight > -0.5)
			fenceHeight -= 0.5;
		glutPostRedisplay();
		break;

	case 'w':
		glGetIntegerv(GL_POLYGON_MODE, polygonmode);
		if (polygonmode[0] == GL_FILL)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glutPostRedisplay();
		break;
	case 'n':
		angle++;
		processAngle();
		setRadian_IN_RANGE();
		glutPostRedisplay();
		break;
	case 'm':
		angle--;
		processAngle();
		setRadian_IN_RANGE();
		glutPostRedisplay();
		break;
	case 'r':
		if (TotalNumberOfCabins < 5)
			TotalNumberOfCabins++;
		glutPostRedisplay();
		break;
	case 'f':
		if (TotalNumberOfCabins > 0)
			TotalNumberOfCabins--;
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

void mouse(int button, int state, int x, int y)
{
	switch (button) {
	case GLUT_LEFT_BUTTON:
		signal = 0;
		if (speed == 0)
			speed++;
		if (speed <= 25)
			speed += 2;
		break;
	case GLUT_MIDDLE_BUTTON:
	case GLUT_RIGHT_BUTTON:
		signal = 1;
		if (speed > 2)
			speed -= 2;
		break;
	default:
		break;
	}
}

void specialkey(GLint key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_RIGHT:
		alpha = alpha + PI / 180;
		if (alpha > 2 * PI) alpha = alpha - 2 * PI;
		glutPostRedisplay();
		break;
	case GLUT_KEY_LEFT:
		alpha = alpha - PI / 180;
		if (alpha < 0) alpha = alpha + 2 * PI;
		glutPostRedisplay();
		break;
	case GLUT_KEY_UP:
		if (beta < 0.45*PI) beta = beta + PI / 180;
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN:
		if (beta > -0.05*PI) beta = beta - PI / 180;
		glutPostRedisplay();
		break;
	default:
		break;
	}
}



void anim(){
	// Overflow Protection
	if (duration + 1 == INT_MAX)
		duration = 0;
	if (angle + 1 == INT_MAX)
		duration = 0;

	if (speed == 1)
		signal = 3;
	else
		duration++;

	if (signal == 0){
		angle++;
		if (speed <= 25 && duration % input1 == 0)
			speed++;
		// The time carousel is in it's peak speed and rotating
		else if (speed > 25 && duration % input2 == 0)
			signal = 1;
		glutPostRedisplay();
	}
	if (signal == 1){
		if (speed > 1){
			angle++;
			if (speed > 1 && duration % input1 == 0)
				speed--;
			glutPostRedisplay();
		}
	}
	if (signal == 3){
		// Do nothing when carousel has not started yet
	}
	else{
		Sleep((int)(100 / speed));
		printf("angle: %d\tspeed: %d\tduration: %d\n", angle, speed, duration);
	}
}


int main(int argc, char** argv)
{
	writemessage();
	printf("\n\n***************************\n");
	printf("Every how long do you want the carousel to change (increase/decrease) it's speed?\n\n --> The default value is 100 <--\n\n --> Please enter default value for best experince\n\nPlease input an integer value and Do Not enter zero: ");
	scanf("%d", &input1);
	printf("\n\n");
	printf("How long do you want the carousel be in it's peak (maximum) speed?\n\n --> The default value is 3000 <--\n\n --> Please enter default value for best experince\n\nPlease input an integer value and Do Not enter zero: ");
	scanf("%d", &input2);

	fillArray();
	processAngle();
	setRadian_IN_RANGE();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	window[0] = glutCreateWindow("First");
	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(anim);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialkey);

	glutInitWindowSize(500, 500);
	glutInitWindowPosition(600, 10);
	window[1] = glutCreateWindow("Second");
	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(anim);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialkey);

	glutMainLoop();
	return 0;
}