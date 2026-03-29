#include <GL/glut.h>
void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);       //컬러버퍼에 초기화 색을 가함
	glColor3f(0.5, 0.5, 0.5);           //회색
	glBegin(GL_POLYGON);                //사각형
	glVertex3f(-0.5, -0.5, 0.0);    //좌하단 좌표
	glVertex3f(0.5, -0.5, 0.0);     //좌하단 좌표
	glVertex3f(0.5, 0.5, 0.0);      //우상단 좌표
	glVertex3f(-0.5, 0.5, 0.0);     //좌상단 좌표
	glEnd();
	glFlush();
}
void MyReshape(int NewWidth, int NewHeight) {
	glViewport(0, 0, NewWidth, NewHeight);
	GLfloat WidthFactor = (GLfloat)NewWidth / (GLfloat)600;
	GLfloat HeightFactor = (GLfloat)NewHeight / (GLfloat)600;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// 창크기가 1200x600이라면, WidthFactor는 2.0, HeightFactor는 1.0이 됨
	// glOrtho의 범위는 x: -2.0 ~ 2.0, y: -1.0 ~ 1.0이 됨
	glOrtho(-1.0 * WidthFactor, 1.0 * WidthFactor,
		-1.0 * HeightFactor, 1.0 * HeightFactor, -1.0, 1.0);
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);               //GLUT 윈도우 함수
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("OpenGL Example Drawing");
	glClearColor(1.0, 1.0, 1.0, 1.0);   //초기화 색은 백색
	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
	glutMainLoop();
	return 0;
}
