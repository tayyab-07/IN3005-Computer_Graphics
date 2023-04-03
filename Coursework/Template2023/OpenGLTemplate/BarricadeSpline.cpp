#include "BarricadeSpline.h"
#define _USE_MATH_DEFINES
#include <math.h>

CBarricadeSpline::CBarricadeSpline()
{
	m_vertexCount = 0;
	m_barricadeCount = 0;
}

CBarricadeSpline::~CBarricadeSpline()
{}

// Perform Catmull Rom spline interpolation between four points, interpolating the space between p1 and p2
glm::vec3 CBarricadeSpline::Interpolate(glm::vec3& p0, glm::vec3& p1, glm::vec3& p2, glm::vec3& p3, float t)
{
	float t2 = t * t;
	float t3 = t2 * t;

	glm::vec3 a = p1;
	glm::vec3 b = 0.5f * (-p0 + p2);
	glm::vec3 c = 0.5f * (2.0f * p0 - 5.0f * p1 + 4.0f * p2 - p3);
	glm::vec3 d = 0.5f * (-p0 + 3.0f * p1 - 3.0f * p2 + p3);

	return a + b * t + c * t2 + d * t3;
}


void CBarricadeSpline::SetControlPoints()
{
	// Points along the track
	// Total of 33 points split up into 10s to make it easier to locate a point
	m_controlPoints.push_back(glm::vec3(900, 100, 0));
	m_controlPoints.push_back(glm::vec3(850, 100, -200));
	m_controlPoints.push_back(glm::vec3(800, 100, -400));
	m_controlPoints.push_back(glm::vec3(750, 100, -600));
	m_controlPoints.push_back(glm::vec3(550, 100, -800));
	m_controlPoints.push_back(glm::vec3(300, 100, -900));
	m_controlPoints.push_back(glm::vec3(0, 100, -900));
	m_controlPoints.push_back(glm::vec3(-200, 90, -900));
	m_controlPoints.push_back(glm::vec3(-400, 80, -800));
	m_controlPoints.push_back(glm::vec3(-450, 65, -600));

	m_controlPoints.push_back(glm::vec3(-650, 50, -400));
	m_controlPoints.push_back(glm::vec3(-750, 40, -200));
	m_controlPoints.push_back(glm::vec3(-700, 30, 0));
	m_controlPoints.push_back(glm::vec3(-800, 20, 250));
	m_controlPoints.push_back(glm::vec3(-950, 20, 400));
	m_controlPoints.push_back(glm::vec3(-1000, 20, 600));
	m_controlPoints.push_back(glm::vec3(-900, 20, 800));
	m_controlPoints.push_back(glm::vec3(-750, 20, 750));
	m_controlPoints.push_back(glm::vec3(-700, 30, 600));
	m_controlPoints.push_back(glm::vec3(-650, 30, 400));

	m_controlPoints.push_back(glm::vec3(-550, 30, 200));
	m_controlPoints.push_back(glm::vec3(-200, 30, 50));
	m_controlPoints.push_back(glm::vec3(50, 35, 150));
	m_controlPoints.push_back(glm::vec3(0, 40, 400));
	m_controlPoints.push_back(glm::vec3(-200, 50, 475));
	m_controlPoints.push_back(glm::vec3(-350, 50, 650));
	m_controlPoints.push_back(glm::vec3(-200, 50, 850));
	m_controlPoints.push_back(glm::vec3(0, 60, 850));
	m_controlPoints.push_back(glm::vec3(300, 70, 800));
	m_controlPoints.push_back(glm::vec3(350, 80, 600));

	m_controlPoints.push_back(glm::vec3(400, 90, 400));
	m_controlPoints.push_back(glm::vec3(600, 95, 350));
	m_controlPoints.push_back(glm::vec3(800, 100, 200));


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// UP VECTORS for each point above
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(-0.2, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(-0.4, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(-0.4, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(-0.4, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(-0.3, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(-0.2, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(-0.1, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));

	m_controlUpVectors.push_back(glm::vec3(0.2, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0.1, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0.1, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0.2, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0.2, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0.1, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(-0.1, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0.0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0.0, 1, 0));

	m_controlUpVectors.push_back(glm::vec3(-0.1, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(-0.1, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(-0.2, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(-0.1, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(-0.1, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));

	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
}

// Determine lengths along the control points, which is the set of control points forming the closed curve
void CBarricadeSpline::ComputeLengthsAlongControlPoints()
{
	int M = (int)m_controlPoints.size();

	float fAccumulatedLength = 0.0f;
	m_distances.push_back(fAccumulatedLength);
	for (int i = 1; i < M; i++) {
		fAccumulatedLength += glm::distance(m_controlPoints[i - 1], m_controlPoints[i]);
		m_distances.push_back(fAccumulatedLength);
	}

	// Get the distance from the last point to the first
	fAccumulatedLength += glm::distance(m_controlPoints[M - 1], m_controlPoints[0]);
	m_distances.push_back(fAccumulatedLength);
}

// Return the point (and upvector, if control upvectors provided) based on a distance d along the control polygon
bool CBarricadeSpline::Sample(float d, glm::vec3& p, glm::vec3& up)
{
	if (d < 0)
		return false;

	int M = (int)m_controlPoints.size();
	if (M == 0)
		return false;

	float fTotalLength = m_distances[m_distances.size() - 1];

	// The the current length along the control polygon; handle the case where we've looped around the track
	float fLength = d - (int)(d / fTotalLength) * fTotalLength;

	// Find the current segment
	int j = -1;
	for (int i = 0; i < (int)m_distances.size() - 1; i++) {
		if (fLength >= m_distances[i] && fLength < m_distances[i + 1]) {
			j = i; // found it!
			break;
		}
	}

	if (j == -1)
		return false;

	// Interpolate on current segment -- get t
	float fSegmentLength = m_distances[j + 1] - m_distances[j];
	float t = (fLength - m_distances[j]) / fSegmentLength;

	// Get the indices of the four points along the control polygon for the current segment
	int iPrev = ((j - 1) + M) % M;
	int iCur = j;
	int iNext = (j + 1) % M;
	int iNextNext = (j + 2) % M;

	// Interpolate to get the point (and upvector)
	p = Interpolate(m_controlPoints[iPrev], m_controlPoints[iCur], m_controlPoints[iNext], m_controlPoints[iNextNext], t);
	if (m_controlUpVectors.size() == m_controlPoints.size())
		up = glm::normalize(Interpolate(m_controlUpVectors[iPrev], m_controlUpVectors[iCur], m_controlUpVectors[iNext], m_controlUpVectors[iNextNext], t));

	return true;
}

// Sample a set of control points using an open Catmull-Rom spline, to produce a set of iNumSamples that are (roughly) equally spaced
void CBarricadeSpline::UniformlySampleControlPoints(int numSamples)
{
	glm::vec3 p, up;

	// Compute the lengths of each segment along the control polygon, and the total length
	ComputeLengthsAlongControlPoints();
	float fTotalLength = m_distances[m_distances.size() - 1];

	// The spacing will be based on the control polygon
	float fSpacing = fTotalLength / numSamples;

	// Call PointAt to sample the spline, to generate the points
	for (int i = 0; i < numSamples; i++) {
		Sample(i * fSpacing, p, up);
		m_centrelinePoints.push_back(p);
		if (m_controlUpVectors.size() > 0)
			m_centrelineUpVectors.push_back(up);
	}

	// Repeat once more for truly equidistant points
	m_controlPoints = m_centrelinePoints;
	m_controlUpVectors = m_centrelineUpVectors;
	m_centrelinePoints.clear();
	m_centrelineUpVectors.clear();
	m_distances.clear();
	ComputeLengthsAlongControlPoints();
	fTotalLength = m_distances[m_distances.size() - 1];
	fSpacing = fTotalLength / numSamples;
	for (int i = 0; i < numSamples; i++) {
		Sample(i * fSpacing, p, up);
		m_centrelinePoints.push_back(p);
		if (m_controlUpVectors.size() > 0)
			m_centrelineUpVectors.push_back(up);
	}
}

void CBarricadeSpline::CreateCentreline()
{
	// Call Set Control Points
	SetControlPoints();

	// Call UniformlySampleControlPoints with the number of samples required
	UniformlySampleControlPoints(sampleNum);

	// Create a VAO called m_vaoCentreline and a VBO to get the points onto the graphics card
	glGenVertexArrays(1, &m_vaoCentreline);
	glBindVertexArray(m_vaoCentreline);
	CVertexBufferObject vbo;
	vbo.Create();
	vbo.Bind();

	// set the texture coordinates and normal for the points in the VBO
	glm::vec2 texCoord(0.0f, 0.0f);
	glm::vec3 normal(0.0f, 1.0f, 0.0f);

	// add the data to every point in the centreline  
	for (unsigned int i = 0; i < m_centrelinePoints.size(); i++)
	{
		glm::vec3 v = m_centrelinePoints[i];
		vbo.AddData(&v, sizeof(glm::vec3));
		vbo.AddData(&texCoord, sizeof(glm::vec2));
		vbo.AddData(&m_centrelineUpVectors[i], sizeof(glm::vec3));
	}

	// Upload the VBO to the GPU
	vbo.UploadDataToGPU(GL_STATIC_DRAW);
	// Set the vertex attribute locations
	GLsizei stride = 2 * sizeof(glm::vec3) + sizeof(glm::vec2);
	// Vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, 0);
	// Texture coordinates
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)sizeof(glm::vec3));
	// Normal vectors
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(glm::vec3) + sizeof(glm::vec2)));
}

void CBarricadeSpline::CreateOffsetCurves()
{
	// Compute the offset curves, one left, and one right.  Store the points in m_leftOffsetPoints and m_rightOffsetPoints respectively

	// track width
	float w = 80;

	// use TNB frame to calculate positions of points in left and right offset curves
	for (int i = 0; i < m_centrelinePoints.size(); i++)
	{
		glm::vec3 p = m_centrelinePoints[i];
		glm::vec3 up = m_centrelineUpVectors[i];
		glm::vec3 pNext = m_centrelinePoints[(i + 1) % sampleNum];
		glm::vec3 t = normalize(pNext - p);
		glm::vec3 n = glm::vec3(glm::cross(t, up));

		m_leftOffsetPoints.push_back(p - ((w / 2) * n));
		m_rightOffsetPoints.push_back(p + ((w / 2) * n));
	}

	// set the txture coordinates and normal for the points in the VBO
	glm::vec2 texCoord(0.0f, 0.0f);
	glm::vec3 normal(0.0f, 1.0f, 0.0f);

	// Set the stride length
	GLsizei stride = 2 * sizeof(glm::vec3) + sizeof(glm::vec2);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// LEFT OFFSET CURVE VBO
	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	glGenVertexArrays(1, &m_vaoLeftOffsetCurve);
	glBindVertexArray(m_vaoLeftOffsetCurve);

	CVertexBufferObject leftVBO;
	leftVBO.Create();
	leftVBO.Bind();

	// use a for loop to add points to vbo 
	for (unsigned int i = 0; i < m_leftOffsetPoints.size(); i++)
	{
		glm::vec3 l = m_leftOffsetPoints[i];
		leftVBO.AddData(&l, sizeof(glm::vec3));
		leftVBO.AddData(&texCoord, sizeof(glm::vec2));
		leftVBO.AddData(&normal, sizeof(glm::vec3));
	}

	// Upload the VBO to the GPU
	leftVBO.UploadDataToGPU(GL_STATIC_DRAW);
	// Vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, 0);
	// Texture coordinates
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)sizeof(glm::vec3));
	// Normal vectors
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(glm::vec3) + sizeof(glm::vec2)));


	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// RIGHT OFFSET CURVE VBO
	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	glGenVertexArrays(1, &m_vaoRightOffsetCurve);
	glBindVertexArray(m_vaoRightOffsetCurve);

	CVertexBufferObject rightVBO;
	rightVBO.Create();
	rightVBO.Bind();

	// use a for loop to add points to vbo 
	for (unsigned int i = 0; i < m_rightOffsetPoints.size(); i++)
	{
		glm::vec3 r = m_rightOffsetPoints[i];
		rightVBO.AddData(&r, sizeof(glm::vec3));
		rightVBO.AddData(&texCoord, sizeof(glm::vec2));
		rightVBO.AddData(&normal, sizeof(glm::vec3));
	}

	// Upload the VBO to the GPU
	rightVBO.UploadDataToGPU(GL_STATIC_DRAW);
	// Vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, 0);
	// Texture coordinates
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)sizeof(glm::vec3));
	// Normal vectors
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(glm::vec3) + sizeof(glm::vec2)));
}

