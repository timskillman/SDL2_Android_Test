#include "SMmaterial.h"

//----- SMmaterial -----------------------------------------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Materials should work with a combination of glMaterial and glColor
//  glMaterial effects (Ambient, Diffuse, Specular, Emissive and shadow) when lighting is on
//  They have no effect when lighting is off.
//
//  glColor ALWAYS affects the colour whether lighting is on or off.
//
////////////////////////////////////////////////////////////////////////////////////////////////

SMmaterial::SMmaterial() : matTexture(NULL), shininess(0.2f)
{
	colAmbient[0] = colAmbient[1] = colAmbient[2] = 0.3f; colAmbient[3] = 1.f;
	colDiffuse[0] = colDiffuse[1] = colDiffuse[2] = colDiffuse[3] = 1.f;
	colSpecular[0] = colSpecular[1] = colSpecular[2] = 0.3f; colSpecular[3] = 1.f;
	colEmissive[0] = colEmissive[1] = colEmissive[2] = 0.0f; colEmissive[3] = 1.f;
}

void SMmaterial::SetColAmbient(uint32_t colour)
{
	colAmbient[0] = (GLfloat)(colour & 255) / 255.f;
	colAmbient[1] = (GLfloat)((colour >> 8) & 255) / 255.f;
	colAmbient[2] = (GLfloat)((colour >> 16) & 255) / 255.f;
	colAmbient[3] = 1.f; // (colour >> 24) & 255;
}

void SMmaterial::SetColAmbient(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	colAmbient[0] = (GLfloat)r / 255.f;
	colAmbient[1] = (GLfloat)g / 255.f;
	colAmbient[2] = (GLfloat)b / 255.f;
	colAmbient[3] = (GLfloat)a / 255.f;
}

void SMmaterial::SetColEmissive(uint32_t colour)
{
	colEmissive[0] = (GLfloat)(colour & 255) / 255.f;
	colEmissive[1] = (GLfloat)((colour >> 8) & 255) / 255.f;
	colEmissive[2] = (GLfloat)((colour >> 16) & 255) / 255.f;
	colEmissive[3] = 1.f; // (GLfloat)((colour >> 24) & 255) / 255.f;
}

void SMmaterial::SetColEmissive(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	colEmissive[0] = (GLfloat)r / 255.f;
	colEmissive[1] = (GLfloat)g / 255.f;
	colEmissive[2] = (GLfloat)b / 255.f;
	colEmissive[3] = (GLfloat)a / 255.f;
}

void SMmaterial::SetColDiffuse(uint32_t colour)
{
	colDiffuse[0] = (GLfloat)(colour & 255) / 255.f;
	colDiffuse[1] = (GLfloat)((colour >> 8) & 255) / 255.f;
	colDiffuse[2] = (GLfloat)((colour >> 16) & 255) / 255.f;
	colDiffuse[3] = (GLfloat)((colour >> 24) & 255) / 255.f;
}

void SMmaterial::SetColDiffuse(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	colDiffuse[0] = (GLfloat)r / 255.f;
	colDiffuse[1] = (GLfloat)g / 255.f;
	colDiffuse[2] = (GLfloat)b / 255.f;
	colDiffuse[3] = (GLfloat)a / 255.f;
}

void SMmaterial::SetColSpecular(uint32_t colour)
{
	colSpecular[0] = (GLfloat)(colour & 255) / 255.f;
	colSpecular[1] = (GLfloat)((colour >> 8) & 255) / 255.f;
	colSpecular[2] = (GLfloat)((colour >> 16) & 255) / 255.f;
	colSpecular[3] = 1.f; // (colour >> 24) & 255;
}

void SMmaterial::SetColSpecular(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	colSpecular[0] = (GLfloat)r / 255.f;
	colSpecular[1] = (GLfloat)g / 255.f;
	colSpecular[2] = (GLfloat)b / 255.f;
	colSpecular[3] = (GLfloat)a / 255.f;
}

void SMmaterial::makeCurrent()
{
	//glEnable(GL_COLOR_MATERIAL); //Do not enable if using glMaterial's

	//glDisableClientState(GL_COLOR_ARRAY);
	//glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	//glDisableClientState(GL_NORMAL_ARRAY);

	//glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	//glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);

	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHT1);
	//glColor3f(0, 0, 0);

	//glMaterialfv(GL_FRONT, GL_AMBIENT, colAmbient);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, colDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, colSpecular);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, colEmissive);
	//float col[4];
	//col[0] = colAmbient[0] + colDiffuse[0];
	//col[1] = colAmbient[1] + colDiffuse[1];
	//col[2] = colAmbient[2] + colDiffuse[2];
	//col[3] = colAmbient[3] + colDiffuse[3];
	//glColor4fv(colAmbient);
	glColor4f(colAmbient[0], colAmbient[1], colAmbient[2], colAmbient[3]);

	if (matTexture) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture(GL_TEXTURE_2D, matTexture->textureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glEnable(GL_TEXTURE_2D);
	}
	else glDisable(GL_TEXTURE_2D);

}
