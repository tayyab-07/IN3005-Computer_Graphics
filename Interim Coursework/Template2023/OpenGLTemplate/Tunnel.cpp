#include "Tunnel.h"

CTunnel::CTunnel()
{

}

CTunnel::~CTunnel()
{
	Release();
}

void CTunnel::Create(string filename)
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
	glm::vec3 v1 = glm::vec3(1, 0, 0);
	glm::vec3 v2 = glm::vec3(11, 0, 0);
	glm::vec3 v3 = glm::vec3(12, 0, 0);
	glm::vec3 v4 = glm::vec3(1, 7, 0);
	glm::vec3 v5 = glm::vec3(11, 7, 0);
	glm::vec3 v6 = glm::vec3(6, 9, 0);
	glm::vec3 v7 = glm::vec3(0, 10, 0);
	glm::vec3 v8 = glm::vec3(12, 10, 0);
	glm::vec3 v9 = glm::vec3(0, 0, -10);
	glm::vec3 v10 = glm::vec3(1, 0, -10);
	glm::vec3 v11 = glm::vec3(11, 0, -10);
	glm::vec3 v12 = glm::vec3(12, 0, -10);
	glm::vec3 v13 = glm::vec3(1, 7, -10);
	glm::vec3 v14 = glm::vec3(11, 7, -10);
	glm::vec3 v15 = glm::vec3(6, 9, -10);
	glm::vec3 v16 = glm::vec3(0, 10, -10);
	glm::vec3 v17 = glm::vec3(12, 10, -10);

	// Normal Vectors
	// setting the normals to be used for the VBO
	glm::vec3 front_normal = glm::vec3(0, 0, 1);
	glm::vec3 left_outside_normal = glm::vec3(-1, 0, 0);
	glm::vec3 back_normal = glm::vec3(0, 0, -1);
	glm::vec3 right_outside_normal = glm::vec3(1, 0, 0);
	glm::vec3 bottom_left_normal = glm::vec3(0, -1, 0);
	glm::vec3 bottom_right_normal = glm::vec3(0, -1, 0);
	glm::vec3 top_normal = glm::vec3(0, 1, 0);
	glm::vec3 left_inside_normal = glm::vec3(1, 0, 0);
	glm::vec3 right_inside_normal = glm::vec3(-1, 0, 0);
	glm::vec3 left_diagonal_normal = glm::vec3((2 * sqrt(29)) / 29, ((-5) * sqrt(29)) / 29, 0);
	glm::vec3 right_diagonal_normal = glm::vec3(((-2) * sqrt(29)) / 29, ((-5) * sqrt(29)) / 29, 0);

	// Texture Coordinates
	// setting the texture coordinates to be used for the VBO
	// there are only 14 different texture coordinates because some of them are duplicates
	glm::vec2 t0 = glm::vec2(0, 0);
	glm::vec2 t1 = glm::vec2(0.083, 0);
	glm::vec2 t2 = glm::vec2(0.916, 0);
	glm::vec2 t3 = glm::vec2(1, 0);
	glm::vec2 t4 = glm::vec2(0.083, 0.7);
	glm::vec2 t5 = glm::vec2(0.916, 0.7);
	glm::vec2 t6 = glm::vec2(0.5, 0.9);
	glm::vec2 t7 = glm::vec2(0, 1);
	glm::vec2 t8 = glm::vec2(1, 1);
	glm::vec2 t9 = glm::vec2(0, 0);
	glm::vec2 t10 = glm::vec2(0.083, 1);
	glm::vec2 t11 = glm::vec2(0, 0.7);
	glm::vec2 t12 = glm::vec2(1, 0.7);
	glm::vec2 t13 = glm::vec2(0, 0.46);
	glm::vec2 t14 = glm::vec2(1, 0.46);

	// Colour
	// setting the colour to be used for the VBO
	// I have only added one colour as i intend to use a texture on my object down the line
	glm::vec3 grey = glm::vec3(0.2, 0.2, 0.2);
	glm::vec3 white = glm::vec3(1, 1, 1);

	//////////////////////////////////////////////////////////////////////////
	// Front face 
	m_VBO.AddData(&v2, sizeof(glm::vec3));
	m_VBO.AddData(&t2, sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&white, sizeof(glm::vec3));

	m_VBO.AddData(&v3, sizeof(glm::vec3));
	m_VBO.AddData(&t3, sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&white, sizeof(glm::vec3));

	m_VBO.AddData(&v5, sizeof(glm::vec3));
	m_VBO.AddData(&t5, sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&white, sizeof(glm::vec3));

	m_VBO.AddData(&v8, sizeof(glm::vec3));
	m_VBO.AddData(&t8, sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&white, sizeof(glm::vec3));
	
	m_VBO.AddData(&v6, sizeof(glm::vec3));
	m_VBO.AddData(&t6, sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&white, sizeof(glm::vec3));

	m_VBO.AddData(&v7, sizeof(glm::vec3));
	m_VBO.AddData(&t7, sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&white, sizeof(glm::vec3));

	m_VBO.AddData(&v4, sizeof(glm::vec3));
	m_VBO.AddData(&t4, sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&white, sizeof(glm::vec3));

	m_VBO.AddData(&v0, sizeof(glm::vec3));
	m_VBO.AddData(&t0, sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&white, sizeof(glm::vec3));

	m_VBO.AddData(&v1, sizeof(glm::vec3));
	m_VBO.AddData(&t1, sizeof(glm::vec2));
	m_VBO.AddData(&front_normal, sizeof(glm::vec3));
	m_VBO.AddData(&white, sizeof(glm::vec3));
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// Outside left face
	m_VBO.AddData(&v9, sizeof(glm::vec3));
	m_VBO.AddData(&t0, sizeof(glm::vec2));
	m_VBO.AddData(&left_outside_normal, sizeof(glm::vec3));
	m_VBO.AddData(&white, sizeof(glm::vec3));

	m_VBO.AddData(&v0, sizeof(glm::vec3));
	m_VBO.AddData(&t3, sizeof(glm::vec2));
	m_VBO.AddData(&left_outside_normal, sizeof(glm::vec3));
	m_VBO.AddData(&white, sizeof(glm::vec3));

	m_VBO.AddData(&v16, sizeof(glm::vec3));
	m_VBO.AddData(&t7, sizeof(glm::vec2));
	m_VBO.AddData(&left_outside_normal, sizeof(glm::vec3));
	m_VBO.AddData(&white, sizeof(glm::vec3));

	m_VBO.AddData(&v7, sizeof(glm::vec3));
	m_VBO.AddData(&t8, sizeof(glm::vec2));
	m_VBO.AddData(&left_outside_normal, sizeof(glm::vec3));
	m_VBO.AddData(&white, sizeof(glm::vec3));
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// Back face
	m_VBO.AddData(&v10, sizeof(glm::vec3));
	m_VBO.AddData(&t2, sizeof(glm::vec2));
	m_VBO.AddData(&back_normal, sizeof(glm::vec3));
	m_VBO.AddData(&white, sizeof(glm::vec3));

	m_VBO.AddData(&v9, sizeof(glm::vec3));
	m_VBO.AddData(&t3, sizeof(glm::vec2));
	m_VBO.AddData(&back_normal, sizeof(glm::vec3));
	m_VBO.AddData(&white, sizeof(glm::vec3));

	m_VBO.AddData(&v13, sizeof(glm::vec3));
	m_VBO.AddData(&t5, sizeof(glm::vec2));
	m_VBO.AddData(&back_normal, sizeof(glm::vec3));
	m_VBO.AddData(&white, sizeof(glm::vec3));

	m_VBO.AddData(&v16, sizeof(glm::vec3));
	m_VBO.AddData(&t8, sizeof(glm::vec2));
	m_VBO.AddData(&back_normal, sizeof(glm::vec3));
	m_VBO.AddData(&white, sizeof(glm::vec3));

	m_VBO.AddData(&v15, sizeof(glm::vec3));
	m_VBO.AddData(&t6, sizeof(glm::vec2));
	m_VBO.AddData(&back_normal, sizeof(glm::vec3));
	m_VBO.AddData(&white, sizeof(glm::vec3));

	m_VBO.AddData(&v17, sizeof(glm::vec3));
	m_VBO.AddData(&t7, sizeof(glm::vec2));
	m_VBO.AddData(&back_normal, sizeof(glm::vec3));
	m_VBO.AddData(&white, sizeof(glm::vec3));

	m_VBO.AddData(&v14, sizeof(glm::vec3));
	m_VBO.AddData(&t4, sizeof(glm::vec2));
	m_VBO.AddData(&back_normal, sizeof(glm::vec3));
	m_VBO.AddData(&white, sizeof(glm::vec3));

	m_VBO.AddData(&v12, sizeof(glm::vec3));
	m_VBO.AddData(&t0, sizeof(glm::vec2));
	m_VBO.AddData(&back_normal, sizeof(glm::vec3));
	m_VBO.AddData(&white, sizeof(glm::vec3));

	m_VBO.AddData(&v11, sizeof(glm::vec3));
	m_VBO.AddData(&t1, sizeof(glm::vec2));
	m_VBO.AddData(&back_normal, sizeof(glm::vec3));
	m_VBO.AddData(&white, sizeof(glm::vec3));
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// Outside right face
	m_VBO.AddData(&v3, sizeof(glm::vec3));
	m_VBO.AddData(&t0, sizeof(glm::vec2));
	m_VBO.AddData(&right_outside_normal, sizeof(glm::vec3));
	m_VBO.AddData(&white, sizeof(glm::vec3));

	m_VBO.AddData(&v12, sizeof(glm::vec3));
	m_VBO.AddData(&t3, sizeof(glm::vec2));
	m_VBO.AddData(&right_outside_normal, sizeof(glm::vec3));
	m_VBO.AddData(&white, sizeof(glm::vec3));

	m_VBO.AddData(&v8, sizeof(glm::vec3));
	m_VBO.AddData(&t7, sizeof(glm::vec2));
	m_VBO.AddData(&right_outside_normal, sizeof(glm::vec3));
	m_VBO.AddData(&white, sizeof(glm::vec3));

	m_VBO.AddData(&v17, sizeof(glm::vec3));
	m_VBO.AddData(&t8, sizeof(glm::vec2));
	m_VBO.AddData(&right_outside_normal, sizeof(glm::vec3));
	m_VBO.AddData(&white, sizeof(glm::vec3));
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// Bottom left face
	m_VBO.AddData(&v9, sizeof(glm::vec3));
	m_VBO.AddData(&t0, sizeof(glm::vec2));
	m_VBO.AddData(&bottom_left_normal, sizeof(glm::vec3));
	m_VBO.AddData(&white, sizeof(glm::vec3));

	m_VBO.AddData(&v10, sizeof(glm::vec3));
	m_VBO.AddData(&t1, sizeof(glm::vec2));
	m_VBO.AddData(&bottom_left_normal, sizeof(glm::vec3));
	m_VBO.AddData(&white, sizeof(glm::vec3));

	m_VBO.AddData(&v0, sizeof(glm::vec3));
	m_VBO.AddData(&t7, sizeof(glm::vec2));
	m_VBO.AddData(&bottom_left_normal, sizeof(glm::vec3));
	m_VBO.AddData(&white, sizeof(glm::vec3));

	m_VBO.AddData(&v1, sizeof(glm::vec3));
	m_VBO.AddData(&t10, sizeof(glm::vec2));
	m_VBO.AddData(&bottom_left_normal, sizeof(glm::vec3));
	m_VBO.AddData(&white, sizeof(glm::vec3));
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// Bottom right face
	m_VBO.AddData(&v11, sizeof(glm::vec3));
	m_VBO.AddData(&t0, sizeof(glm::vec2));
	m_VBO.AddData(&bottom_right_normal, sizeof(glm::vec3));
	m_VBO.AddData(&white, sizeof(glm::vec3));

	m_VBO.AddData(&v12, sizeof(glm::vec3));
	m_VBO.AddData(&t1, sizeof(glm::vec2));
	m_VBO.AddData(&bottom_right_normal, sizeof(glm::vec3));
	m_VBO.AddData(&white, sizeof(glm::vec3));

	m_VBO.AddData(&v2, sizeof(glm::vec3));
	m_VBO.AddData(&t7, sizeof(glm::vec2));
	m_VBO.AddData(&bottom_right_normal, sizeof(glm::vec3));
	m_VBO.AddData(&white, sizeof(glm::vec3));

	m_VBO.AddData(&v3, sizeof(glm::vec3));
	m_VBO.AddData(&t10, sizeof(glm::vec2));
	m_VBO.AddData(&bottom_right_normal, sizeof(glm::vec3));
	m_VBO.AddData(&white, sizeof(glm::vec3));
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// Top face
	m_VBO.AddData(&v7, sizeof(glm::vec3));
	m_VBO.AddData(&t0, sizeof(glm::vec2));
	m_VBO.AddData(&top_normal, sizeof(glm::vec3));
	m_VBO.AddData(&white, sizeof(glm::vec3));

	m_VBO.AddData(&v8, sizeof(glm::vec3));
	m_VBO.AddData(&t3, sizeof(glm::vec2));
	m_VBO.AddData(&top_normal, sizeof(glm::vec3));
	m_VBO.AddData(&white, sizeof(glm::vec3));

	m_VBO.AddData(&v16, sizeof(glm::vec3));
	m_VBO.AddData(&t7, sizeof(glm::vec2));
	m_VBO.AddData(&top_normal, sizeof(glm::vec3));
	m_VBO.AddData(&white, sizeof(glm::vec3));

	m_VBO.AddData(&v17, sizeof(glm::vec3));
	m_VBO.AddData(&t8, sizeof(glm::vec2));
	m_VBO.AddData(&top_normal, sizeof(glm::vec3));
	m_VBO.AddData(&white, sizeof(glm::vec3));
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// Inside left face
	m_VBO.AddData(&v1, sizeof(glm::vec3));
	m_VBO.AddData(&t0, sizeof(glm::vec2));
	m_VBO.AddData(&left_inside_normal, sizeof(glm::vec3));
	m_VBO.AddData(&white, sizeof(glm::vec3));

	m_VBO.AddData(&v10, sizeof(glm::vec3));
	m_VBO.AddData(&t3, sizeof(glm::vec2));
	m_VBO.AddData(&left_inside_normal, sizeof(glm::vec3));
	m_VBO.AddData(&white, sizeof(glm::vec3));

	m_VBO.AddData(&v4, sizeof(glm::vec3));
	m_VBO.AddData(&t11, sizeof(glm::vec2));
	m_VBO.AddData(&left_inside_normal, sizeof(glm::vec3));
	m_VBO.AddData(&white, sizeof(glm::vec3));

	m_VBO.AddData(&v13, sizeof(glm::vec3));
	m_VBO.AddData(&t12, sizeof(glm::vec2));
	m_VBO.AddData(&left_inside_normal, sizeof(glm::vec3));
	m_VBO.AddData(&white, sizeof(glm::vec3));
	//////////////////////////////////////////////////////////////////////////
	
	//////////////////////////////////////////////////////////////////////////
	// Inside right face
	m_VBO.AddData(&v11, sizeof(glm::vec3));
	m_VBO.AddData(&t0, sizeof(glm::vec2));
	m_VBO.AddData(&right_inside_normal, sizeof(glm::vec3));
	m_VBO.AddData(&white, sizeof(glm::vec3));

	m_VBO.AddData(&v2, sizeof(glm::vec3));
	m_VBO.AddData(&t3, sizeof(glm::vec2));
	m_VBO.AddData(&right_inside_normal, sizeof(glm::vec3));
	m_VBO.AddData(&white, sizeof(glm::vec3));

	m_VBO.AddData(&v14, sizeof(glm::vec3));
	m_VBO.AddData(&t11, sizeof(glm::vec2));
	m_VBO.AddData(&right_inside_normal, sizeof(glm::vec3));
	m_VBO.AddData(&white, sizeof(glm::vec3));

	m_VBO.AddData(&v5, sizeof(glm::vec3));
	m_VBO.AddData(&t12, sizeof(glm::vec2));
	m_VBO.AddData(&right_inside_normal, sizeof(glm::vec3));
	m_VBO.AddData(&white, sizeof(glm::vec3));
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// Inside left diagonal face
	m_VBO.AddData(&v4, sizeof(glm::vec3));
	m_VBO.AddData(&t0, sizeof(glm::vec2));
	m_VBO.AddData(&left_diagonal_normal, sizeof(glm::vec3));
	m_VBO.AddData(&white, sizeof(glm::vec3));

	m_VBO.AddData(&v13, sizeof(glm::vec3));
	m_VBO.AddData(&t3, sizeof(glm::vec2));
	m_VBO.AddData(&left_diagonal_normal, sizeof(glm::vec3));
	m_VBO.AddData(&white, sizeof(glm::vec3));

	m_VBO.AddData(&v6, sizeof(glm::vec3));
	m_VBO.AddData(&t13, sizeof(glm::vec2));
	m_VBO.AddData(&left_diagonal_normal, sizeof(glm::vec3));
	m_VBO.AddData(&white, sizeof(glm::vec3));

	m_VBO.AddData(&v15, sizeof(glm::vec3));
	m_VBO.AddData(&t14, sizeof(glm::vec2));
	m_VBO.AddData(&left_diagonal_normal, sizeof(glm::vec3));
	m_VBO.AddData(&white, sizeof(glm::vec3));
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// Inside right diagonal face
	m_VBO.AddData(&v14, sizeof(glm::vec3));
	m_VBO.AddData(&t0, sizeof(glm::vec2));
	m_VBO.AddData(&right_diagonal_normal, sizeof(glm::vec3));
	m_VBO.AddData(&white, sizeof(glm::vec3));

	m_VBO.AddData(&v5, sizeof(glm::vec3));
	m_VBO.AddData(&t3, sizeof(glm::vec2));
	m_VBO.AddData(&right_diagonal_normal, sizeof(glm::vec3));
	m_VBO.AddData(&white, sizeof(glm::vec3));

	m_VBO.AddData(&v15, sizeof(glm::vec3));
	m_VBO.AddData(&t13, sizeof(glm::vec2));
	m_VBO.AddData(&right_diagonal_normal, sizeof(glm::vec3));
	m_VBO.AddData(&white, sizeof(glm::vec3));

	m_VBO.AddData(&v6, sizeof(glm::vec3));
	m_VBO.AddData(&t14, sizeof(glm::vec2));
	m_VBO.AddData(&right_diagonal_normal, sizeof(glm::vec3));
	m_VBO.AddData(&white, sizeof(glm::vec3));
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

