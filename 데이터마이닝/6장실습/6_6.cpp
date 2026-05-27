#include <GL/glut.h>
static float Day = 0, Time = 0;

void MyTimer(int v) {
	Day++;
	Time += 0.5;
	glutPostRedisplay();
	glutTimerFunc(10, MyTimer, 0); // 10ms마다 MyIdle 호출
}
void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(1.0, 0.3, 0.3);
	glutWireSphere(0.15, 20, 16);
	glPushMatrix();
	glRotatef(Day, 0.0, 1.0, 0.0);
	glTranslatef(0.6, 0.0, 0.0);
	glRotatef(Time, 0.0, 1.0, 0.0);  // 엄밀하게는 지구의 자전이 달의 공전을 유발하는 문제가 있다.
	glColor3f(0.5, 0.6, 0.7);
	glutWireSphere(0.08, 10, 8);
	glPushMatrix();
	glRotatef(Time, 0.0, 1.0, 0.0);
	glTranslatef(0.15, 0.0, 0.0);
	glColor3f(0.9, 0.8, 0.2);
	glutWireSphere(0.04, 10, 8);
	glPopMatrix();
	glPopMatrix();
	glutSwapBuffers();
}

void MyKeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'd':
		Day += 10;
		if (Day >= 360)
			Day -= 360;
		glutPostRedisplay();
		break;
	case 't':
		Time += 5;
		if (Time >= 360)
			Time -= 360;
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("OpenGL Sample Drawing");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glutDisplayFunc(MyDisplay);
	glutKeyboardFunc(MyKeyboard);
	glutTimerFunc(10, MyTimer, 0); // 10ms마다 MyIdle 호출
	glutMainLoop();
	return 0;
}
// 도전문제
// 1. glutTimerFunc를 이용하여 자전과 공전을 구현하시오.
// 2. 지구에 보라색 달을 추가하시오. 원래 달보다 지구에서 약간 더 멀고, 약간 더 느리게 회전한다.
// 3. 지구보다 안쪽에서 태양을 중심으로 회전하는 녹색 금성을 추가하시오.
// 3-1. 금성은 자전하지 않고, 지구보다 빠르게 공전한다.