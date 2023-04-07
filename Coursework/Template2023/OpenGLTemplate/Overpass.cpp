#include "Overpass.h"

COverpass::COverpass()
{

}

COverpass::~COverpass()
{
	Release();
}

void COverpass::Create(string filename, float textureRepeat)
{
	// loads the textures for the tunnel
	m_tTexture.Load(filename);
	m_tTexture.SetSamplerObjectParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	m_tTexture.SetSamplerObjectParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	m_tTexture.SetSamplerObjectParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
	m_tTexture.SetSamplerObjectParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);

	// creating and binding a VBO
	glGenVertexArrays(1, &m_uiVAO);
	glBindVertexArray(m_uiVAO);
	m_VBO.Create();
	m_VBO.Bind();

	// Vertext Coordinates
	// Setting the vertex coordinates to be used for the VBO
	glm::vec3 v0 = glm::vec3(0, 0, 0);
	glm::vec3 v1 = glm::vec3(10, 0, 0);
	glm::vec3 v2 = glm::vec3(110, 0, 0);
	glm::vec3 v3 = glm::vec3(120, 0, 0);
	glm::vec3 v4 = glm::vec3(10, 20, 0);
	glm::vec3 v5 = glm::vec3(35, 25, 0);
	glm::vec3 v6 = glm::vec3(60, 30, 0);
	glm::vec3 v7 = glm::vec3(85, 25, 0);
	glm::vec3 v8 = glm::vec3(110, 20, 0);
	glm::vec3 v9 = glm::vec3(25, 35, 0);
	glm::vec3 v10 = glm::vec3(50, 40, 0);
	glm::vec3 v11 = glm::vec3(70, 40, 0);
	glm::vec3 v12 = glm::vec3(95, 35, 0);

	glm::vec3 v13 = glm::vec3(0, 0, -20);
	glm::vec3 v14 = glm::vec3(10, 0, -20);
	glm::vec3 v15 = glm::vec3(110, 0, -20);
	glm::vec3 v16 = glm::vec3(120, 0, -20);
	glm::vec3 v17 = glm::vec3(10, 20, -20);
	glm::vec3 v18 = glm::vec3(35, 25, -20);
	glm::vec3 v19 = glm::vec3(60, 30, -20);
	glm::vec3 v20 = glm::vec3(85, 25, -20);
	glm::vec3 v21 = glm::vec3(110, 20, -20);
	glm::vec3 v22 = glm::vec3(25, 35, -20);
	glm::vec3 v23 = glm::vec3(50, 40, -20);
	glm::vec3 v24 = glm::vec3(70, 40, -20);
	glm::vec3 v25 = glm::vec3(95, 35, -20);

	// Normal Vectors
	// setting the normals to be used for the VBO
	glm::vec3 front_normal = glm::vec3(0, 0, 1);
	glm::vec3 back_normal = glm::vec3(0, 0, -1);
	glm::vec3 top_normal = glm::vec3(0, 1, 0);
	glm::vec3 bottom_normal = glm::vec3(0, -1, 0);

	glm::vec3 inside_btm_left_normal = normalize( glm::vec3( glm::cross ((v14 - v1), (v5 - v1)) ));
	glm::vec3 inside_top_left_normal = normalize( glm::vec3( glm::cross ((v18 - v5), (v6 - v5)) ));

	glm::vec3 inside_top_right_normal = normalize( glm::vec3( glm::cross ((v19 - v6), (v7 - v6)) ));
	glm::vec3 inside_btm_right_normal = normalize( glm::vec3( glm::cross ((v20 - v7), (v2 - v7)) ));

	glm::vec3 outside_btm_left_normal = normalize( glm::vec3( glm::cross ((v4 - v0), (v13 - v0)) ));
	glm::vec3 outside_mid_left_normal = normalize( glm::vec3( glm::cross ((v9 - v4), (v17 - v4)) ));
	glm::vec3 outside_top_left_normal = normalize( glm::vec3( glm::cross ((v10- v9), (v22 - v9)) ));

	glm::vec3 outside_top_right_normal = normalize( glm::vec3( glm::cross ((v12- v11), (v24 - v11)) ));
	glm::vec3 outside_mid_right_normal = normalize( glm::vec3( glm::cross ((v8 - v12), (v25 - v12)) ));
	glm::vec3 outside_btm_right_normal = normalize( glm::vec3( glm::cross ((v3 - v8), (v21 - v8)) ));
	

	// Texture Coordinates
	// setting the texture coordinates to be used for the VBO
	glm::vec2 overpassTexCoords[4]
	{
		glm::vec2(0.0f, 0.0f), // 0
		glm::vec2(0.0f, textureRepeat),  // 1
		glm::vec2(textureRepeat, 0.0f),  // 2
		glm::vec2(textureRepeat, textureRepeat)  // 3
	};

	glm::vec2 overpassFrontBackTexCoords[14]
	{
		glm::vec2(1.0f, 0.0f), //3
		glm::vec2(0.92f, 0.32f), //8
		glm::vec2(0.92f, 0.0f),  //2
		glm::vec2(0.79f, 0.58f),  //12
		glm::vec2(0.71f, 0.42f),  //7
		glm::vec2(0.58f, 0.66f),  //11
		glm::vec2(0.5f, 0.5f),  //6

		glm::vec2(0.42f, 0.66f),  //10
		glm::vec2(0.29f, 0.42f),  //5
		glm::vec2(0.21f, 0.58f),  //9
		glm::vec2(0.08f, 0.0f), //1
		glm::vec2(0.08f, 0.32f), //4
		glm::vec2(0.0f, 0.0f), //0

	};

	// Colour
	// setting the colour to be used for the VBO
	glm::vec3 grey = glm::vec3(0.25, 0.25, 0.25);
	glm::vec3 white = glm::vec3(1, 1, 1);

	//////////////////////////////////////////////////////////////////////////
	// Front face 
	m_VBO.AddData(&v3, sizeof(glm::vec3));
	m_VBO.AddData(&overpassFrontBackTexCoords[0], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));

	m_VBO.AddData(&v8, sizeof(glm::vec3));
	m_VBO.AddData(&overpassFrontBackTexCoords[1], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));

	m_VBO.AddData(&v2, sizeof(glm::vec3));
	m_VBO.AddData(&overpassFrontBackTexCoords[2], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));

	m_VBO.AddData(&v12, sizeof(glm::vec3));
	m_VBO.AddData(&overpassFrontBackTexCoords[3], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));

	m_VBO.AddData(&v7, sizeof(glm::vec3));
	m_VBO.AddData(&overpassFrontBackTexCoords[4], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));

	m_VBO.AddData(&v11, sizeof(glm::vec3));
	m_VBO.AddData(&overpassFrontBackTexCoords[5], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));

	m_VBO.AddData(&v6, sizeof(glm::vec3));
	m_VBO.AddData(&overpassFrontBackTexCoords[6], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));

	m_VBO.AddData(&v10, sizeof(glm::vec3));
	m_VBO.AddData(&overpassFrontBackTexCoords[7], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));

	m_VBO.AddData(&v5, sizeof(glm::vec3));
	m_VBO.AddData(&overpassFrontBackTexCoords[8], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));

	m_VBO.AddData(&v9, sizeof(glm::vec3));
	m_VBO.AddData(&overpassFrontBackTexCoords[9], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));
	
	m_VBO.AddData(&v1, sizeof(glm::vec3));
	m_VBO.AddData(&overpassFrontBackTexCoords[10], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));

	m_VBO.AddData(&v4, sizeof(glm::vec3));
	m_VBO.AddData(&overpassFrontBackTexCoords[11], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));

	m_VBO.AddData(&v0, sizeof(glm::vec3));
	m_VBO.AddData(&overpassFrontBackTexCoords[12], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// Back face
	m_VBO.AddData(&v13, sizeof(glm::vec3));
	m_VBO.AddData(&overpassFrontBackTexCoords[0], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));

	m_VBO.AddData(&v17, sizeof(glm::vec3));
	m_VBO.AddData(&overpassFrontBackTexCoords[1], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));

	m_VBO.AddData(&v14, sizeof(glm::vec3));
	m_VBO.AddData(&overpassFrontBackTexCoords[2], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));

	m_VBO.AddData(&v22, sizeof(glm::vec3));
	m_VBO.AddData(&overpassFrontBackTexCoords[3], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));

	m_VBO.AddData(&v18, sizeof(glm::vec3));
	m_VBO.AddData(&overpassFrontBackTexCoords[4], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));

	m_VBO.AddData(&v23, sizeof(glm::vec3));
	m_VBO.AddData(&overpassFrontBackTexCoords[5], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));

	m_VBO.AddData(&v19, sizeof(glm::vec3));
	m_VBO.AddData(&overpassFrontBackTexCoords[6], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));

	m_VBO.AddData(&v24, sizeof(glm::vec3));
	m_VBO.AddData(&overpassFrontBackTexCoords[7], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));

	m_VBO.AddData(&v20, sizeof(glm::vec3));
	m_VBO.AddData(&overpassFrontBackTexCoords[8], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));

	m_VBO.AddData(&v25, sizeof(glm::vec3));
	m_VBO.AddData(&overpassFrontBackTexCoords[9], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));

	m_VBO.AddData(&v15, sizeof(glm::vec3));
	m_VBO.AddData(&overpassFrontBackTexCoords[10], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));

	m_VBO.AddData(&v21, sizeof(glm::vec3));
	m_VBO.AddData(&overpassFrontBackTexCoords[11], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));

	m_VBO.AddData(&v16, sizeof(glm::vec3));
	m_VBO.AddData(&overpassFrontBackTexCoords[12], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// Top face
	m_VBO.AddData(&v10, sizeof(glm::vec3));
	m_VBO.AddData(&overpassTexCoords[0], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));

	m_VBO.AddData(&v11, sizeof(glm::vec3));
	m_VBO.AddData(&overpassTexCoords[2], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));
	
	m_VBO.AddData(&v23, sizeof(glm::vec3));
	m_VBO.AddData(&overpassTexCoords[1], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));

	m_VBO.AddData(&v24, sizeof(glm::vec3));
	m_VBO.AddData(&overpassTexCoords[3], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// Bottom Left face
	m_VBO.AddData(&v0, sizeof(glm::vec3));
	m_VBO.AddData(&overpassTexCoords[0], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));

	m_VBO.AddData(&v13, sizeof(glm::vec3));
	m_VBO.AddData(&overpassTexCoords[2], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));

	m_VBO.AddData(&v1, sizeof(glm::vec3));
	m_VBO.AddData(&overpassTexCoords[1], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));

	m_VBO.AddData(&v14, sizeof(glm::vec3));
	m_VBO.AddData(&overpassTexCoords[3], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// Bottom Right face
	m_VBO.AddData(&v2, sizeof(glm::vec3));
	m_VBO.AddData(&overpassTexCoords[0], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));

	m_VBO.AddData(&v15, sizeof(glm::vec3));
	m_VBO.AddData(&overpassTexCoords[2], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));

	m_VBO.AddData(&v3, sizeof(glm::vec3));
	m_VBO.AddData(&overpassTexCoords[1], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));

	m_VBO.AddData(&v16, sizeof(glm::vec3));
	m_VBO.AddData(&overpassTexCoords[3], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// Inside bottom left face
	m_VBO.AddData(&v1, sizeof(glm::vec3));
	m_VBO.AddData(&overpassTexCoords[0], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));

	m_VBO.AddData(&v14, sizeof(glm::vec3));
	m_VBO.AddData(&overpassTexCoords[2], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));

	m_VBO.AddData(&v5, sizeof(glm::vec3));
	m_VBO.AddData(&overpassTexCoords[1], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));

	m_VBO.AddData(&v18, sizeof(glm::vec3));
	m_VBO.AddData(&overpassTexCoords[3], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// Inside top left face
	m_VBO.AddData(&v5, sizeof(glm::vec3));
	m_VBO.AddData(&overpassTexCoords[0], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));

	m_VBO.AddData(&v18, sizeof(glm::vec3));
	m_VBO.AddData(&overpassTexCoords[2], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));

	m_VBO.AddData(&v6, sizeof(glm::vec3));
	m_VBO.AddData(&overpassTexCoords[1], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));

	m_VBO.AddData(&v19, sizeof(glm::vec3));
	m_VBO.AddData(&overpassTexCoords[3], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// Inside top right face
	m_VBO.AddData(&v6, sizeof(glm::vec3));
	m_VBO.AddData(&overpassTexCoords[0], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));

	m_VBO.AddData(&v19, sizeof(glm::vec3));
	m_VBO.AddData(&overpassTexCoords[2], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));

	m_VBO.AddData(&v7, sizeof(glm::vec3));
	m_VBO.AddData(&overpassTexCoords[1], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));

	m_VBO.AddData(&v20, sizeof(glm::vec3));
	m_VBO.AddData(&overpassTexCoords[3], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// Inside bottom right face
	m_VBO.AddData(&v7, sizeof(glm::vec3));
	m_VBO.AddData(&overpassTexCoords[0], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));

	m_VBO.AddData(&v20, sizeof(glm::vec3));
	m_VBO.AddData(&overpassTexCoords[2], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));

	m_VBO.AddData(&v2, sizeof(glm::vec3));
	m_VBO.AddData(&overpassTexCoords[1], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));

	m_VBO.AddData(&v15, sizeof(glm::vec3));
	m_VBO.AddData(&overpassTexCoords[3], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// Outside bottom left face
	m_VBO.AddData(&v13, sizeof(glm::vec3));
	m_VBO.AddData(&overpassTexCoords[0], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));

	m_VBO.AddData(&v0, sizeof(glm::vec3));
	m_VBO.AddData(&overpassTexCoords[2], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));

	m_VBO.AddData(&v17, sizeof(glm::vec3));
	m_VBO.AddData(&overpassTexCoords[1], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));

	m_VBO.AddData(&v4, sizeof(glm::vec3));
	m_VBO.AddData(&overpassTexCoords[3], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// Outside middle left face
	m_VBO.AddData(&v17, sizeof(glm::vec3));
	m_VBO.AddData(&overpassTexCoords[0], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));

	m_VBO.AddData(&v4, sizeof(glm::vec3));
	m_VBO.AddData(&overpassTexCoords[2], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));

	m_VBO.AddData(&v22, sizeof(glm::vec3));
	m_VBO.AddData(&overpassTexCoords[1], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));

	m_VBO.AddData(&v9, sizeof(glm::vec3));
	m_VBO.AddData(&overpassTexCoords[3], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// Outside top left face
	m_VBO.AddData(&v22, sizeof(glm::vec3));
	m_VBO.AddData(&overpassTexCoords[0], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));

	m_VBO.AddData(&v9, sizeof(glm::vec3));
	m_VBO.AddData(&overpassTexCoords[2], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));

	m_VBO.AddData(&v23, sizeof(glm::vec3));
	m_VBO.AddData(&overpassTexCoords[1], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));

	m_VBO.AddData(&v10, sizeof(glm::vec3));
	m_VBO.AddData(&overpassTexCoords[3], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// Outside top right face
	m_VBO.AddData(&v24, sizeof(glm::vec3));
	m_VBO.AddData(&overpassTexCoords[0], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));

	m_VBO.AddData(&v11, sizeof(glm::vec3));
	m_VBO.AddData(&overpassTexCoords[2], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));

	m_VBO.AddData(&v25, sizeof(glm::vec3));
	m_VBO.AddData(&overpassTexCoords[1], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));

	m_VBO.AddData(&v12, sizeof(glm::vec3));
	m_VBO.AddData(&overpassTexCoords[3], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// Outside middle right face
	m_VBO.AddData(&v25, sizeof(glm::vec3));
	m_VBO.AddData(&overpassTexCoords[0], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));

	m_VBO.AddData(&v12, sizeof(glm::vec3));
	m_VBO.AddData(&overpassTexCoords[2], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));

	m_VBO.AddData(&v21, sizeof(glm::vec3));
	m_VBO.AddData(&overpassTexCoords[1], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));

	m_VBO.AddData(&v8, sizeof(glm::vec3));
	m_VBO.AddData(&overpassTexCoords[3], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// Outside bottom right face
	m_VBO.AddData(&v21, sizeof(glm::vec3));
	m_VBO.AddData(&overpassTexCoords[0], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));

	m_VBO.AddData(&v8, sizeof(glm::vec3));
	m_VBO.AddData(&overpassTexCoords[2], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));

	m_VBO.AddData(&v16, sizeof(glm::vec3));
	m_VBO.AddData(&overpassTexCoords[1], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));

	m_VBO.AddData(&v3, sizeof(glm::vec3));
	m_VBO.AddData(&overpassTexCoords[3], sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&grey, sizeof(glm::vec3));
	//////////////////////////////////////////////////////////////////////////


	// Upload data to GPU
	m_VBO.UploadDataToGPU(GL_STATIC_DRAW);
	// set stride length equal to length of attributes (11)
	GLsizei stride = 3 * sizeof(glm::vec3) + sizeof(glm::vec2);

	// Vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, 0);

	// Texture coordinates
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)sizeof(glm::vec3));

	// Normal vectors
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(glm::vec3) + sizeof(glm::vec2)));

	// Colours
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(glm::vec3) + sizeof(glm::vec2) + sizeof(glm::vec3)));

}

