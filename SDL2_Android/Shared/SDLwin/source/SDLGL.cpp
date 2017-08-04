#include "SDLGL.h"

#define MAX_INDEXES 15000

namespace SDLGL {

	static uint16_t lindexes[MAX_INDEXES];

	void SetColStream(GLvoid* cols)
	{
		if (cols != NULL) {
			glColorPointer(4, GL_UNSIGNED_BYTE, 0, cols);
			glEnableClientState(GL_COLOR_ARRAY);
			//glEnable(GL_COLOR_MATERIAL);
		}
		else {
			glDisableClientState(GL_COLOR_ARRAY);
			//glDisable(GL_COLOR_MATERIAL);
		}
	}

	void SetUVStream(GLvoid* uv)
	{
		if (uv != NULL) {
			glTexCoordPointer(2, GL_FLOAT, 0, uv);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		}
		else {
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		}
	}

	void SetNormStream(const GLvoid* normals)
	{
		if (normals != NULL) {
			glNormalPointer(GL_FLOAT, 0, normals);
			glEnableClientState(GL_NORMAL_ARRAY);
		}
		else {
			glDisableClientState(GL_NORMAL_ARRAY);
		}
	}

	void SetVertStream(const GLvoid* verts)
	{
		if (verts != NULL) {
			glVertexPointer(3, GL_FLOAT, 0, verts);
			glEnableClientState(GL_VERTEX_ARRAY);
		}
		else {
			glDisableClientState(GL_VERTEX_ARRAY);
		}
	}

	void DrawPrims(uint16_t mode, GLvoid* indices, int indexNo)
	{
		if (indices == NULL) 
			glDrawElements(mode, indexNo, GL_UNSIGNED_SHORT, &lindexes);
		else
			glDrawElements(mode, indexNo, GL_UNSIGNED_SHORT, indices);
	}

	void SetPerspMul(float perspmul, int32_t w, int32_t h, float nearz, float farz)
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		//GLint vp[4];
		//glGetIntegerv(GL_VIEWPORT, vp);
		//GLfloat aspect = (float)vp[2] / (float)vp[3];

		////Following 3 lines of code make a FOV compatible with gluPerspective from a perspective multiplier...
		////----------------------------------------------------------------------------------------------------
		////float irad1 = 360.f / PI;
		////float fov = (std::atanf(((float)vp[3]*0.5f) /perspmul))*irad1;  //angle = atan((height/2) / perspmul)
		////gluPerspective(perspmul, aspect, SGVars::nearz, SGVars::farz);
		//// /* Perspective(fov, aspect, SGVars::nearz, SGVars::farz); */		//internal routine

		////BUT! ... we can trash the ATAN/TAN and radian conversions to just ...
		//float fov = ((float)vp[3] / 2.f) / perspmul;

		float fov = ((float)h / 2.f) / perspmul;
		GLfloat aspect = (float)w / (float)h;
		GLfloat ymax = nearz * (GLfloat)fov;
		GLfloat ymin = -ymax;
		GLfloat xmin = ymin * aspect;
		GLfloat xmax = -xmin;
#ifdef __WINDOWS__
		glFrustum((GLdouble)xmin, (GLdouble)xmax, (GLdouble)ymin, (GLdouble)ymax, (GLdouble)nearz, (GLdouble)farz);
#endif
#ifdef __ANDROID__
		glFrustumf(xmin, xmax, ymin, ymax, nearz, farz);
#endif
	}

	void SetOrtho(float left, float right, float top, float bottom, float nearz, float farz) 
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
#ifdef __WINDOWS__
		glOrtho(left, right, top, bottom, (GLdouble)nearz, (GLdouble)farz);
#endif
#ifdef __ANDROID__
		glOrthof(left, right, top, bottom, nearz, farz);
#endif
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}

	void SetOrtho(float nearz, float farz)
	{
		//Set whole GL display as 1:1 2D canvas (top-left origin)
		GLint vp[4];
		glGetIntegerv(GL_VIEWPORT, vp);
		SetOrtho(0.f, (float)vp[2], (float)vp[3], 0.f, nearz, farz);
	}
}