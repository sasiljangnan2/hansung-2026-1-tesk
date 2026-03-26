#include <GL/glut.h>
#include <stdio.h>
GLfloat Delta = 0.0;
GLfloat cx = -0.5, cy = 0.0;
float clickX = 0, clickY = 0;
float moveX = 0, moveY = 0;
void MyDisplay() {

    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.5, 0.8);

    // 중심점을 기준으로 사각형을 그림
    //glVertex3f(cx - 0.5 + Delta, cy - 0.5, 0.0);
    //glVertex3f(cx + 0.5 + Delta, cy - 0.5, 0.0);
    //glVertex3f(cx + 0.5 + Delta, cy + 0.5, 0.0);
    //glVertex3f(cx - 0.5 + Delta, cy + 0.5, 0.0);

    glVertex3f(-1.0 + Delta, -0.5, 0.0);
    glVertex3f(0.0 + Delta, -0.5, 0.0);
    glVertex3f(0.0 + Delta, 0.5, 0.0);
    glVertex3f(-1.0 + Delta, 0.5, 0.0);
    glEnd();
    glutSwapBuffers();
}

void MyIdle() {
    Delta = Delta + 0.001;
    glutPostRedisplay();
}

void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y) {
    if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN) {
        clickX = X / 600.0 * 2 - 1;         // glut 픽셀좌표를 -1 ~ 1 gl좌표로 변환
        clickY = (600 - Y) / 600.0 * 2 - 1;

        printf("target : %f, %f\n", clickX, clickY);
        printf("current : %f, %f\n", cx, cy);
    }
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("OpenGL Drawing Example");
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, 1.0, -1.0); // gl좌표는 -1 ~ 1 범위로 설정
    glutDisplayFunc(MyDisplay);
    glutIdleFunc(MyIdle);
    glutMouseFunc(MyMouseClick);
    glutMainLoop();
    return 0;
}
// 문제: 마우스를 클릭한 방향으로 사각형을 천천히 이동시키기