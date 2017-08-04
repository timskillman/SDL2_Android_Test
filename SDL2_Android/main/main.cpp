#include <SDL.h>

#ifdef __ANDROID__
#include <SDL_opengles.h>
#endif

#ifdef __WINDOWS__
#include <GL/gl.h>
#endif

#define CUBE_SIZE 0.2f

void setViewPort(GLint w, GLint h, GLfloat nearz, GLfloat farz) {
	//Set viewport
	glViewport(0, 0, w, h);

	//Set perspective view ...
	GLfloat aspect = w / h;
	float fov = ((float)h / 2.f) / 800.f;
	GLfloat ymax = nearz * (GLfloat)fov;
	GLfloat ymin = -ymax;
	GLfloat xmin = ymin * aspect;
	GLfloat xmax = -xmin;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustumf(xmin, xmax, ymin, ymax, nearz, farz);
	glDepthRangef(nearz, farz);
}

//Setup a cuboid data
static GLubyte color[8][4] = {
	{ 255, 0, 0, 0 },{ 255, 0, 0, 255 },
	{ 0, 255, 0, 255 },{ 0, 255, 0, 255 },
	{ 0, 255, 0, 255 },{ 255, 255, 255, 255 },
	{ 255, 0, 255, 255 },{ 0, 0, 255, 255 }
};

static GLfloat cube[8][3] = {
	{ CUBE_SIZE, CUBE_SIZE, -CUBE_SIZE },{ CUBE_SIZE, -CUBE_SIZE, -CUBE_SIZE },
	{ -CUBE_SIZE, -CUBE_SIZE, -CUBE_SIZE },{ -CUBE_SIZE, CUBE_SIZE, -CUBE_SIZE },
	{ -CUBE_SIZE, CUBE_SIZE, CUBE_SIZE },{ CUBE_SIZE, CUBE_SIZE, CUBE_SIZE },
	{ CUBE_SIZE, -CUBE_SIZE, CUBE_SIZE },{ -CUBE_SIZE, -CUBE_SIZE, CUBE_SIZE }
};

static GLushort indices[36] =
{ 
	0, 3, 4,  4, 5, 0,  0, 5, 6,  6, 1, 0,  6, 7, 2,  2, 1, 6,
	7, 4, 3,  3, 2, 7,  5, 4, 7,  7, 6, 5,  2, 3, 1,  3, 0, 1 
};

static SDL_Window *window;
static SDL_GLContext glcontext;

///// MAIN /////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		SDL_Log("Unable to initialize SDL");
		return 1;
	}

	//Setup SDL attributes
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);

	//Setup window and gl context
	SDL_DisplayMode mode;
	SDL_GetDesktopDisplayMode(0, &mode);
	window = SDL_CreateWindow("SDL2 Android test", 
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, mode.w, mode.h,
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);
	if (window == NULL) {
		SDL_Log("Unable to initialize SDL window");
		return 1;
	}

	glcontext = SDL_GL_CreateContext(window);
	SDL_GL_MakeCurrent(window, glcontext);

	GLfloat nearz = -1.f;
	GLfloat farz = 100.f;
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	setViewPort(mode.w, mode.h, nearz, farz);

	float rotx = 0; float roty = 0;
	bool quit = false;
	SDL_Event ev;

	while (!quit)
	{
		//process events ...
		while (SDL_PollEvent(&ev)) {
			switch (ev.type) {
				case SDL_QUIT: quit = true; break;
			}
		}

		//clear background to dark blue ...
		glClearColor(0.f, 0.f, 0.2f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Setup model view matrix ...
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(0.f, 0.f, -1.f);  //push model back into scene
		glRotatef(rotx, 1.f, 0, 0);		//rotate on the X axis
		glRotatef(roty, 0, 1.f, 0);		//rotate on the Y axis
		rotx += 0.1f;
		roty += 0.3f;

		//Draw a coloured cube ...
		glColorPointer(4, GL_UNSIGNED_BYTE, 0, color);
		glEnableClientState(GL_COLOR_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, cube);
		glEnableClientState(GL_VERTEX_ARRAY);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, indices);

		SDL_GL_SwapWindow(window);
	}

	SDL_GL_DeleteContext(glcontext);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