void CBarricadeSpline::CreateLeftBarricade(string directory, string filename, float textureRepeat)
{
	// Load the texture
	m_texture.Load(directory + filename, true);
	m_directory = directory;
	m_filename = filename;

	// Set parameters for texturing using sampler object
	m_texture.SetSamplerObjectParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	m_texture.SetSamplerObjectParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	m_texture.SetSamplerObjectParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
	m_texture.SetSamplerObjectParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Use a TNB frame and offset point to find a point above the offset point(barricade point) and a normal
	for (int i = 0; i < m_leftOffsetPoints.size(); i++)
	{
		glm::vec3 p = m_leftOffsetPoints[i];
		glm::vec3 up = m_centrelineUpVectors[i];
		glm::vec3 pNext = m_leftOffsetPoints[(i + 1) % m_leftOffsetPoints.size()];
		glm::vec3 t = normalize(pNext - p);
		glm::vec3 n = normalize(glm::vec3(glm::cross(t, up)));
		glm::vec3 b = normalize(glm::vec3(glm::cross(n, t)));

		m_leftBarricadePoints.push_back(p + (barricadeHeight * b));
		m_leftBarricadeNormals.push_back(n);
	}

	glGenVertexArrays(1, &m_vaoLeftBarricade);
	glBindVertexArray(m_vaoLeftBarricade);

	CVertexBufferObject vbo;
	vbo.Create();
	vbo.Bind();

	// Texture coordinates stored in an array
	// right side of the texture pattern repeated
	glm::vec2 texCoord[4]
	{
		glm::vec2(0.0f, 0.0f),
		glm::vec2(0.0f, 1.0f),
		glm::vec2(textureRepeat, 0.0f),
		glm::vec2(textureRepeat, 1.0f)
	};

	// Add position, texture coord and normal to vbo
	// points are added so that the winding of the resulting triangles faces towards the track
	for (int i = 0; i < m_leftOffsetPoints.size() + 1; i++)
	{
		glm::vec3 q = m_leftBarricadePoints[i % m_leftBarricadePoints.size()];
		vbo.AddData(&q, sizeof(glm::vec3));
		vbo.AddData(&texCoord[(i % 2) + 2], sizeof(glm::vec2));
		vbo.AddData(&m_leftBarricadeNormals[i % m_leftBarricadeNormals.size()], sizeof(glm::vec3));

		glm::vec3 p = m_leftOffsetPoints[i % m_leftOffsetPoints.size()];
		vbo.AddData(&p, sizeof(glm::vec3));
		vbo.AddData(&texCoord[i % 2], sizeof(glm::vec2));
		vbo.AddData(&m_leftBarricadeNormals[i % m_leftBarricadeNormals.size()], sizeof(glm::vec3));

		m_barricadeCount = m_barricadeCount + 2;
	}
	
	// Set the vertex attribute locations
	GLsizei stride = 2 * sizeof(glm::vec3) + sizeof(glm::vec2);
	// Upload the VBO to the GPU
	vbo.UploadDataToGPU(GL_STATIC_DRAW);
	// Vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, 0);
	// Texture coordinates
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)sizeof(glm::vec3));
	// Normal vectors
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(glm::vec3) + sizeof(glm::vec2)));

}

