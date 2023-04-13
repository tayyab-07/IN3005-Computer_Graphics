#pragma once

#include "Common.h"
#include "Texture.h"
#include "VertexBufferObject.h"

// Class for generating an overpass
class COverpass
{
public:
	//constructor and destructor for the overpass
	COverpass();
	~COverpass();

	//funtions for the overpass
	void Create(string filename, float fTextureRepeat);
	void Render();
	void Release();

private:

	GLuint m_uiVAO;
	CVertexBufferObject m_VBO;
	CTexture m_tTexture;
};