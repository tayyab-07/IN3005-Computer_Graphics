#pragma once

#include "Common.h"
#include "Texture.h"
#include "VertexBufferObject.h"

// Class for generating a tunnel
class CTunnel
{
public:
	//constructor and destructor for the tunnel
	CTunnel();
	~CTunnel();

	//funtions for the tunnel
	void Create(string filename, float fTextureRepeat);
	void Render();
	void Release();

private:

	GLuint m_uiVAO;
	CVertexBufferObject m_VBO;
	CTexture m_tTexture;
};
