#include "ogldev_math_3d.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <Windows.h>

GLuint VBO;
static void Render();
static void CreateVertexBuffer();

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("chapter3");
	glutDisplayFunc(Render);

	GLenum res = glewInit();
	if (res != GLEW_OK) {
		fprintf(stderr, "Error: '%s' \n", glewGetErrorString(res));
		Sleep(2000);
		return 1;
	}
	CreateVertexBuffer();
	glClearColor(0, 0, 0, 0);
	glutMainLoop();
	return 0;
}

static void CreateVertexBuffer() {
	Vector3f Vertice[6];
	Vertice[0] = Vector3f(1.0f, 1.0f, 0.0f);
	Vertice[1] = Vector3f(-1.0f, 1.0f, 0.0f);
	Vertice[2] = Vector3f(0.0f, -1.0f, 0.0f);

	Vertice[3] = Vector3f(0.0f, 1.0f, 0.0f);
	Vertice[4] = Vector3f(1.0f, -1.0f, 0.0f);
	Vertice[5] = Vector3f(-1.0f, -1.0f, 0.0f);


	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertice), Vertice, GL_STATIC_DRAW);
}

static void Render() {
	glClear(GL_COLOR_BUFFER_BIT);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(0);
	glutSwapBuffers();
	glFlush();
}
