#include "GameEngine.h"
#include "triangleRenderer.h"
#include <iostream>
using namespace GE;

using namespace std;

TriangleRenderer* triangle;

namespace GE {

	GameEngine::GameEngine() {

	}

	GameEngine::~GameEngine() {

	}

	bool GameEngine::init() {
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			cerr << "Unavailable to initialise SDL! SDL error: " << SDL_GetError() << endl;

			return false;
		}

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		window = SDL_CreateWindow("SDL OpenGL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

		if (window == nullptr) {
			cerr << "unable to create window! SDL error!: " << SDL_GetError() << endl;

			return false;
		}

		glContext = SDL_GL_CreateContext(window);

		if (glContext == nullptr) {
			cerr << "SDL could not create GL context! SDL error: " << SDL_GetError() << endl;

			return false;
		}

		GLenum status = glewInit();
		if (status != GLEW_OK) {
			cerr << "error initialising GLEW! Error: " << glewGetErrorString(status) << endl;

			return false;
		}

		if (SDL_GL_SetSwapInterval(1) != 0) {
			cerr << "Warning: unable to set VSync! Error: " << SDL_GetError() << endl;

			return false;
		}

		triangle = new TriangleRenderer();
		triangle->init();

		return true;
	}

	bool GameEngine::keep_running() {
		SDL_PumpEvents();

		SDL_Event evt;

		if (SDL_PeepEvents(&evt, 1, SDL_GETEVENT, SDL_QUIT, SDL_QUIT)) {
			return false;
		}
		return true;
	}

	void GameEngine::update() {
		triangle->update();
	}

	void GameEngine::draw() {
		glClearColor(0.392f, 0.584f, 0.929f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBegin(GL_TRIANGLES);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex2f(-1.0f, 0.0f);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex2f(1.0f, 0.0f);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex2f(0.0f, 1.0f);

			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex2f(-1.0f, 0.0f);
			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex2f(0.0f, -1.0f);
			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex2f(1.0f, 0.0f);
		glEnd();

		triangle->draw();

		SDL_GL_SwapWindow(window);
	}

	void GameEngine::shutdown() {
		SDL_DestroyWindow(window);

		window = nullptr;

		triangle->destroy();

		SDL_Quit();
	}

	void GameEngine::setwindowtitle(const char* new_title) {
		SDL_SetWindowTitle(window, new_title);
	}

	void display_info_message(const char* msg) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Xenas Game Engine", msg, nullptr);
	}


}