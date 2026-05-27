#include <GL/glut.h>
int angle = 0;
int mode = 1;
void MyTimer(int v) {
	angle++;
	glutPostRedisplay();
	glutTimerFunc(10, MyTimer, 0); // 10ms마다 MyIdle 호출
}

void MyKeyboard(unsigned char ch, int x, int y) {
	if (ch == 'q') exit(0);
	if (ch == '1') mode = 1;
	if (ch == '2') mode = 2;
	if (ch == '3') mode = 3;
	// 타이머가 있으므로 굳이 다시 그리지 않는다.
	//glutPostRedisplay(); 
}
void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, 600, 600);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	switch (mode) {
	case 1:
		glColor3f(1.0, 0.0, 0.0);
		glRotatef(angle * 0.8f, 0.0, 0.0, 1.0); // 2. 회전
		break;
	case 2:
		glColor3f(0.0, 1.0, 0.0);
		glTranslatef(-0.15, -0.15, 0.0);	// 3. 회전 중심을 원하는 곳으로 이동
		glRotatef(angle * 0.8f, 0.0, 0.0, 1.0); // 2. 회전
		glTranslatef(0.15, 0.15, 0.0);	// 1. 회전 중심을 원점으로 이동
		break;
	case 3:
		glColor3f(0.0, 0.0, 1.0);
		break;
	}
	glutSolidCube(0.3);
	glFlush();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("OpenGL Sample Drawing");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glutDisplayFunc(MyDisplay);
	glutKeyboardFunc(MyKeyboard);
	//glutIdleFunc(MyIdle); // idle 대신 timer 사용
	glutTimerFunc(10, MyTimer, 0); // 10ms마다 MyIdle 호출
	glutMainLoop();
	return 0;
}
// 도전문제
// 1. 사각형은 중심이 원점이 아니고, (0.6, 0.4)위치에 존재한다. 그리고 그 (0.6, 0.4)을 중심으로 회전한다.
// 2. 사각형은 중심이 (0.6, 0.4)위치에 존재한다. 그리고 이동한 사각형의 좌하단 (0.6-0.15, 0.4-0.15)를 중심으로 회전한다.