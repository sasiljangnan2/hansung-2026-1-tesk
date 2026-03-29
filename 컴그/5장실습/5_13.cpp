#include <windows.h>
#include <GL/glut.h>

GLfloat MyVertices[8][3] = {
	{ -0.25, -0.25, 0.25 },
	{ -0.25, 0.25, 0.25 },
	{ 0.25, 0.25, 0.25 },
	{ 0.25, -0.25, 0.25 },
	{ -0.25, -0.25, -0.25 },
	{ -0.25, 0.25, -0.25 },
	{ 0.25, 0.25, -0.25 },
	{ 0.25, -0.25, -0.25 }
};
GLfloat MyColors[8][3] = {
	{ 0.2, 0.2, 0.2 },
	{ 1.0, 0.0, 0.0 },
	{ 1.0, 1.0, 0.0 },
	{ 0.0, 1.0, 0.0 },
	{ 0.0, 0.0, 1.0 },
	{ 1.0, 0.0, 1.0 },
	{ 1.0, 1.0, 1.0 },
	{ 0.0, 1.0, 1.0 }
};
GLubyte MyVertexList[24] = {
	0, 3, 2, 1,
	2, 3, 7, 6,
	0, 4, 7, 3,
	1, 2, 6, 5,
	4, 5, 6, 7,
	0, 1, 5, 4
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 현대적인 OpenGL에서는 VBO(Vertex Buffer Object)와 VAO(Vertex Array Object)를 사용한다.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef APIENTRYP
#define APIENTRYP APIENTRY *
#endif

// 1. VBO 관련 상수 직접 정의
#define GL_ARRAY_BUFFER								0x8892
#define GL_ELEMENT_ARRAY_BUFFER           0x8893
#define GL_STATIC_DRAW								0x88E4
// 추가된 자료형들
typedef ptrdiff_t GLintptr;
typedef ptrdiff_t GLsizeiptr;

// 2. 함수 포인터 타입 정의 (typedef)
typedef void (APIENTRYP PFNGLGENBUFFERSPROC) (GLsizei n, GLuint* buffers);
typedef void (APIENTRYP PFNGLBINDBUFFERPROC) (GLenum target, GLuint buffer);
typedef void (APIENTRYP PFNGLBUFFERDATAPROC) (GLenum target, GLsizeiptr size, const void* data, GLenum usage);
typedef void (APIENTRYP PFNGLDELETEBUFFERSPROC) (GLsizei n, const GLuint* buffers);
// --- VAO 관련 추가 정의 ---
typedef void (APIENTRYP PFNGLGENVERTEXARRAYSPROC) (GLsizei n, GLuint* arrays);
typedef void (APIENTRYP PFNGLBINDVERTEXARRAYPROC) (GLuint array);
typedef void (APIENTRYP PFNGLDELETEVERTEXARRAYSPROC) (GLsizei n, const GLuint* arrays);


// 3. 실제 함수로 사용할 포인터 변수 선언
PFNGLGENBUFFERSPROC glGenBuffers = NULL;
PFNGLBINDBUFFERPROC glBindBuffer = NULL;
PFNGLBUFFERDATAPROC glBufferData = NULL;
PFNGLDELETEBUFFERSPROC glDeleteBuffers = NULL;
PFNGLGENVERTEXARRAYSPROC glGenVertexArrays = NULL;
PFNGLBINDVERTEXARRAYPROC glBindVertexArray = NULL;
PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays = NULL;


// 버퍼 식별자 (ID)
GLuint vboVertexID, vboColorID, iboID;
// VAO 식별자 추가
GLuint vaoID;

void SetupScene() {
	// 1. 함수 포인터 로드
	glGenBuffers = (PFNGLGENBUFFERSPROC)wglGetProcAddress("glGenBuffers");
	glBindBuffer = (PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer");
	glBufferData = (PFNGLBUFFERDATAPROC)wglGetProcAddress("glBufferData");
	// VAO 함수 로드
	glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)wglGetProcAddress("glGenVertexArrays");
	glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)wglGetProcAddress("glBindVertexArray");

	// 2. VAO 생성 및 바인딩 (지금부터 하는 설정을 VAO에 저장함)
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);

	// --- 이 내부의 설정들이 VAO에 '녹화'됩니다 ---

	// 정점 VBO 설정
	glGenBuffers(1, &vboVertexID);
	glBindBuffer(GL_ARRAY_BUFFER, vboVertexID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(MyVertices), MyVertices, GL_STATIC_DRAW);
	glEnableClientState(GL_VERTEX_ARRAY); // 상태 포함
	// VAO는 glVertexPointer호출시 현재 VBO의 ID, 형식(GL_FLOAT, 3), offset을 저장한다.
	glVertexPointer(3, GL_FLOAT, 0, 0);			// 마지막 값은 주소가 아닌 offset 이다.
	// shader 코드에서는 다음과 같이 바뀐다 glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0) 

	// 색상 VBO 설정
	glGenBuffers(1, &vboColorID);
	glBindBuffer(GL_ARRAY_BUFFER, vboColorID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(MyColors), MyColors, GL_STATIC_DRAW);
	glEnableClientState(GL_COLOR_ARRAY); // 상태 포함
	glColorPointer(3, GL_FLOAT, 0, 0);
	// shader 코드에서는 다음과 같이 바뀐다 glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0) 

	// 인덱스 버퍼(IBO) 설정 (VAO는 IBO 바인딩 상태도 저장)
	glGenBuffers(1, &iboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID); // VAO는 glBindBuffer 호출시 인덱스 버퍼의 ID도 저장한다.
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(MyVertexList), MyVertexList, GL_STATIC_DRAW);

	// 녹화 종료 (바인딩 해제)
	glBindVertexArray(0);

	// 중요: VAO를 풀기 전에 VBO를 먼저 풀면 안 됩니다. 
	// VAO가 바인딩된 상태에서 세팅을 마쳐야 그 연결 관계가 VAO에 귀속됩니다.
}

