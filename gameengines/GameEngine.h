#pragma once
#include <glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include "triangleRenderer.h"

namespace GE {
	class GameEngine {
	public:
		GameEngine();

		virtual ~GameEngine();

		bool init();
		bool keep_running();
		void update();
		void draw();
		void shutdown();

		void setwindowtitle(const char*);


	
	private:
		SDL_Window* window;

		SDL_GLContext glContext;

		triangleRenderer* triangle;
	};

	void display_info_message(const char*);
}