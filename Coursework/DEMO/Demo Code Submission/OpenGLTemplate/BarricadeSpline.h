#pragma once
#include "Common.h"
#include "vertexBufferObject.h"
#include "vertexBufferObjectIndexed.h"
#include "Texture.h"


class CBarricadeSpline
{
public:
	CBarricadeSpline();
	~CBarricadeSpline();

	void CreateCentreline();

	void CreateOffsetCurves();

	void CreateLeftBarricade(string sDirectory, string sFilename, float fTextureRepeat);
	void CreateRightBarricade(string sDirectory, string sFilename, float fTextureRepeat);
	void RenderBarricades();

	bool Sample(float d, glm::vec3& p, glm::vec3& up = _dummy_vector); // Return a point on the centreline based on a certain distance along the control curve.

private:

	void SetControlPoints();
	void ComputeLengthsAlongControlPoints();
	void UniformlySampleControlPoints(int numSamples);
	glm::vec3 Interpolate(glm::vec3& p0, glm::vec3& p1, glm::vec3& p2, glm::vec3& p3, float t);

	vector<float> m_distances;
	CTexture m_texture;

	GLuint m_vaoCentreline;
	GLuint m_vaoLeftOffsetCurve;
	GLuint m_vaoRightOffsetCurve;
	GLuint m_vaoLeftBarricade;
	GLuint m_vaoRightBarricade;

	static glm::vec3 _dummy_vector;
	vector<glm::vec3> m_controlPoints;		// Control points, which are interpolated to produce the centreline points
	vector<glm::vec3> m_controlUpVectors;	// Control upvectors, which are interpolated to produce the centreline upvectors
	vector<glm::vec3> m_centrelinePoints;	// Centreline points
	vector<glm::vec3> m_centrelineUpVectors;// Centreline upvectors

	vector<glm::vec3> m_leftOffsetPoints;	// Left offset curve points
	vector<glm::vec3> m_rightOffsetPoints;	// Right offset curve points

	vector<glm::vec3> m_leftBarricadePoints;
	vector<glm::vec3> m_rightBarricadePoints;

	vector<glm::vec3> m_leftBarricadeNormals;
	vector<glm::vec3> m_rightBarricadeNormals;

	unsigned int m_vertexCount;				// Number of vertices in the track VBO
	unsigned int m_barricadeCount;			// Number of vertices in both barricade vbos 

	int sampleNum = 1000;					// Number of uniformly created smaples stored in a variable for ease of use
	float barricadeHeight = 15;				// Height of barricades

	string m_directory;
	string m_filename;
};