void CBarricadeSpline::CreateRightBarricade(string directory, string filename, float textureRepeat)
{
	// Load the texture
	m_texture.Load(directory + filename, true);
	m_directory = directory;
	m_filename = filename;

	// Set parameters for texturing using sampler object
	m_texture.SetSamplerObjectParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	m_texture.SetSamplerObjectParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	m_texture.SetSamplerObjectParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
	m_texture.SetSamplerObjectParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Use a TNB frame and offset point to find a point above the offset point(barricade point) and a normal
	for (int i = 0; i < m_rightOffsetPoints.size(); i++)
	{
		glm::vec3 p = m_rightOffsetPoints[i];
		glm::vec3 up = m_centrelineUpVectors[i];
		glm::vec3 pNext = m_rightOffsetPoints[(i + 1) % m_rightOffsetPoints.size()];
		glm::vec3 t = normalize(pNext - p);
		glm::vec3 n = normalize(glm::vec3(glm::cross(t, up)));
		glm::vec3 b = normalize(glm::vec3(glm::cross(n, t)));

		m_rightBarricadePoints.push_back(p + (barricadeHeight * b));
		m_rightBarricadeNormals.push_back(n);
	}

	glGenVertexArrays(1, &m_vaoRightBarricade);
	glBindVertexArray(m_vaoRightBarricade);

	CVertexBufferObject vbo;
	vbo.Create();
	vbo.Bind();

	// Texture coordinates store in an array
	// right side of the texture pattern repeated
	glm::vec2 texCoord[4]
	{
		glm::vec2(0.0f, 0.0f),
		glm::vec2(0.0f, 1.0f),
		glm::vec2(textureRepeat, 0.0f),
		glm::vec2(textureRepeat, 1.0f)
	};

	// Add position, texture coord and normal to vbo
	// points are added so that the winding of the resulting triangles faces towards the track
	for (int i = 0; i < m_rightOffsetPoints.size() + 1; i++)
	{
		glm::vec3 p = m_rightOffsetPoints[i % m_rightOffsetPoints.size()];
		vbo.AddData(&p, sizeof(glm::vec3));
		vbo.AddData(&texCoord[i % 2], sizeof(glm::vec2));
		vbo.AddData(&m_rightBarricadeNormals[i % m_rightBarricadeNormals.size()], sizeof(glm::vec3));

		glm::vec3 q = m_rightBarricadePoints[i % m_rightBarricadePoints.size()];
		vbo.AddData(&q, sizeof(glm::vec3));
		vbo.AddData(&texCoord[(i % 2) + 2], sizeof(glm::vec2));
		vbo.AddData(&m_rightBarricadeNormals[i % m_rightBarricadeNormals.size()], sizeof(glm::vec3));
	}

	// Set the vertex attribute locations
	GLsizei stride = 2 * sizeof(glm::vec3) + sizeof(glm::vec2);
	// Upload the VBO to the GPU
	vbo.UploadDataToGPU(GL_STATIC_DRAW);
	// Vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, 0);
	// Texture coordinates
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)sizeof(glm::vec3));
	// Normal vectors
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(glm::vec3) + sizeof(glm::vec2)));
}

void CBarricadeSpline::RenderBarricades()
{
	//Bind the vbos and textures and render them using a Triangle strip

	glBindVertexArray(m_vaoLeftBarricade);
	m_texture.Bind();
	glDrawArrays(GL_TRIANGLE_STRIP, 0, m_barricadeCount);

	glBindVertexArray(m_vaoRightBarricade);
	m_texture.Bind();
	glDrawArrays(GL_TRIANGLE_STRIP, 0, m_barricadeCount);
}

glm::vec3 CBarricadeSpline::_dummy_vector(0.0f, 0.0f, 0.0f);