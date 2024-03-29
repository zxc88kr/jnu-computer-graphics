// 컴퓨터그래픽스 HW#5
// 학번 : 195443
// 이름 : 박찬

#include <glut.h>

void teapot() // teapot
{
	glPushMatrix();
	glTranslatef(0.0, 0.3, 0.0);
	glutSolidTeapot(0.3);
	glPopMatrix();
}

void cube() // cube
{
	glPushMatrix();
	glTranslatef(0.0, -0.3, 0.0);
	glRotatef(30.0, 0.0, 1.0, 0.0);
	glutSolidCube(0.3);
	glPopMatrix();
}

void leftViewport() // image viewed from the right eye
{
	glViewport(0, 0, 500, 500);
	glPushMatrix();
	gluLookAt(0.1, 0.1, 0.3, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	teapot();
	cube();
	glPopMatrix();
}

void rightViewport() // image viewed from the left eye
{
	glViewport(500, 0, 500, 500);
	glPushMatrix();
	gluLookAt(-0.1, 0.1, 0.3, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	teapot();
	cube();
	glPopMatrix();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	leftViewport();
	rightViewport();

	glFlush(); // single buffer switching
}

void initProperty() // material and light properties
{
	GLfloat material_diffuse[] = { 0.5, 0.4, 0.3, 1.0 };
	GLfloat material_ambient[] = { 0.5, 0.4, 0.3, 1.0 };
	GLfloat material_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat material_shininess[] = { 50.0 };
	
	GLfloat light_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat light_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_position[] = { -3.0, 2.0, 3.0, 0.0 };

	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);

	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}

void initVisibility() // polygon rendering
{
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
}

void init()
{
	glClearColor(0.7, 0.5, 0.3, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 2.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	initProperty();
	initVisibility();

	glEnable(GL_DEPTH_TEST);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); // single buffer

	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1000, 500);
	glutCreateWindow("HW5");

	init();

	glutDisplayFunc(display);
	glutIdleFunc(display);

	glutMainLoop();

	return 0;
}