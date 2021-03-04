#include "GameEngine.h"
#include <iostream>

using namespace std;

namespace GE {

	GLfloat vertexData[] = {
		-1.0f,0.0f,
		1.0f, 0.0f,
		0.0f,1.0f
	};

	TriangleRenderer::TriangleRenderer() { }

	TriangleRenderer::~TriangleRenderer() { }

	void displayShaderCompilerError(GLuint shaderid) {

		GLint MsgLen = 0;

		glGetShaderiv(shaderid, GL_INFO_LOG_LENGTH, &MsgLen);

		if (MsgLen > 1) {
			GLchar* Msg = new GLchar[MsgLen + 1];

			glGetShaderInfoLog(shaderid, MsgLen, NULL, Msg);

			cerr << "Error compiling shader" << Msg << endl;

			delete[] Msg;
		}
	}

	void TriangleRenderer::init() {
		//shader code
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		const GLchar* V_ShaderCode[] = {
			"#version 140\n"
			"in vec2 vertexPos2D:\n"
			"void main(){\n"
			"gl_Position = vec4 (vertexPos2D.x,vertexPos.2D.y,0,1);\n"
			"}\n"
		};

		glShaderSource(vertexShader, 1, V_ShaderCode, NULL);

		glCompileShader(vertexShader);

		GLint isShaderCompiledOK = GL_FALSE;

		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isShaderCompiledOK);

		if (isShaderCompiledOK != GL_TRUE) {
			cerr << "unable to compile vertex shader" << endl;

			displayShaderCompilerError(vertexShader);

			return;
		}

		//fragment shader code 
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		const GLchar* F_ShaderCode[] = {
			"#version 140\n"
			"out vec4 fragmentColor:\n"
			"void main()\n"
			"{\n"
			"fragmentColour = vec4(1.0,0.0,0.0, 1.0);\n"
			"}\n"
		};

		glShaderSource(fragmentShader, 1, F_ShaderCode, NULL);

		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isShaderCompiledOK);

		if (isShaderCompiledOK != GL_TRUE) {
			cerr << "unable to compile fragment shader" << endl;

			displayShaderCompilerError(fragmentShader);

			return;
		}

		programId = glCreateProgram();

		glAttachShader(programId, vertexShader);
		glAttachShader(programId, fragmentShader);

		glLinkProgram(programId);

		GLint isProgramLinked = GL_FALSE;
		glGetProgramiv(programId, GL_LINK_STATUS, &isProgramLinked);
		if (isProgramLinked != GL_TRUE) {
			cerr << "failed to link program" << endl;
		}

		vertexPos2DLocation = glGetAttribLocation(programId, "vertexPos2D");
		if (vertexPos2DLocation == -1) {
			cerr << "problem getting vertex2DPos" << endl;
		}

		glGenBuffers(1, &vboTriangle);
		glBindBuffer(GL_ARRAY_BUFFER, vboTriangle);

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	}

	void TriangleRenderer::update(){ }

	void TriangleRenderer::draw() {

		glUseProgram(programId);

		glVertexAttribPointer(vertexPos2DLocation, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), nullptr);

		glEnableVertexAttribArray(vertexPos2DLocation);

		glBindBuffer(GL_ARRAY_BUFFER, vboTriangle);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glDisableVertexAttribArray(vertexPos2DLocation);

		glUseProgram(0);
	}

	void TriangleRenderer::destroy() {
		glDeleteProgram(programId);

		glDeleteBuffers(1, &vboTriangle);
	}
}

