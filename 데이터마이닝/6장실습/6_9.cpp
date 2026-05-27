#include <GL/glut.h>
#include <math.h>

float h = 0.25;
float a = 0.01f;
float t = 0;
GLUquadricObj* cyl;

void MyIdle()
{
	t = t + 1.0f;
	if (h <= 0.1) a = +0.0001f;
	if (h >= 0.6) a = -0.0001f;
	h = h + a;
	glutPostRedisplay();
}

void MyTimer(int v) {
	t = t + 1.0f;
	if (h <= 0.1) a = 0.01f;
	if (h >= 0.6) a = -0.01f;
	h = h + a;
	glutTimerFunc(10, MyTimer, 0); // 10ms마다 MyIdle 호출
	glutPostRedisplay();
}
// 현재 좌표계에서, 높낮이는 y축으로, 앞뒤는 z축으로, 좌우는 x축으로 설정되어 있다.
void MyDisplay() {
	cyl = gluNewQuadric();
	gluQuadricDrawStyle(cyl, GLU_LINE);

	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	//실린더의 기본 형태를 파악한다.
	//gluCylinder(cyl, 0.1, 0.1, 2.0, 20, 15);
	glScalef(8, 0.3, 8);
	glutWireCube(0.3);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.0, 0.0, 1.0);
	glTranslatef(0, h, 0);
	glutWireSphere(0.1, 20, 20);
	glPopMatrix();

	// 1. 몸통
	//glPushMatrix();
	// glRotatef(-90, 1, 0, 0); // -90
	// // Cynliner는 +z방향으로 길어진다.
	// gluCylinder(cyl, 0.1, 0.1, 0.5, 20, 5);
	//
	// // 2. 팔1
	//	glPushMatrix();
	//	 glTranslatef(0.15, 0.0, 0.5);
	//	 glutWireSphere(0.05, 20, 20);
	//	 glRotatef( t*0.01, 1, 0, 0);
	//	 gluCylinder(cyl, 0.05, 0.05, 0.2, 20, 1);
	//	glPopMatrix();
	//
	//glPopMatrix(); // 몸통 끝


	glFlush();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("OpenGL Sample Drawing");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(20, 1, 0.1, 1000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 1.6, 8,
		0, 0, 0,
		0, 1, 0);

	glutDisplayFunc(MyDisplay);
	//glutIdleFunc(MyIdle); // timer를 사용하기로 한다.
	glutTimerFunc(10, MyTimer, 0); // 10ms마다 MyIdle 호출
	glutMainLoop();
	return 0;
}