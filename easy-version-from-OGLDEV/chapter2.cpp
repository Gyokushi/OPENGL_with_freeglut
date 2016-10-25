#include "ogldev_math_3d.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <iostream>
#include <Windows.h>

void Render();
GLuint VBO;
void CreateVertexBuffer();
int main(int argc, char** argv) {

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(640, 320);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Chapter2");
	glClearColor(0, 0, 0, 0);
	glutDisplayFunc(Render);

	GLenum result = glewInit();
	if (result != GLEW_OK) {
		fprintf(stderr,"ERROR:'%s'\n ",glewGetErrorString(result));
		Sleep(2000);
		return 1;
	}
	CreateVertexBuffer();
	std::cout << "Hello again! You perform well so far!" << std::endl;

	glutMainLoop();
	return 0;
}
static void Render() {
	glClear(GL_COLOR_BUFFER_BIT);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3,GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_POINTS, 0, 1);
	glDisableVertexAttribArray(0);
	glutSwapBuffers();
}


void CreateVertexBuffer() {
	Vector3f Vertice[1];
	Vertice[0] = Vector3f(0, 0, 0);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertice), Vertice, GL_STATIC_DRAW);
}
