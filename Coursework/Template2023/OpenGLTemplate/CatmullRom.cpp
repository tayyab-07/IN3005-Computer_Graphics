#include "CatmullRom.h"
#define _USE_MATH_DEFINES
#include <math.h>



CCatmullRom::CCatmullRom()
{
	m_vertexCount = 0;
}

CCatmullRom::~CCatmullRom()
{}

// Perform Catmull Rom spline interpolation between four points, interpolating the space between p1 and p2
glm::vec3 CCatmullRom::Interpolate(glm::vec3 &p0, glm::vec3 &p1, glm::vec3 &p2, glm::vec3 &p3, float t)
{
    float t2 = t * t;
    float t3 = t2 * t;

	glm::vec3 a = p1;
	glm::vec3 b = 0.5f * (-p0 + p2);
	glm::vec3 c = 0.5f * (2.0f*p0 - 5.0f*p1 + 4.0f*p2 - p3);
	glm::vec3 d = 0.5f * (-p0 + 3.0f*p1 - 3.0f*p2 + p3);

	return a + b*t + c*t2 + d*t3;

}


void CCatmullRom::SetControlPoints()
{
	// Set control points (m_controlPoints) here, or load from disk

	// Optionally, set upvectors (m_controlUpVectors, one for each control point as well)

	// Points along the track
	// Total of 53 points split up into 10s to make it easier to locate a point
	m_controlPoints.push_back(glm::vec3(900, 5, 0));
	m_controlPoints.push_back(glm::vec3(900, 20, -150));
	m_controlPoints.push_back(glm::vec3(900, 35, -300));
	m_controlPoints.push_back(glm::vec3(900, 50, -450));
	m_controlPoints.push_back(glm::vec3(900, 65, -600));
	m_controlPoints.push_back(glm::vec3(900, 65, -675));
	m_controlPoints.push_back(glm::vec3(875, 65, -700));
	m_controlPoints.push_back(glm::vec3(850, 55, -675));
	m_controlPoints.push_back(glm::vec3(800, 40, -525));
	m_controlPoints.push_back(glm::vec3(650, 25, -450));

	m_controlPoints.push_back(glm::vec3(350, 15, -350));
	m_controlPoints.push_back(glm::vec3(175, 5, -335));
	m_controlPoints.push_back(glm::vec3(0, 5, -325));
	m_controlPoints.push_back(glm::vec3(0, 10, -400));
	m_controlPoints.push_back(glm::vec3(175, 25, -450));
	m_controlPoints.push_back(glm::vec3(275, 50, -550));
	m_controlPoints.push_back(glm::vec3(175, 85, -700));
	m_controlPoints.push_back(glm::vec3(-50, 110, -725));
	m_controlPoints.push_back(glm::vec3(-200, 110, -700));
	m_controlPoints.push_back(glm::vec3(-250, 105, -500));

	m_controlPoints.push_back(glm::vec3(-300, 100, -350));
	m_controlPoints.push_back(glm::vec3(-300, 70, -225));
	m_controlPoints.push_back(glm::vec3(-350, 55, -100));
	m_controlPoints.push_back(glm::vec3(-400, 35, 0));
	m_controlPoints.push_back(glm::vec3(-400, 15, 150));
	m_controlPoints.push_back(glm::vec3(-450, 15, 250));
	m_controlPoints.push_back(glm::vec3(-500, 15, 350));
	m_controlPoints.push_back(glm::vec3(-550, 15, 450));
	m_controlPoints.push_back(glm::vec3(-500, 15, 550));
	m_controlPoints.push_back(glm::vec3(-450, 15, 550));

	m_controlPoints.push_back(glm::vec3(-400, 15, 400));
	m_controlPoints.push_back(glm::vec3(-375, 15, 300));
	m_controlPoints.push_back(glm::vec3(-350, 15, 200));
	m_controlPoints.push_back(glm::vec3(-325, 20, 100));
	m_controlPoints.push_back(glm::vec3(-300, 25, 0));
	m_controlPoints.push_back(glm::vec3(-250, 40, -150));
	m_controlPoints.push_back(glm::vec3(-200, 40, -200));
	m_controlPoints.push_back(glm::vec3(-150, 30, -225));
	m_controlPoints.push_back(glm::vec3(-100, 20, -200));
	m_controlPoints.push_back(glm::vec3(-50, 15, -175));

	m_controlPoints.push_back(glm::vec3(-25, 15, -150));
	m_controlPoints.push_back(glm::vec3(-25, 15, -75));
	m_controlPoints.push_back(glm::vec3(25, 15, -75));
	m_controlPoints.push_back(glm::vec3(25, 15, 0));
	m_controlPoints.push_back(glm::vec3(25, 10, 100));
	m_controlPoints.push_back(glm::vec3(25, 7.5, 200));
	m_controlPoints.push_back(glm::vec3(125, 6.25, 275));
	m_controlPoints.push_back(glm::vec3(225, 5, 350));
	m_controlPoints.push_back(glm::vec3(500, 5, 350));
	m_controlPoints.push_back(glm::vec3(750, 5, 350));

	m_controlPoints.push_back(glm::vec3(825, 5, 275));
	m_controlPoints.push_back(glm::vec3(900, 5, 200));
	m_controlPoints.push_back(glm::vec3(900, 5, 100));

	m_controlUpVectors.push_back(glm::vec3(-1, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(-1, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(-1, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));

	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));

	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));

	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));

	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
	m_controlUpVectors.push_back(glm::vec3(0, 1, 0));
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
void CCatmullRom::ComputeLengthsAlongControlPoints()
{
	int M = (int) m_controlPoints.size();

	float fAccumulatedLength = 0.0f;
	m_distances.push_back(fAccumulatedLength);
	for (int i = 1; i < M; i++) {
		fAccumulatedLength += glm::distance(m_controlPoints[i-1], m_controlPoints[i]);
		m_distances.push_back(fAccumulatedLength);
	}

	// Get the distance from the last point to the first
	fAccumulatedLength += glm::distance(m_controlPoints[M-1], m_controlPoints[0]);
	m_distances.push_back(fAccumulatedLength);
}


