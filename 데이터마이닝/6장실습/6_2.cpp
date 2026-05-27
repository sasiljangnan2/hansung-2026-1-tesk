#include <GL/glut.h>
#include <math.h>
void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, 600, 600);
	glColor3f(1.0, 0.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	int option = 3;
	switch (option) {
	case 0:
		glTranslatef(0.6f, 0.0, 0.0); // x축으로 0.6만큼 이동
		break;
	case 1: {
		float mat1[16] = { // gl은 column major 방식으로 저장된다.
			1,		0, 0, 0,
			0,		1, 0, 0,
			0,		0, 1, 0,
			0.6f,	0, 0, 1
		};
		glLoadMatrixf(mat1); // 직접 행렬 입력
	    }
		break;
	case 2:
		glRotatef(15.0, 0.0, 0.0, 1.0);
		break;
	case 3: {
		float rad = 15.0 * 3.141592 / 180.0;
		float mat2[16] = { // 수학 교재와 비교하면 전치시킨 느낌으로 저장해야 한다.
			cos(rad), sin(rad), 0, 0,
			-sin(rad), cos(rad), 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		};
		glLoadMatrixf(mat2); // 직접 행렬 입력
	    }
		break;
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