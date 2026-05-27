#include <GL/glut.h>
int angle = 0;
int mode = 1;
void MyTimer(int v) {
	angle++;
	glutTimerFunc(10, MyTimer, 0); // 10ms마다 MyIdle 호출
	glutPostRedisplay();
}

void MyKeyboard(unsigned char ch, int x, int y) {
	if (ch == 'q') exit(0);
	if (ch == '1') mode = 1;
	if (ch == '2') mode = 2;
	if (ch == '3') mode = 3;
	//glutPostRedisplay();
}
void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, 600, 600);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	switch (mode) {
	case 1: // 물체 기준 간단한 방법
		glColor3f(1.0, 0.0, 0.0);
		glTranslatef(0.6 - 0.15, 0.4 - 0.15, 0.0);	// 3. 회전 중심을 원하는 곳으로 이동
		glRotatef(angle * 0.8f, 0.0, 0.0, 1.0); // 2. 회전
		glTranslatef(0.15, 0.15, 0.0);	// 1. 회전 중심을 원점으로 이동
		break;
	case 2: // 좌표계 기준 이해, 물체기준 이해도 가능
		glColor3f(0.0, 1.0, 0.0);
		glTranslatef(0.6, 0.4, 0.0);	// 1. 좌표계를 이동 
		glTranslatef((-0.15), (-0.15), 0.0);	// 2. 회전 중심이 물체 좌표의 원점이 되도록 추가 이동
		glRotatef(angle * 0.8f, 0.0, 0.0, 1.0); // 3. 피봇 이동에서 회전
		glTranslatef(0.15, 0.15, 0.0);	// 4. 회전결과를 원위치(좌표계가 이미 회전되어 있으므로, 좌하단이 회전 전의 위치로 복귀함)
		break;
	case 3: // 물체 기준 복잡한 방법(좌하단의 전역좌표가 0.45, 0.25임을 이용)
		glColor3f(0.0, 0.0, 1.0);
		glTranslatef((0.6 - 0.15), (0.4 - 0.15), 0.0);	// 4. 피봇회전 3단계, 원 자리로 복원
		glRotatef(angle * 0.8f, 0.0, 0.0, 1.0);	// 3. 피봇회전 2단계, 실제 회전
		glTranslatef(-(0.6 - 0.15), -(0.4 - 0.15), 0.0); // 2. 피봇회전 1단계, 피봇의 움직임. 피봇의 위치를 알고 있음
		glTranslatef(0.6, 0.4, 0.0); // 1. 움직인다. glutSolidCube(0.3)와 연결되어 있는 느낌.
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