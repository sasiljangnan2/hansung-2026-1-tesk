#include <GL/glut.h>
GLint TopLeftX, TopLeftY, BottomRightX, BottomRightY;

void MyDisplay() {
    glViewport(0, 0, 600, 600);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_POLYGON);
        glVertex3f(TopLeftX / 600.0, (600 - TopLeftY) / 600.0, 0.0);
        glVertex3f(TopLeftX / 600.0, (600 - BottomRightY) / 600.0, 0.0);
        glVertex3f(BottomRightX / 600.0, (600 - BottomRightY) / 600.0, 0.0);
        glVertex3f(BottomRightX / 600.0, (600 - TopLeftY) / 600.0, 0.0);
    glEnd();
    glFlush();
}

void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y) {
    if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN) {
        TopLeftX = X;
        TopLeftY = Y;
    }
}

void MyMouseMove(GLint X, GLint Y) {
    BottomRightX = X;
    BottomRightY = Y;
    glutPostRedisplay(); // 매번 화면을 다시 그려달라고 요청
}

int main(int argc, char** argv) {
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("OpenGL Drawing Example");

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

    glutDisplayFunc(MyDisplay);
	glutMouseFunc(MyMouseClick); // 버튼을 누르거나 뗄 때 호출됨
	glutMotionFunc(MyMouseMove); // 드래그임. glutPassiveMotionFunc() for no button pressed
    glutMainLoop();
    return 0;
}
