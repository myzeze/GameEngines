#pragma once

#include <glew.h>
#include <SDL.h>
#include <SDL_opengl.h>

namespace GE {
	class triangleRenderer {
	public:
		triangleRenderer();

		virtual ~triangleRenderer();

		void init();

		void update();

		void draw();

		void destroy();

	private:
		GLuint programId;

		GLint vertexPos2DLocation;

		GLuint vboTriangle;
	};
}
