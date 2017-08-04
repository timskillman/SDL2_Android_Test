#pragma once

#include "SDLGL.h"
#include "SMtexture.h"
#include <string>

class SMmaterial {
public:

public:
	SMmaterial();

	void SetTexture(SMtexture* texture) { matTexture = texture; }
	void SetColAmbient(uint32_t colour);
	void SetColAmbient(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
	void SetColEmissive(uint32_t colour);
	void SetColEmissive(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
	void SetColDiffuse(uint32_t colour);
	void SetColDiffuse(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
	void SetColSpecular(uint32_t colour);
	void SetColSpecular(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
	void SetSpecularPower(uint32_t s) { shininess = (float)s / 255.0f; }
	void SetAlphaMode(GLenum mode) { }
	void SetCullMode(int32_t cm) { cullmode = (cm == 1); }
	void makeCurrent();

	enum {
		ALPHA_NONE = 0,
		ALPHA_HALF = 1,
		ALPHA_ADD = 2,
		ALPHA_SUB = 3,
		ALPHA_BLEND = 4,
		ALPHA_DEFAULT = 5
	};

	enum {
		CULL_FRONT,
		CULL_BACK,
		CULL_NONE
	};

	SMtexture* matTexture;
	std::string texName;
	int32_t texRef;

private:
	GLfloat colAmbient[4];
	GLfloat colDiffuse[4];
	GLfloat colEmissive[4];
	GLfloat colSpecular[4];
	float shininess;
	bool cullmode;

};