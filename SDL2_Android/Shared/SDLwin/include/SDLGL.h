#pragma once

#include <SDL.h>
//#include <SDL_image.h>
#include "SDL_syswm.h"
#include "Vectorf.h"

#ifdef __IPHONEOS__
#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>
#endif /* __IPHONEOS__ */

#ifdef __ANDROID__
#include <SDL_opengles.h>
#endif /* __ANDROID__ */

#ifdef __WINDOWS__
#include <GL/gl.h>
#endif /* __WINDOWS__ */

#define SM_NEARZ 1.0f
#define SM_FARZ 2500.0f

namespace SDLGL
{
	void SetColStream(GLvoid* cols);
	void SetUVStream(GLvoid* uv);
	void SetNormStream(const GLvoid* normals);
	void SetVertStream(const GLvoid* verts);
	void DrawPrims(uint16_t mode, GLvoid* indices, int indexNo);
	void SetPerspMul(float perspmul, int32_t w, int32_t h, float nearz = SM_NEARZ, float farz = SM_FARZ);
	void SetOrtho(float left, float right, float top, float bottom, float nearz = SM_NEARZ, float farz = SM_FARZ);
	void SetOrtho(float nearz = SM_NEARZ, float farz = SM_FARZ);
};

