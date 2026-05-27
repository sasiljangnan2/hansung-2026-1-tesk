#include <GL/glut.h>
void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, 600, 600);
	glColor3f(1.0, 0.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); // 단위행렬로 초기화한다. 이 함수가 왜 필요한지 생각해보자.
	//glRotatef(45.0, 0.0, 0.0, 1.0);
	if (true) {
		glTranslatef(0.6, 0.0, 0.0);
	}
	else {
		// 평행이동, column major.
		float mat[16] = {
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0.6, 0, 0, 1
		};
		// 차이: glTranslatef는 기존 행렬에 곱하는 것이고, glLoadMatrixf는 행렬을 덮어쓰는 것이다.
		glLoadMatrixf(mat);
	}
	glutSolidCube(0.3);
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
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glutDisplayFunc(MyDisplay);
	glutMainLoop();
	return 0;
}