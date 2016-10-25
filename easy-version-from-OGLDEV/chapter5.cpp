#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "ogldev_math_3d.h"
#include "ogldev_util.h"
#include <string.h>
#include <Windows.h>

GLuint VBO;
GLuint gScaleLocation;
const char* pVSFilename = "shader1.vs";
const char* pFSFilename = "shader1.fs";
static void CreateVertexBuffer();
static void InitGlutCallbacks();
static void Render();
static void AddShader(GLuint,const char*,GLenum);
static void CompileShaders();

int main(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("chapter5");

	InitGlutCallbacks();
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	GLenum res = glewInit();
	if (res != GLEW_OK) {
		fprintf(stderr, "Error: '%s' \n", glewGetErrorString(res));
		Sleep(2000);
		return 0;
	}

	CreateVertexBuffer();

	CompileShaders();



	glutMainLoop();

	return 0;
}

static void InitGlutCallbacks() {
	glutDisplayFunc(Render);
	glutIdleFunc(Render);
}

static void CreateVertexBuffer() {
	Vector3f Vertices[3];
	Vertices[0] = Vector3f(0.0f, -1.0f, 0.0f);
	Vertices[1] = Vector3f(1.0f, 1.0f, 0.0f);
	Vertices[2] = Vector3f(-1.0f, 1.0f, 0.0f);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
}

static void Render() {
	static float scale = 0.0f;
	scale += 0.001f;
	glUniform1f(gScaleLocation, sinf(scale));
	glClear(GL_COLOR_BUFFER_BIT);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);

	glutSwapBuffers();
}

static void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType) {
	GLuint ShaderObj = glCreateShader(ShaderType);
	if (ShaderObj == 0) {
		fprintf(stderr, "Error: Cannot create Shader Type %d \n", ShaderType);
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
	if (!ReadFile(pVSFilename, vs)) {
		fprintf(stderr, "Error: Cannot read file" + *pVSFilename);
		Sleep(20000);
		exit(-1);
	}
	if (!ReadFile(pFSFilename, fs)) {
		fprintf(stderr, "Error: Cannot read file" + *pFSFilename);
		Sleep(20000);
		exit(-1);
	}

	AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);
	AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

	GLint success = 0;
	GLchar InfoLog[1024] = { 0 };
	glLinkProgram(ShaderProgram);
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &success);

	if (!success) {
		glGetProgramInfoLog(ShaderProgram, 1024, NULL, InfoLog);
		fprintf(stderr, "Error: Linking shader program '%s' \n", InfoLog);
		Sleep(20000);
		exit(1);
	}

	glUseProgram(ShaderProgram);
	gScaleLocation = glGetUniformLocation(ShaderProgram, "gScale");
	assert(gScaleLocation != 0xFFFFFFFF);
}
