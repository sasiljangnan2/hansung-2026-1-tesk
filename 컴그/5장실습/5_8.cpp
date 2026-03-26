#include <GL/glut.h>
GLboolean IsSphere = true;

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.5, 0.0, 0.5);
    if (IsSphere)
        glutWireSphere(0.2, 15, 15);
    else
        glutWireTorus(0.1, 0.3, 40, 20);
    glFlush();
}

void MyMainMenu(int entryID) {
    if (entryID == 1)
        IsSphere = true;
    else if (entryID == 2)
        IsSphere = false;
    else if (entryID == 9)
        exit(0);
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("OpenGL Example Drawing");

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

    GLint MyMainMenuID = glutCreateMenu(MyMainMenu); // 비어있는 메뉴를 생성
    glutAddMenuEntry("Draw Sphere", 1); // 메뉴 하나 추가
    glutAddMenuEntry("Draw Torus", 2);
    glutAddMenuEntry("Exit", 9); // 번호는 임의로 정해도 된다.
    glutAttachMenu(GLUT_RIGHT_BUTTON); // 오른쪽 버튼에 메뉴를 붙인다. GLUT_MIDDLE_BUTTON
    glutDisplayFunc(MyDisplay);
    glutMainLoop();
    return 0;
}

// 문제: 메뉴에 주전자 그리기(Draw Teapot)를 추가하고, 이를 선택하면 주전자를 그리도록 프로그램을 수정하시오.