// Return the point (and upvector, if control upvectors provided) based on a distance d along the control polygon
bool CCatmullRom::Sample(float d, glm::vec3 &p, glm::vec3 &up)
{
	if (d < 0)
		return false;

	int M = (int) m_controlPoints.size();
	if (M == 0)
		return false;


	float fTotalLength = m_distances[m_distances.size() - 1];

	// The the current length along the control polygon; handle the case where we've looped around the track
	float fLength = d - (int) (d / fTotalLength) * fTotalLength;

	// Find the current segment
	int j = -1;
	for (int i = 0; i < (int)m_distances.size()-1; i++) {
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
	int iPrev = ((j-1) + M) % M;
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
void CCatmullRom::UniformlySampleControlPoints(int numSamples)
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

void CCatmullRom::CreateCentreline()
{
	// Call Set Control Points
	SetControlPoints();

	// Call UniformlySampleControlPoints with the number of samples required
	UniformlySampleControlPoints(5000);

	// Create a VAO called m_vaoCentreline and a VBO to get the points onto the graphics card
	glGenVertexArrays(1, &m_vaoCentreline);
	glBindVertexArray(m_vaoCentreline);
	CVertexBufferObject vbo;
	vbo.Create();
	vbo.Bind();

	//set the texture coordinates and normal for the points in the VBO
	glm::vec2 texCoord(0.0f, 0.0f);
	glm::vec3 normal(0.0f, 1.0f, 0.0f);
	//add the data to every point in the centreline  
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


void CCatmullRom::CreateOffsetCurves()
{
	// Compute the offset curves, one left, and one right.  Store the points in m_leftOffsetPoints and m_rightOffsetPoints respectively

	float w = 20;

	for (int i = 0; i < m_centrelinePoints.size(); i++)
	{
		glm::vec3 p = m_centrelinePoints[i];
		glm::vec3 up = m_centrelineUpVectors[i];
		glm::vec3 pNext = m_centrelinePoints[(i + 1) % 5000];
		glm::vec3 t = normalize(pNext - p);
		glm::vec3 n = glm::vec3((t.y*up.z)-(t.z*up.y), (t.z*up.x)-(t.x*up.z), (t.x*up.y)-(t.y*up.x));

		m_leftOffsetPoints.push_back(p - (w * n));
		m_rightOffsetPoints.push_back(p + (w * n));
	}


	// Generate two VAOs called m_vaoLeftOffsetCurve and m_vaoRightOffsetCurve, each with a VBO, and get the offset curve points on the graphics card
	// Note it is possible to only use one VAO / VBO with all the points instead.

	//set the txture coordinates and normal for the points in the VBO
	glm::vec2 texCoord(0.0f, 0.0f);
	glm::vec3 normal(0.0f, 1.0f, 0.0f);

	// Set the vertex attribute locations
	GLsizei stride = 2 * sizeof(glm::vec3) + sizeof(glm::vec2);

	glGenVertexArrays(1, &m_vaoLeftOffsetCurve);
	glBindVertexArray(m_vaoLeftOffsetCurve);

	CVertexBufferObject leftVBO;
	leftVBO.Create();
	leftVBO.Bind();

	// use a for loop to add points to vbo from both left and right offset points
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


	glGenVertexArrays(1, &m_vaoRightOffsetCurve);
	glBindVertexArray(m_vaoRightOffsetCurve);

	CVertexBufferObject rightVBO;
	rightVBO.Create();
	rightVBO.Bind();

	// use a for loop to add points to vbo from both left and right offset points
	for (unsigned int i = 0; i < m_rightOffsetPoints.size(); i++)
	{
		glm::vec3 r = m_rightOffsetPoints[i];
		rightVBO.AddData(&r, sizeof(glm::vec3));
		rightVBO.AddData(&texCoord, sizeof(glm::vec2));
		rightVBO.AddData(&normal, sizeof(glm::vec3));
	}

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


void CCatmullRom::CreateTrack()
{
	
	// Generate a VAO called m_vaoTrack and a VBO to get the offset curve points and indices on the graphics card

}


void CCatmullRom::RenderCentreline()
{
	// Bind the VAO m_vaoCentreline and render it
	glBindVertexArray(m_vaoCentreline);

	//change the line size and point size so theyre more visible when rendered
	glLineWidth(10);
	glPointSize(5);

	//render the path as both points and as a line loop
	glDrawArrays(GL_POINTS, 0, m_centrelinePoints.size());
	glDrawArrays(GL_LINE_LOOP, 0, m_centrelinePoints.size());

}

void CCatmullRom::RenderOffsetCurves()
{
	// Bind the VAO m_vaoLeftOffsetCurve and render it
	glBindVertexArray(m_vaoLeftOffsetCurve);
	//change the line size and point size so theyre more visible when rendered
	glLineWidth(10);
	glPointSize(5);
	//render the path as both points and as a line loop
	glDrawArrays(GL_POINTS, 0, m_leftOffsetPoints.size());
	glDrawArrays(GL_LINE_LOOP, 0, m_leftOffsetPoints.size());

	// Bind the VAO m_vaoRightOffsetCurve and render it
	glBindVertexArray(m_vaoRightOffsetCurve);
	//change the line size and point size so theyre more visible when rendered
	glLineWidth(10);
	glPointSize(5);
	//render the path as both points and as a line loop
	glDrawArrays(GL_POINTS, 0, m_rightOffsetPoints.size());
	glDrawArrays(GL_LINE_LOOP, 0, m_rightOffsetPoints.size());
}


void CCatmullRom::RenderTrack()
{
	// Bind the VAO m_vaoTrack and render it
}

int CCatmullRom::CurrentLap(float d)
{

	return (int)(d / m_distances.back());

}

glm::vec3 CCatmullRom::_dummy_vector(0.0f, 0.0f, 0.0f);