void COverpass::Render()
{
	glBindVertexArray(m_uiVAO);
	m_tTexture.Bind();
	
	// Call glDrawArrays to render a face
	// Front face
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 13);
	// Back face
	glDrawArrays(GL_TRIANGLE_STRIP, 13, 13);
	// Top face
	glDrawArrays(GL_TRIANGLE_STRIP, 26, 4);
	// Bottom right face
	glDrawArrays(GL_TRIANGLE_STRIP, 30, 4);
	// Bottom left face
	glDrawArrays(GL_TRIANGLE_STRIP, 34, 4);
	// Inside bottom left face
	glDrawArrays(GL_TRIANGLE_STRIP, 38, 4);
	// Inside top left face
	glDrawArrays(GL_TRIANGLE_STRIP, 42, 4);
	// Inside top right face
	glDrawArrays(GL_TRIANGLE_STRIP, 46, 4);
	// Inside bottom right face
	glDrawArrays(GL_TRIANGLE_STRIP, 50, 4);
	// Outside bottom left face
	glDrawArrays(GL_TRIANGLE_STRIP, 54, 4);
	// Outside middle left face
	glDrawArrays(GL_TRIANGLE_STRIP, 58, 4);
	// Outside top left face
	glDrawArrays(GL_TRIANGLE_STRIP, 62, 4);
	// Outside top right face
	glDrawArrays(GL_TRIANGLE_STRIP, 66, 4);
	// Outside middle right face
	glDrawArrays(GL_TRIANGLE_STRIP, 70, 4);
	// Outside bottom right face
	glDrawArrays(GL_TRIANGLE_STRIP, 74, 4);
	
}

void COverpass::Release()
{
	m_tTexture.Release();
	glDeleteVertexArrays(1, &m_uiVAO);
	m_VBO.Release();
}