void MyDisplayVAO() {
	glClear(GL_COLOR_BUFFER_BIT);
	glFrontFace(GL_CCW); // 깊이검사(8장)를 하지 않고, front face사용
	glEnable(GL_CULL_FACE);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(30.0, 1.0, 1.0, 1.0);

	// [핵심] 저장된 모든 상태(VBO 바인딩, 포인터, IBO)를 한 번에 복구
	glBindVertexArray(vaoID);

	// 이제 별도의 glBindBuffer나 glVertexPointer 없이 바로 그리기 가능
	for (GLint i = 0; i < 6; i++) {
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, (GLvoid*)(4 * i));
	}

	glBindVertexArray(0); // 사용 후 해제
	glFlush();
}

void Cleanup() {
	// 1. 함수 포인터 타입 정의 (glGen... 할 때와 동일한 방식)
	PFNGLDELETEBUFFERSPROC glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)wglGetProcAddress("glDeleteBuffers");
	PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)wglGetProcAddress("glDeleteVertexArrays");

	// 2. 실제 삭제
	if (glDeleteBuffers) {
		glDeleteBuffers(1, &vboVertexID);
		glDeleteBuffers(1, &vboColorID);
		glDeleteBuffers(1, &iboID);
	}
	if (glDeleteVertexArrays) {
		glDeleteVertexArrays(1, &vaoID);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 현대적인 OpenGL에서는 VBO(Vertex Buffer Object)와 VAO(Vertex Array Object)를 사용한다.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MyDisplayVA() {
	glClear(GL_COLOR_BUFFER_BIT);
	glFrontFace(GL_CCW); // 깊이검사(8장)를 하지 않고, front face사용
	glEnable(GL_CULL_FACE);
	// 설명 시작
	// 현대에는 이런 함수를 사용하지 않음. 대신 VBO를 사용함
	// 함수 이름보다 정점과 인덱스의 관계를 파악하는 것이 중요
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glColorPointer(3, GL_FLOAT, 0, MyColors);
	glVertexPointer(3, GL_FLOAT, 0, MyVertices);
	// 설명 끝
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(30.0, 1.0, 1.0, 1.0);
	for (GLint i = 0; i < 6; i++)
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &MyVertexList[4 * i]);
	glFlush();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(0, 0);
	Sleep(500);
	glutCreateWindow("OpenGL Drawing Example");

	//HWND hWnd = GetActiveWindow();
	//SetForegroundWindow(hWnd);  // 창을 맨 앞으로
	//SetActiveWindow(hWnd);


	const bool bUseVAO = false; // VAO 사용 여부를 제어하는 플래그 
	if (bUseVAO) {
		SetupScene();
	}

	glClearColor(0.5, 0.5, 0.5, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	if (bUseVAO)
		glutDisplayFunc(MyDisplayVAO);
	else
		glutDisplayFunc(MyDisplayVA);

	glutMainLoop();

	if (bUseVAO) // 강제 종료시에는 MainLoop 탈출전에 종료되어 Cleanup()가 호출되지 않지만, 정상 종료 시에는 리소스 정리를 위해 호출한다.
		Cleanup();

	return 0;
}