void CTunnel::Render()
{
	glBindVertexArray(m_uiVAO);
	m_tTexture.Bind();

	// Call glDrawArrays to render a face
	// Front face
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 9);
	// Outside left face
	glDrawArrays(GL_TRIANGLE_STRIP, 9, 4);
	// back face
	glDrawArrays(GL_TRIANGLE_STRIP, 13, 9);
	// outside right face
	glDrawArrays(GL_TRIANGLE_STRIP, 22, 4);
	// bottom left face
	glDrawArrays(GL_TRIANGLE_STRIP, 26, 4);
	// bottom right face
	glDrawArrays(GL_TRIANGLE_STRIP, 30, 4);
	// top face
	glDrawArrays(GL_TRIANGLE_STRIP, 34, 4);
	// inside left face
	glDrawArrays(GL_TRIANGLE_STRIP, 38, 4);
	// inside right face
	glDrawArrays(GL_TRIANGLE_STRIP, 42, 4);
	// inside left diagonal face
	glDrawArrays(GL_TRIANGLE_STRIP, 46, 4);
	// inside right diagonal face
	glDrawArrays(GL_TRIANGLE_STRIP, 50, 4);

}

void CTunnel::Release()
{
	m_tTexture.Release();
	glDeleteVertexArrays(1, &m_uiVAO);
	m_VBO.Release();
}
