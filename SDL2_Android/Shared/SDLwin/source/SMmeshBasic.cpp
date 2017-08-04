#include "SMmeshBasic.h"

void SMmeshBasic::render()
{
	SetUVStream(NULL);
	SetColStream(NULL);
	SetNormStream(&normals.front());
	SetVertStream(&verts.front());
	DrawPrims(mode, &indices.front(), indexes);
}