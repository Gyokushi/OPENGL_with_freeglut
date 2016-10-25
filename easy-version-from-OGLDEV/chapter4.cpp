#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <string.h>
#include "ogldev_util.h"
#include "ogldev_math_3d.h"
#include <Windows.h>

GLuint VBO;
static void CreateVertexBuffer();
static void Render();
static void InitializeGlutCallBacks();
static void AddShader(GLuint, const char*, GLenum);
static void CompileShaders();
const char* pVSFileName = "shader.vs";
const char* pFSFileName = "shader.fs";



int main(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(640, 320);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Chapter4");
	InitializeGlutCallBacks();
	glutDisplayFunc(Render);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	
	GLenum res = glewInit();
	if (res != GLEW_OK) {
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		Sleep(20000);
		return -1;
	}

	CreateVertexBuffer();
	CompileShaders();
	glutMainLoop();
	return 0;
}

static void AddShader(GLuint ShaderProgram,const char* pShaderText, GLenum ShaderType) {
	GLuint ShaderObj = glCreateShader(ShaderType);
	if (ShaderObj == 0) {
		fprintf(stderr, "Error: creating shader type %d \n", ShaderType);
		Sleep(20000);
		exit(0);
	}

	const GLchar* p[1];
	p[0] = pShaderText;
	GLint Lengths[1];
	Lengths[0] = strlen(pShaderText);
	glShaderSource(ShaderObj, 1, p, Lengths);
	glCompileShader(ShaderObj);

	GLint success;
	glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);

	if (!success) {
		GLchar InfoLog[1024];
		glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
		fprintf(stderr, "Error compiling shader type %d: '%s' \n", ShaderType, InfoLog);
		Sleep(20000);
		exit(1);
	}

	glAttachShader(ShaderProgram, ShaderObj);
}

static void CompileShaders() {
	GLuint ShaderProgram = glCreateProgram();

	if (ShaderProgram == 0) {
		fprintf(stderr, "Error: creating Shader Program\n");
		Sleep(20000);
		exit(1);
	}

	string vs, fs;
	if (!ReadFile(pVSFileName, vs)) {
		fprintf(stderr,"Error: Cannot read file"+*pVSFileName);
		exit(1);
	}

	if (!ReadFile(pFSFileName, fs)) {
		fprintf(stderr, "Error: Cannot read file" + *pFSFileName);
		exit(1);
	}

	AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);
	AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

	GLint success = 0;
	GLchar ErrorLog[1024] = { 0 };
	glLinkProgram(ShaderProgram);
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ShaderProgram,sizeof(ErrorLog),NULL,ErrorLog);
		fprintf(stderr, "Error: Linking shader program '%s' \n", ErrorLog);
		exit(1);
	}

	glUseProgram(ShaderProgram);
}

static void InitializeGlutCallBacks() {
	glutDisplayFunc(Render);
}

static void CreateVertexBuffer() {
	Vector3f Vertice[3];
	Vertice[0] = Vector3f(0.0f,-1.0f,0.0f);
	Vertice[1] = Vector3f(1.0f,1.0f,0.0f);
	Vertice[2] = Vector3f(-1.0f,1.0f,0.0f);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertice), Vertice, GL_STATIC_DRAW);
}

static void Render() {
	glClear(GL_COLOR_BUFFER_BIT);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);

	glutSwapBuffers();
}
