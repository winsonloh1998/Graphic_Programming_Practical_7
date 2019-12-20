#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#pragma comment (lib, "GLU32.lib")
#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "Practical 7"

//Step 1: Variable declaration
GLuint texture = 0;
BITMAP BMP;
HBITMAP hBMP = NULL;
LPCSTR imageFileName = "brick.bmp";
int questionNo = 1;

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
			PostQuitMessage(0);
		else if (wParam == 'X')
			glRotatef(1, 1, 0, 0);
		else if (wParam == 'Y')
			glRotatef(1, 0, 1, 0);
		else if (wParam == 'Z')
			glRotatef(1, 0, 0, 1);
		else if (wParam == '1')
			questionNo = 1;
		else if (wParam == '2')
			questionNo = 2;
		else if (wParam == 'C')
			imageFileName = "creeper.bmp";
		else if (wParam == 'B')
			imageFileName = "brick.bmp";
		else if (wParam == 'M')
			imageFileName = "metal.bmp";
		else if (wParam == 'S')
			imageFileName = "skeleton.bmp";
		else if (wParam == 'W')
			imageFileName = "wood.bmp";
		break;
	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

//--------------------------------------------------------------------

bool initPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 0;

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------

void drawPyramid() {
	//Basement
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1);
	glVertex3f(-0.5, -0.5, 0.5);
	glTexCoord2f(1, 1);
	glVertex3f(0.5, -0.5, 0.5);
	glTexCoord2f(1, 0);
	glVertex3f(0.5, -0.5, -0.5);
	glTexCoord2f(0, 0);
	glVertex3f(-0.5, -0.5, -0.5);
	glEnd();

	//4 Triangles
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex3f(-0.5, -0.5, -0.5);
	glTexCoord2f(1, 0);
	glVertex3f(0.0, 0.0, 0.0);
	glTexCoord2f(1, 1);
	glVertex3f(-0.5, -0.5, 0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex3f(-0.5, -0.5, 0.5);
	glTexCoord2f(1, 0);
	glVertex3f(0.0, 0.0, 0.0);
	glTexCoord2f(1, 1);
	glVertex3f(0.5, -0.5, 0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex3f(0.5, -0.5, 0.5);
	glTexCoord2f(1, 0);
	glVertex3f(0.0, 0.0, 0.0);
	glTexCoord2f(1, 1);
	glVertex3f(0.5, -0.5, -0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex3f(0.5, -0.5, -0.5);
	glTexCoord2f(1, 0);
	glVertex3f(0.0, 0.0, 0.0);
	glTexCoord2f(1, 1);
	glVertex3f(-0.5, -0.5, -0.5);
	glEnd();
}

void drawCube(float s) {

	//front
	//See x z
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 1.0);
	glVertex3f(0.0f, 0.0f, s);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(s, 0.0f, s);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(s, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();

	//left
	//See y z
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0);
	glVertex3f(0.0f, s, 0.0f);
	glTexCoord2f(1.0f, 1.0);
	glVertex3f(0.0f, s, s);
	glTexCoord2f(0.0f, 1.0);
	glVertex3f(0.0f, 0.0f, s);
	glEnd();

	//top
	//See x y
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0);
	glVertex3f(0.0f, 0.0f, s);
	glTexCoord2f(0.0f, 1.0);
	glVertex3f(0.0f, s, s);
	glTexCoord2f(1.0f, 1.0);
	glVertex3f(s, s, s);
	glTexCoord2f(1.0f, 0.0);
	glVertex3f(s, 0.0f, s);
	glEnd();

	//right
	//See y z
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 1.0);
	glVertex3f(s, 0.0f, s);
	glTexCoord2f(1.0f, 1.0);
	glVertex3f(s, s, s);
	glTexCoord2f(1.0f, 0.0);
	glVertex3f(s, s, 0.0f);
	glTexCoord2f(0.0f, 0.0);
	glVertex3f(s, 0.0f, 0.0f);
	glEnd();

	//Bottom
	//See x y 
	glBegin(GL_POLYGON);
	glTexCoord2f(1.0f, 0.0);
	glVertex3f(s, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0);
	glVertex3f(0.0f, s, 0.0f);
	glTexCoord2f(1.0f, 1.0);
	glVertex3f(s, s, 0.0f);
	glEnd();

	//back
	//See x z 
	glBegin(GL_POLYGON);
	glTexCoord2f(1.0f, 0.0);
	glVertex3f(s, s, 0.0f);
	glTexCoord2f(1.0f, 1.0);
	glVertex3f(s, s, s);
	glTexCoord2f(0.0f, 1.0);
	glVertex3f(0.0f, s, s);
	glTexCoord2f(0.0f, 0.0);
	glVertex3f(0.0f, s, 0.0f);
	glEnd();
}

void display(LPCSTR textureFile) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glClearColor(1.0, 1.0, 1.0, 0.0);

	if (hBMP != NULL)
	{
		glDisable(GL_TEXTURE_2D);
		DeleteObject(hBMP);
		glDeleteTextures(1, &texture);
	}

	//Step 3: Initialize texture info
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		textureFile, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);


	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	if (questionNo == 1)
		drawPyramid();
	else if (questionNo == 2)
		drawCube(0.5);

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
}
//--------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WindowProcedure;
	wc.lpszClassName = WINDOW_TITLE;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc)) return false;

	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
		NULL, NULL, wc.hInstance, NULL);

	//--------------------------------
	//	Initialize window for OpenGL
	//--------------------------------

	HDC hdc = GetDC(hWnd);

	//	initialize pixel format for the window
	initPixelFormat(hdc);

	//	get an openGL context
	HGLRC hglrc = wglCreateContext(hdc);

	//	make context current
	if (!wglMakeCurrent(hdc, hglrc)) return false;

	//--------------------------------
	//	End initialization
	//--------------------------------

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		display(imageFileName);

		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------
