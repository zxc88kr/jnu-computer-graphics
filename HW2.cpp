// 컴퓨터그래픽스 HW#2
// 학번 : 195443
// 이름 : 박찬

#include <glut.h>

float theta = 0.0; // angle of rotation
float scale = 1.000; // size of multiple
bool scaleUp = true; // size is increasing

void quad()	// one quad
{
	glBegin(GL_QUADS);
	glVertex3d(0.0, 0.0, 0.0);
	glVertex3d(1.0, 0.0, 0.0);
	glVertex3d(1.0, 1.0, 0.0);
	glVertex3d(0.0, 1.0, 0.0);
	glEnd();
}

void cube() // one cube with six quads
{
	// front side
	glColor3d(0.0, 1.0, 0.0); // green
	glPushMatrix();
	quad();
	glPopMatrix();

	// back side
	glColor3d(1.0, 0.0, 0.0); // red
	glPushMatrix();
	glTranslatef(0.0, 0.0, -1.0);
	quad();
	glPopMatrix();

	// left side
	glColor3d(0.0, 0.0, 1.0); // blue
	glPushMatrix();
	glRotatef(90.0, 0.0, 1.0, 0.0);
	quad();
	glPopMatrix();

	// right side
	glColor3d(1.0, 1.0, 0.0); // yellow
	glPushMatrix();
	glRotatef(90.0, 0.0, 1.0, 0.0);
	glTranslatef(0.0, 0.0, 1.0);
	quad();
	glPopMatrix();

	// top side
	glColor3d(1.0, 0.0, 1.0); // magenta
	glPushMatrix();
	glRotatef(90.0, -1.0, 0.0, 0.0);
	glTranslatef(0.0, 0.0, 1.0);
	quad();
	glPopMatrix();

	// bottom side
	glColor3d(0.0, 1.0, 1.0); // cyan
	glPushMatrix();
	glRotatef(90.0, -1.0, 0.0, 0.0);
	quad();
	glPopMatrix();
}

void cone() // cone
{
	glColor3d(0.7, 1.0, 0.7); // light green
	glPushMatrix();
	glTranslatef(-2.5, 0.0, 0.0);
	glRotatef(90.0, -1.0, 0.0, 0.0);
	glutSolidCone(1.0, 1.0, 100, 100);
	glPopMatrix();
}

void torus() // torus
{
	glColor3d(1.0, 0.7, 1.0); // light pink
	glPushMatrix();
	glTranslatef(0.0, 2.5, -1.0);
	glRotatef(25.0, 1.0, 0.0, 0.0);
	glutSolidTorus(0.3, 0.7, 3, 30);
	glPopMatrix();
}

void sphere() // sphere
{
	GLUquadricObj* qobj;
	qobj = gluNewQuadric();
	glColor3d(0.3, 0.3, 0.3); // light black
	glPushMatrix();
	glTranslatef(0.0, -1.5, 1.0);
	gluSphere(qobj, 0.5, 100, 100);
	glPopMatrix();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glRotatef(theta, 1.0, 1.0, -1.0);
	cube();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.5, 0.0, -0.5);
	glRotatef(theta, 0.0, 1.0, 0.0);
	glTranslatef(0.0, 0.0, 1.0);
	cone();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 2.5, -1.0);
	glRotatef(theta * 2, 1.0, 0.0, 0.0);
	glTranslatef(0.0, -2.5, 1.0);
	torus();
	glPopMatrix();

	glPushMatrix();
	glScalef(scale, scale, scale);
	sphere();
	glPopMatrix();

	glutSwapBuffers(); // double buffer switching

	theta += 0.1;
	if (theta > 360.0)
		theta -= 360.0;

	if (scaleUp) // size is increasing
	{
		scale += 0.001;
		if (scale >= 2.000)
			scaleUp = false;
	}
	else // size is decreasing
	{
		scale -= 0.001;
		if (scale <= 1.000)
			scaleUp = true;
	}
}

void init()
{
	glClearColor(0.7, 0.5, 0.3, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(20.0, 1.0, 1.0, 150.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(15.0, 10.0, 20.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glEnable(GL_DEPTH_TEST);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // double buffer

	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("HW2");

	init();

	glutDisplayFunc(display);
	glutIdleFunc(display);

	glutMainLoop();

	return 0;
}