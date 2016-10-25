#include <iostream>
#include <GL/freeglut.h>

void Render();

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Hello World!!!");

	std::cout << "Thanks god T^T" << std::endl;
	glutDisplayFunc(Render);
	glClearColor(0, 0, 0, 0);
	glutMainLoop();
	return  0;
}

void Render() {
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
}