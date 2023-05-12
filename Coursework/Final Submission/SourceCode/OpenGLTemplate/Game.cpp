/* 
OpenGL Template for INM376 / IN3005
City University London, School of Mathematics, Computer Science and Engineering
Source code drawn from a number of sources and examples, including contributions from
 - Ben Humphrey (gametutorials.com), Michal Bubner (mbsoftworks.sk), Christophe Riccio (glm.g-truc.net)
 - Christy Quinn, Sam Kellett and others

 For educational use by Department of Computer Science, City University London UK.

 This template contains a skybox, simple terrain, camera, lighting, shaders, texturing

 Potential ways to modify the code:  Add new geometry types, shaders, change the terrain, load new meshes, change the lighting, 
 different camera controls, different shaders, etc.
 
 Template version 5.0a 29/01/2017
 Dr Greg Slabaugh (gregory.slabaugh.1@city.ac.uk) 

 version 6.0a 29/01/2019
 Dr Eddie Edwards (Philip.Edwards@city.ac.uk)

 version 6.1a 13/02/2022 - Sorted out Release mode and a few small compiler warnings
 Dr Eddie Edwards (Philip.Edwards@city.ac.uk)

*/

#include "game.h"

// Setup includes
#include "HighResolutionTimer.h"
#include "GameWindow.h"

// Game includes
#include "Camera.h"
#include "Skybox.h"
#include "Shaders.h"
#include "FreeTypeFont.h"
#include "MatrixStack.h"
#include "OpenAssetImportMesh.h"
#include "TreeMesh.h"
#include "CatmullRom.h"
#include "BarricadeSpline.h"
#include "Tunnel.h"
#include "Overpass.h"
#include "HeightMapTerrain.h"
#include "FrameBufferObject.h"
#include "Plane.h"

// Constructor
Game::Game()
{
	m_pSkybox = NULL;
	m_pCamera = NULL;
	m_pShaderPrograms = NULL;
	m_pFtFont = NULL;
	m_pPlayerCarMesh = NULL;
	m_pCar1Mesh = NULL;
	m_pCar2Mesh = NULL;
	m_pCar3Mesh = NULL;
	m_pCar4Mesh = NULL;
	m_pTreeMesh = NULL;
	m_pHighResolutionTimer = NULL;
	m_pCatmullRom = NULL;
	m_pBarricadeSpline = NULL;
	m_pTunnel = NULL;
	m_pOverpass = NULL;
	m_pHeightMapTerrain = NULL;
	m_pFBO = NULL;
	m_pPlane = NULL;

	m_dt = 0.0;
	m_framesPerSecond = 0;
	m_frameCount = 0;
	m_elapsedTime = 0.0f;
	m_currentDistance = 0.0f;

	// Camera variables
	// set third person camera to true to start game on that camera
	m_firstCam = false;
	m_thirdCam = true;
	m_freeCam = false;

	// Player variables
	t = glm::vec3(0);
	n = glm::vec3(0);
	b = glm::vec3(0);

	m_playerPosition = glm::vec3(0);
	m_playerOrientation = glm::mat4(1);

	m_playerSpeed = 0.0f;
	m_playerTurn = 0.0f;
	m_playerRotation = 0.0f;

	m_points = 0.0f;
	m_pointMultiplier = 1.0f;
	m_health = 100;

	// Obstacle Cars
	// obstacle cars start at different points along the track
	m_car1Distance = 800.0f;
	m_car2Distance = 1600.0f;
	m_car3Distance = 2400.0f;
	m_car4Distance = 3200.0f;

	m_car1Position = glm::vec3(0);
	m_car1Orientation = glm::mat4(1);

	m_car2Position = glm::vec3(0);
	m_car2Orientation = glm::mat4(1);

	m_car3Position = glm::vec3(0);
	m_car3Orientation = glm::mat4(1);

	m_car4Position = glm::vec3(0);
	m_car4Orientation = glm::mat4(1);
}

// Destructor
Game::~Game() 
{ 
	//game objects
	delete m_pCamera;
	delete m_pSkybox;
	delete m_pFtFont;
	delete m_pPlayerCarMesh;
	delete m_pCar1Mesh;
	delete m_pCar2Mesh;
	delete m_pCar3Mesh;
	delete m_pCar4Mesh;
	delete m_pTreeMesh;
	delete m_pCatmullRom;
	delete m_pBarricadeSpline;
	delete m_pTunnel;
	delete m_pOverpass;
	delete m_pHeightMapTerrain;
	delete m_pFBO;
	delete m_pPlane;

	if (m_pShaderPrograms != NULL) {
		for (unsigned int i = 0; i < m_pShaderPrograms->size(); i++)
			delete (*m_pShaderPrograms)[i];
	}
	delete m_pShaderPrograms;

	//setup objects
	delete m_pHighResolutionTimer;
}

// Initialisation:  This method only runs once at startup
void Game::Initialise() 
{
	// Set the clear colour and depth
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClearDepth(1.0f);

	/// Create objects
	m_pCamera = new CCamera;
	m_pSkybox = new CSkybox;
	m_pShaderPrograms = new vector <CShaderProgram *>;
	m_pFtFont = new CFreeTypeFont;
	m_pPlayerCarMesh = new COpenAssetImportMesh;
	m_pCar1Mesh = new COpenAssetImportMesh;
	m_pCar2Mesh = new COpenAssetImportMesh;
	m_pCar3Mesh = new COpenAssetImportMesh;
	m_pCar4Mesh = new COpenAssetImportMesh;
	m_pTreeMesh = new CTreeMesh;
	m_pCatmullRom = new CCatmullRom;
	m_pBarricadeSpline = new CBarricadeSpline;
	m_pTunnel = new CTunnel;
	m_pOverpass = new COverpass;
	m_pHeightMapTerrain = new CHeightMapTerrain;
	m_pFBO = new CFrameBufferObject;
	m_pPlane = new CPlane;

	RECT dimensions = m_gameWindow.GetDimensions();

	int width = dimensions.right - dimensions.left;
	int height = dimensions.bottom - dimensions.top;

	// Set the orthographic and perspective projection matrices based on the image size
	m_pCamera->SetOrthographicProjectionMatrix(width, height); 
	m_pCamera->SetPerspectiveProjectionMatrix(45.0f, (float) width / (float) height, 0.1f, 5000.0f);

	// Load shaders
	vector<CShader> shShaders;
	vector<string> sShaderFileNames;
	sShaderFileNames.push_back("mainShader.vert");
	sShaderFileNames.push_back("mainShader.frag");

	sShaderFileNames.push_back("textShader.vert");
	sShaderFileNames.push_back("textShader.frag");

	sShaderFileNames.push_back("tunnelShader.vert");
	sShaderFileNames.push_back("tunnelShader.frag");

	// Overpass Tesselation shaders CURRENTLY BROKEN
	// Overpass rendered using tunnel shader as of right now
	sShaderFileNames.push_back("overpassShader.vert");
	sShaderFileNames.push_back("overpassTessControl.tcnl");
	sShaderFileNames.push_back("overpassTessEval.tese");
	sShaderFileNames.push_back("overpassShader.frag");

	sShaderFileNames.push_back("treeShader.vert");
	sShaderFileNames.push_back("treeShader.frag");

	sShaderFileNames.push_back("carShader.vert");
	sShaderFileNames.push_back("carShader.frag");


	for (int i = 0; i < (int) sShaderFileNames.size(); i++) {
		string sExt = sShaderFileNames[i].substr((int) sShaderFileNames[i].size()-4, 4);
		int iShaderType;
		if (sExt == "vert") iShaderType = GL_VERTEX_SHADER;
		else if (sExt == "frag") iShaderType = GL_FRAGMENT_SHADER;
		else if (sExt == "geom") iShaderType = GL_GEOMETRY_SHADER;
		else if (sExt == "tcnl") iShaderType = GL_TESS_CONTROL_SHADER;
		else iShaderType = GL_TESS_EVALUATION_SHADER;
		CShader shader;
		shader.LoadShader("resources\\shaders\\"+sShaderFileNames[i], iShaderType);
		shShaders.push_back(shader);
	}

	// Create an FBO
	m_pFBO->Create(width, height);

	// Create the main shader program
	CShaderProgram *pMainProgram = new CShaderProgram;
	pMainProgram->CreateProgram();
	pMainProgram->AddShaderToProgram(&shShaders[0]);
	pMainProgram->AddShaderToProgram(&shShaders[1]);
	pMainProgram->LinkProgram();
	m_pShaderPrograms->push_back(pMainProgram);

	// Create a shader program for fonts
	CShaderProgram *pFontProgram = new CShaderProgram;
	pFontProgram->CreateProgram();
	pFontProgram->AddShaderToProgram(&shShaders[2]);
	pFontProgram->AddShaderToProgram(&shShaders[3]);
	pFontProgram->LinkProgram();
	m_pShaderPrograms->push_back(pFontProgram);

	// Create a tunnel shader program
	CShaderProgram *pTunnelProgram = new CShaderProgram;
	pTunnelProgram->CreateProgram();
	pTunnelProgram->AddShaderToProgram(&shShaders[4]);
	pTunnelProgram->AddShaderToProgram(&shShaders[5]);
	pTunnelProgram->LinkProgram();
	m_pShaderPrograms->push_back(pTunnelProgram);

	// Create an overpass shader program
	CShaderProgram *pOverpassProgram = new CShaderProgram;
	pOverpassProgram->CreateProgram();
	pOverpassProgram->AddShaderToProgram(&shShaders[6]);
	pOverpassProgram->AddShaderToProgram(&shShaders[7]);
	pOverpassProgram->AddShaderToProgram(&shShaders[8]);
	pOverpassProgram->AddShaderToProgram(&shShaders[9]);
	pOverpassProgram->LinkProgram();
	m_pShaderPrograms->push_back(pOverpassProgram);

	// Create a tree shader program
	CShaderProgram *pTreeProgram = new CShaderProgram;
	pTreeProgram->CreateProgram();
	pTreeProgram->AddShaderToProgram(&shShaders[10]);
	pTreeProgram->AddShaderToProgram(&shShaders[11]);
	pTreeProgram->LinkProgram();
	m_pShaderPrograms->push_back(pTreeProgram);

	// Create a car shader program
	CShaderProgram *pCarProgram = new CShaderProgram;
	pCarProgram->CreateProgram();
	pCarProgram->AddShaderToProgram(&shShaders[12]);
	pCarProgram->AddShaderToProgram(&shShaders[13]);
	pCarProgram->LinkProgram();
	m_pShaderPrograms->push_back(pCarProgram);

	// You can follow this pattern to load additional shaders

	// Enabling MSAA
	glEnable(GL_MULTISAMPLE);

	// Enabling Cull Face
	glEnable(GL_CULL_FACE);

	// Create the skybox
	// Skybox downloaded from https://opengameart.org/content/mountain-skyboxes
	m_pSkybox->Create(2500.0f);

	// The height map was created by myself
	// The grass texture is from: https://opengameart.org/content/grass-texture-0 downloaded on 3rd Apr 2023
	m_pHeightMapTerrain->Create("resources\\textures\\terrainNew1.bmp", "resources\\textures\\grass3.png", glm::vec3(0, 0, 0), 2000.0f, 2000.0f, 75.f);

	m_pFtFont->LoadSystemFont("arial.ttf", 32);
	m_pFtFont->SetShaderProgram(pFontProgram);

	// Load some meshes in OBJ format
	m_pPlayerCarMesh->Load("resources\\models\\Cars\\obj\\car-coupe-blue.obj"); // downloaded from: https://opengameart.org/content/vehicles-assets-pt1
	m_pTreeMesh->Load("resources\\models\\Tree\\tree.obj"); // downloaded from: https://opengameart.org/content/lowpoly-tree
	m_pCar1Mesh->Load("resources\\models\\Cars\\obj\\car-van-silver.obj"); //downloaded from: https://opengameart.org/content/vehicles-assets-pt1
	m_pCar2Mesh->Load("resources\\models\\Cars\\obj\\car-pickup-violet.obj"); //downloaded from: https://opengameart.org/content/vehicles-assets-pt1
	m_pCar3Mesh->Load("resources\\models\\Cars\\obj\\car-hatchback-red.obj"); //downloaded from: https://opengameart.org/content/vehicles-assets-pt1
	m_pCar4Mesh->Load("resources\\models\\Cars\\obj\\car-normal-green.obj"); //downloaded from: https://opengameart.org/content/vehicles-assets-pt1

	//tunnel texture downloaded from: https://opengameart.org/node/7651 on 11th Mar 2023
	m_pTunnel->Create("resources\\textures\\5sqtunnelroaddark.jpg", 5.0f);

	// overpass texture downloaded from: https://opengameart.org/node/49685
	m_pOverpass->Create("resources\\textures\\tex-13_spec.jpg", 1.0f);

	//initialise centreline for the track
	m_pCatmullRom->CreateCentreline();
	//initialise offset curves for the track
	m_pCatmullRom->CreateOffsetCurves();
	//initialise track, with texture
	m_pCatmullRom->CreateTrack("resources\\textures\\", "01tizeta_asphalts2.png", 0.1f); // from https://opengameart.org/content/black-asphalt-tilling-256px

	// Due to the fact that only 1 texture can be applied for an object of one class, 
	// i decided to create another almost identical catmullRom spline class to create the barricades
	// this will let me give the barricades a different texture to the track
	m_pBarricadeSpline->CreateCentreline();
	m_pBarricadeSpline->CreateOffsetCurves();
	m_pBarricadeSpline->CreateLeftBarricade("resources\\textures\\", "doortile.png", 0.1f); // from https://opengameart.org/content/seamless-metal-door-texture
	m_pBarricadeSpline->CreateRightBarricade("resources\\textures\\", "doortile.png", 0.1f); // from https://opengameart.org/content/seamless-metal-door-texture
}

// Render method runs repeatedly in a loop
void Game::RenderScene(int pass)
{
	// Clear the buffers and enable depth testing (z-buffering)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	// Set up a matrix stack
	glutil::MatrixStack modelViewMatrixStack;
	modelViewMatrixStack.SetIdentity();

	// Use the main shader program 
	CShaderProgram* pMainProgram = (*m_pShaderPrograms)[0];
	pMainProgram->UseProgram();
	pMainProgram->SetUniform("bUseTexture", true);
	pMainProgram->SetUniform("sampler0", 0);
	// Note: cubemap and non-cubemap textures should not be mixed in the same texture unit.  Setting unit 10 to be a cubemap texture.
	int cubeMapTextureUnit = 10;
	pMainProgram->SetUniform("CubeMapTex", cubeMapTextureUnit);

	// Set the projection matrix
	pMainProgram->SetUniform("matrices.projMatrix", m_pCamera->GetPerspectiveProjectionMatrix());
	// Set previous Matrix in order to send to shader program for motion blur. Motion blur currently not working
	glm::mat4* prevMatrix = m_pCamera->GetPerspectiveProjectionMatrix();

	// Call LookAt to create the view matrix and put this on the modelViewMatrix stack. 
	// Store the view matrix and the normal matrix associated with the view matrix for later (they're useful for lighting -- since lighting is done in eye coordinates)
	modelViewMatrixStack.LookAt(m_pCamera->GetPosition(), m_pCamera->GetView(), m_pCamera->GetUpVector());
	glm::mat4 viewMatrix = modelViewMatrixStack.Top();
	glm::mat3 viewNormalMatrix = m_pCamera->ComputeNormalMatrix(viewMatrix);
	
	// Set light and materials in main shader program
	glm::vec4 lightPosition1 = glm::vec4(0, 100, -1500, 1); // Position of light source *in world coordinates*
	glm::vec3 lightPosVec3 = glm::vec3(0, 100, -1500);
	pMainProgram->SetUniform("light1.position", viewMatrix*lightPosition1); // Position of light source *in eye coordinates*
	pMainProgram->SetUniform("light1.La", glm::vec3(1.0f));		// Ambient colour of light
	pMainProgram->SetUniform("light1.Ld", glm::vec3(1.0f));		// Diffuse colour of light
	pMainProgram->SetUniform("light1.Ls", glm::vec3(1.0f));		// Specular colour of light
	pMainProgram->SetUniform("material1.Ma", glm::vec3(1.0f));	// Ambient material reflectance
	pMainProgram->SetUniform("material1.Md", glm::vec3(0.0f));	// Diffuse material reflectance
	pMainProgram->SetUniform("material1.Ms", glm::vec3(0.0f));	// Specular material reflectance
	pMainProgram->SetUniform("material1.shininess", 15.0f);		// Shininess material property

	// Render the skybox and terrain with full ambient reflectance 
	modelViewMatrixStack.Push();
		pMainProgram->SetUniform("renderSkybox", true);
		// Translate the modelview matrix to the camera eye point so skybox stays centred around camera
		glm::vec3 vEye = m_pCamera->GetPosition();
		modelViewMatrixStack.Translate(vEye);
		pMainProgram->SetUniform("matrices.modelViewMatrix", modelViewMatrixStack.Top());
		pMainProgram->SetUniform("matrices.normalMatrix", m_pCamera->ComputeNormalMatrix(modelViewMatrixStack.Top()));
		m_pSkybox->Render(cubeMapTextureUnit);
		pMainProgram->SetUniform("renderSkybox", false);
	modelViewMatrixStack.Pop();

	// Render the height mapped terrain
	modelViewMatrixStack.Push();
		modelViewMatrixStack.Translate(glm::vec3(0.0f, 0.0f, 0.0f));
		pMainProgram->SetUniform("matrices.modelViewMatrix", modelViewMatrixStack.Top());
		pMainProgram->SetUniform("matrices.normalMatrix", m_pCamera->ComputeNormalMatrix(modelViewMatrixStack.Top()));
		m_pHeightMapTerrain->Render();
	modelViewMatrixStack.Pop();
	

	// Turn on diffuse + specular materials
	pMainProgram->SetUniform("material1.Ma", glm::vec3(0.5f));	// Ambient material reflectance
	pMainProgram->SetUniform("material1.Md", glm::vec3(0.5f));	// Diffuse material reflectance
	pMainProgram->SetUniform("material1.Ms", glm::vec3(1.0f));	// Specular material reflectance

	//Render the players car
	modelViewMatrixStack.Push();
		modelViewMatrixStack.Translate(m_playerPosition);
		modelViewMatrixStack *= m_playerOrientation;
		modelViewMatrixStack.Scale(glm::vec3(1.75f));
		modelViewMatrixStack.Rotate(glm::vec3(0,1,0), glm::radians(m_playerRotation));
		pMainProgram->SetUniform("bUseTexture", true); // turn on/off texturing
		pMainProgram->SetUniform("matrices.modelViewMatrix", modelViewMatrixStack.Top());
		pMainProgram->SetUniform("matrices.normalMatrix", m_pCamera->ComputeNormalMatrix(modelViewMatrixStack.Top()));
		// Render your object here
		m_pPlayerCarMesh->Render();
	modelViewMatrixStack.Pop();

	//Render the track
	modelViewMatrixStack.Push();
		pMainProgram->SetUniform("bUseTexture", true); // turn on/off texturing
		pMainProgram->SetUniform("matrices.modelViewMatrix", modelViewMatrixStack.Top());
		pMainProgram->SetUniform("matrices.normalMatrix", m_pCamera->ComputeNormalMatrix(modelViewMatrixStack.Top()));
		// Render your object here
		m_pCatmullRom->RenderTrack();
	modelViewMatrixStack.Pop();

	// Render the barricades
	// Disable and enable GL_CULL_FACE in order to draw both sides of the barricades
	glDisable(GL_CULL_FACE);
	modelViewMatrixStack.Push();
		pMainProgram->SetUniform("bUseTexture", true); // turn on/off texturing
		pMainProgram->SetUniform("matrices.modelViewMatrix", modelViewMatrixStack.Top());
		pMainProgram->SetUniform("matrices.normalMatrix", m_pCamera->ComputeNormalMatrix(modelViewMatrixStack.Top()));
		// Render your object here
		m_pBarricadeSpline->RenderBarricades();
	modelViewMatrixStack.Pop();
	glEnable(GL_CULL_FACE);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Use the tunnel shader program 
	CShaderProgram *pTunnelProgram = (*m_pShaderPrograms)[2];
	pTunnelProgram->UseProgram();
	pTunnelProgram->SetUniform("bUseTexture", true);
	pTunnelProgram->SetUniform("sampler0", 0);

	// Set the projection matrix
	pTunnelProgram->SetUniform("matrices.projMatrix", m_pCamera->GetPerspectiveProjectionMatrix());

	// Set world light and materials of tunnels in tunnel shader program
	pTunnelProgram->SetUniform("light[0].position", viewMatrix * lightPosition1);	// Position of light source *in eye coordinates*
	pTunnelProgram->SetUniform("light[0].La", glm::vec3(1));						// Ambient colour of light
	pTunnelProgram->SetUniform("light[0].Ld", glm::vec3(1));						// Diffuse colour of light
	pTunnelProgram->SetUniform("light[0].Ls", glm::vec3(1));						// Specular colour of light
	pTunnelProgram->SetUniform("material1.Ma", glm::vec3(0.3f, 0.3f, 0.3f));		// materials ambient colour
	pTunnelProgram->SetUniform("material1.Md", glm::vec3(0.3f, 0.3f, 0.3f));		// materials diffuse colour
	pTunnelProgram->SetUniform("material1.Ms", glm::vec3(1.0f, 1.0f, 1.0f));		// materials specular colour
	pTunnelProgram->SetUniform("material1.shininess", 15.0f);						// Shininess material property
	glm::vec3 direction = (glm::vec3(0,0,0) - lightPosVec3);						// vector to work out world lights direction
	pTunnelProgram->SetUniform("light[0].direction", glm::normalize(viewNormalMatrix * direction)); // world light direction
	pTunnelProgram->SetUniform("light[0].exponent", 200.0f);						// world light exponent
	pTunnelProgram->SetUniform("light[0].cutoff", 89.0f);							// world light cutoff


	// the headlamps position and directions are set relative to the player position and orientation given by the TNB frame in the update method
	// Set the first headlamp light position, ambient, diffuse, specular, direction, expoenet, cutoff
	pTunnelProgram->SetUniform("light[1].position", viewMatrix * glm::vec4(m_playerPosition + (n * 30.0f), 1.0f)); // Light position in eye coordinates
	pTunnelProgram->SetUniform("light[1].La", glm::vec3(0.8f, 0.8f, 0.0f));
	pTunnelProgram->SetUniform("light[1].Ld", glm::vec3(0.8f, 0.8f, 0.0f));
	pTunnelProgram->SetUniform("light[1].Ls", glm::vec3(0.8f, 0.8f, 0.0f));
	pTunnelProgram->SetUniform("light[1].direction", glm::normalize(viewNormalMatrix * (t - (b * 0.2f))));
	pTunnelProgram->SetUniform("light[1].exponent", 2.0f);
	pTunnelProgram->SetUniform("light[1].cutoff", 30.0f);

	// Set the second headlamp light position, ambient, diffuse, specular, direction, expoenet, cutoff
	pTunnelProgram->SetUniform("light[2].position", viewMatrix * glm::vec4(m_playerPosition - (n * 30.0f), 1.0f)); // Light position in eye coordinates
	pTunnelProgram->SetUniform("light[2].La", glm::vec3(0.8f, 0.8f, 0.0f));
	pTunnelProgram->SetUniform("light[2].Ld", glm::vec3(0.8f, 0.8f, 0.0f));
	pTunnelProgram->SetUniform("light[2].Ls", glm::vec3(0.8f, 0.8f, 0.0));
	pTunnelProgram->SetUniform("light[2].direction", glm::normalize(viewNormalMatrix * (t - (b * 0.2f))));
	pTunnelProgram->SetUniform("light[2].exponent", 2.0f);
	pTunnelProgram->SetUniform("light[2].cutoff", 30.0f);

	// render tunnel after turn 1
	modelViewMatrixStack.Push();
		modelViewMatrixStack.Translate(glm::vec3(300,85,-850));
		modelViewMatrixStack.Rotate(glm::vec3(0,1,0), glm::radians(91.0f));
		modelViewMatrixStack.Scale(glm::vec3(10,10,50));
		pTunnelProgram->SetUniform("matrices.modelViewMatrix", modelViewMatrixStack.Top());
		pTunnelProgram->SetUniform("matrices.normalMatrix", m_pCamera->ComputeNormalMatrix(modelViewMatrixStack.Top()));
		pTunnelProgram->SetUniform("bUseTexture", true); // turn on/off texturing
		m_pTunnel->Render();
	modelViewMatrixStack.Pop();

	// render tunnel after hairpin
	modelViewMatrixStack.Push();
		modelViewMatrixStack.Translate(glm::vec3(-790, 20, 685));
		modelViewMatrixStack.Rotate(glm::vec3(0, 1, 0), glm::radians(-16.f));
		modelViewMatrixStack.Scale(glm::vec3(10, 10, 45));
		pTunnelProgram->SetUniform("matrices.modelViewMatrix", modelViewMatrixStack.Top());
		pTunnelProgram->SetUniform("matrices.normalMatrix", m_pCamera->ComputeNormalMatrix(modelViewMatrixStack.Top()));
		pTunnelProgram->SetUniform("bUseTexture", true); // turn on/off texturing
		m_pTunnel->Render();
	modelViewMatrixStack.Pop();

	// render overpass between tunnel
	modelViewMatrixStack.Push();
		modelViewMatrixStack.Translate(glm::vec3(-820, 70, -500));
		modelViewMatrixStack.Rotate(glm::vec3(0,1,0), glm::radians(-40.0f));
		modelViewMatrixStack.Scale(glm::vec3(3, 2, 2));
		pTunnelProgram->SetUniform("matrices.modelViewMatrix", modelViewMatrixStack.Top());
		pTunnelProgram->SetUniform("matrices.normalMatrix", m_pCamera->ComputeNormalMatrix(modelViewMatrixStack.Top()));
		pTunnelProgram->SetUniform("bUseTexture", true); // turn on/off texturing
		m_pOverpass->Render();
	modelViewMatrixStack.Pop();

	// render overpass in final sector
	modelViewMatrixStack.Push();
		modelViewMatrixStack.Translate(glm::vec3(20, 70, 1000));
		modelViewMatrixStack.Rotate(glm::vec3(0, 1, 0), glm::radians(90.0f));
		modelViewMatrixStack.Scale(glm::vec3(3, 2, 2));
		pTunnelProgram->SetUniform("matrices.modelViewMatrix", modelViewMatrixStack.Top());
		pTunnelProgram->SetUniform("matrices.normalMatrix", m_pCamera->ComputeNormalMatrix(modelViewMatrixStack.Top()));
		pTunnelProgram->SetUniform("bUseTexture", true); // turn on/off texturing
		m_pOverpass->Render();
	modelViewMatrixStack.Pop();

	// render overpass at last corner
	modelViewMatrixStack.Push();
		modelViewMatrixStack.Translate(glm::vec3(675, 70, 500));
		modelViewMatrixStack.Rotate(glm::vec3(0, 1, 0), glm::radians(120.0f));
		modelViewMatrixStack.Scale(glm::vec3(3, 3, 2));
		pTunnelProgram->SetUniform("matrices.modelViewMatrix", modelViewMatrixStack.Top());
		pTunnelProgram->SetUniform("matrices.normalMatrix", m_pCamera->ComputeNormalMatrix(modelViewMatrixStack.Top()));
		pTunnelProgram->SetUniform("bUseTexture", true); // turn on/off texturing
		m_pOverpass->Render();
	modelViewMatrixStack.Pop();

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Use the overpass shader program 
	/// CURRENTLY BROKEN	
	/*
	CShaderProgram* pOverpassProgram = (*m_pShaderPrograms)[3];
	pOverpassProgram->UseProgram();
	pOverpassProgram->SetUniform("bUseTexture", true);
	pOverpassProgram->SetUniform("sampler0", 0);

	// Set the projection matrix
	pOverpassProgram->SetUniform("MVP", m_pCamera->GetPerspectiveProjectionMatrix());

	// Set light and materials in tunnel shader program
	pOverpassProgram->SetUniform("light1.position", viewMatrix* lightPosition1); // Position of light source *in eye coordinates*
	pOverpassProgram->SetUniform("light1.La", glm::vec3(1, 1, 1));	// Ambient colour of light
	pOverpassProgram->SetUniform("light1.Ld", glm::vec3(1, 1, 1));	// Diffuse colour of light
	pOverpassProgram->SetUniform("light1.Ls", glm::vec3(1, 1, 1));	// Specular colour of light
	pOverpassProgram->SetUniform("material1.shininess", 40.0f);		// Shininess material property

	// render overpass
	modelViewMatrixStack.Push();
		modelViewMatrixStack.Translate(glm::vec3(200, 200, 0));
		modelViewMatrixStack.Scale(glm::vec3(1, 1, 1));
		pOverpassProgram->SetUniform("TessLevel", 4);
		pOverpassProgram->SetUniform("ModelViewMatrix", modelViewMatrixStack.Top());
		pOverpassProgram->SetUniform("NormalMatrix", m_pCamera->ComputeNormalMatrix(modelViewMatrixStack.Top()));
		pOverpassProgram->SetUniform("bUseTexture", true); // turn on/off texturing
		m_pOverpass->Render();
	modelViewMatrixStack.Pop();
	*/
	

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Use the tree shader program 

	// Use the tree shader program 
	CShaderProgram* pTreeProgram = (*m_pShaderPrograms)[4];
	pTreeProgram->UseProgram();
	pTreeProgram->SetUniform("bUseTexture", true);
	pTreeProgram->SetUniform("sampler0", 0);

	// Set the projection matrix
	pTreeProgram->SetUniform("matrices.projMatrix", m_pCamera->GetPerspectiveProjectionMatrix());

	// Set light and materials in tree shader program
	pTreeProgram->SetUniform("light1.position", viewMatrix* lightPosition1); // Position of light source *in eye coordinates*
	pTreeProgram->SetUniform("light1.La", glm::vec3(1, 1, 1));	// Ambient colour of light
	pTreeProgram->SetUniform("light1.Ld", glm::vec3(1, 1, 1));	// Diffuse colour of light
	pTreeProgram->SetUniform("light1.Ls", glm::vec3(1, 1, 1));	// Specular colour of light
	pTreeProgram->SetUniform("material1.Ma", glm::vec3(0.5f));	// Ambient material reflectance
	pTreeProgram->SetUniform("material1.Md", glm::vec3(0.5f));	// Diffuse material reflectance
	pTreeProgram->SetUniform("material1.Ms", glm::vec3(1.0f));	// Specular material reflectance
	pTreeProgram->SetUniform("material1.shininess", 15.0f);		// Shininess material property
		
	//Render the trees 1
	modelViewMatrixStack.Push();
		modelViewMatrixStack.Translate(glm::vec3(-900, 120, -900));
		modelViewMatrixStack.Scale(glm::vec3(10, 10, 10));
		pTreeProgram->SetUniform("bUseTexture", true); // turn on/off texturing
		pTreeProgram->SetUniform("matrices.modelViewMatrix", modelViewMatrixStack.Top());
		pTreeProgram->SetUniform("matrices.normalMatrix", m_pCamera->ComputeNormalMatrix(modelViewMatrixStack.Top()));
		// Render your object here
		m_pTreeMesh->Render();
	modelViewMatrixStack.Pop();

	//Render the trees 2
	modelViewMatrixStack.Push();
		modelViewMatrixStack.Translate(glm::vec3(-300, 120, -700));
		modelViewMatrixStack.Scale(glm::vec3(10, 10, 10));
		pTreeProgram->SetUniform("bUseTexture", true); // turn on/off texturing
		pTreeProgram->SetUniform("matrices.modelViewMatrix", modelViewMatrixStack.Top());
		pTreeProgram->SetUniform("matrices.normalMatrix", m_pCamera->ComputeNormalMatrix(modelViewMatrixStack.Top()));
		// Render your object here
		m_pTreeMesh->Render();
	modelViewMatrixStack.Pop();

	//Render the trees 3 
	modelViewMatrixStack.Push();
		modelViewMatrixStack.Translate(glm::vec3(0, 120, -800));
		modelViewMatrixStack.Scale(glm::vec3(10, 10, 10));
		pTreeProgram->SetUniform("bUseTexture", true); // turn on/off texturing
		pTreeProgram->SetUniform("matrices.modelViewMatrix", modelViewMatrixStack.Top());
		pTreeProgram->SetUniform("matrices.normalMatrix", m_pCamera->ComputeNormalMatrix(modelViewMatrixStack.Top()));
		// Render your object here
		m_pTreeMesh->Render();
	modelViewMatrixStack.Pop();

	//Render the trees 4
	modelViewMatrixStack.Push();
		modelViewMatrixStack.Translate(glm::vec3(350, 120, -600));
		modelViewMatrixStack.Scale(glm::vec3(10, 10, 10));
		pTreeProgram->SetUniform("bUseTexture", true); // turn on/off texturing
		pTreeProgram->SetUniform("matrices.modelViewMatrix", modelViewMatrixStack.Top());
		pTreeProgram->SetUniform("matrices.normalMatrix", m_pCamera->ComputeNormalMatrix(modelViewMatrixStack.Top()));
		// Render your object here
		m_pTreeMesh->Render();
	modelViewMatrixStack.Pop();

	//Render the trees 5
	modelViewMatrixStack.Push();
		modelViewMatrixStack.Translate(glm::vec3(800, 120, -1200));
		modelViewMatrixStack.Scale(glm::vec3(10, 10, 10));
		pTreeProgram->SetUniform("bUseTexture", true); // turn on/off texturing
		pTreeProgram->SetUniform("matrices.modelViewMatrix", modelViewMatrixStack.Top());
		pTreeProgram->SetUniform("matrices.normalMatrix", m_pCamera->ComputeNormalMatrix(modelViewMatrixStack.Top()));
		// Render your object here
		m_pTreeMesh->Render();
	modelViewMatrixStack.Pop();

	//Render the trees 6
	modelViewMatrixStack.Push();
		modelViewMatrixStack.Translate(glm::vec3(350, 120, -200));
		modelViewMatrixStack.Scale(glm::vec3(10, 10, 10));
		pTreeProgram->SetUniform("bUseTexture", true); // turn on/off texturing
		pTreeProgram->SetUniform("matrices.modelViewMatrix", modelViewMatrixStack.Top());
		pTreeProgram->SetUniform("matrices.normalMatrix", m_pCamera->ComputeNormalMatrix(modelViewMatrixStack.Top()));
		// Render your object here
		m_pTreeMesh->Render();
	modelViewMatrixStack.Pop();

	//Render the trees 7
	modelViewMatrixStack.Push();
		modelViewMatrixStack.Translate(glm::vec3(350, 120, -600));
		modelViewMatrixStack.Scale(glm::vec3(10, 10, 10));
		pTreeProgram->SetUniform("bUseTexture", true); // turn on/off texturing
		pTreeProgram->SetUniform("matrices.modelViewMatrix", modelViewMatrixStack.Top());
		pTreeProgram->SetUniform("matrices.normalMatrix", m_pCamera->ComputeNormalMatrix(modelViewMatrixStack.Top()));
		// Render your object here
		m_pTreeMesh->Render();
	modelViewMatrixStack.Pop();

	//Render the trees 8
	modelViewMatrixStack.Push();
		modelViewMatrixStack.Translate(glm::vec3(0, 120, -400));
		modelViewMatrixStack.Scale(glm::vec3(10, 10, 10));
		pTreeProgram->SetUniform("bUseTexture", true); // turn on/off texturing
		pTreeProgram->SetUniform("matrices.modelViewMatrix", modelViewMatrixStack.Top());
		pTreeProgram->SetUniform("matrices.normalMatrix", m_pCamera->ComputeNormalMatrix(modelViewMatrixStack.Top()));
		// Render your object here
		m_pTreeMesh->Render();
	modelViewMatrixStack.Pop();

	//Render the trees 9
	modelViewMatrixStack.Push();
	modelViewMatrixStack.Translate(glm::vec3(-500, 120, -400));
	modelViewMatrixStack.Scale(glm::vec3(10, 10, 10));
	pTreeProgram->SetUniform("bUseTexture", true); // turn on/off texturing
	pTreeProgram->SetUniform("matrices.modelViewMatrix", modelViewMatrixStack.Top());
	pTreeProgram->SetUniform("matrices.normalMatrix", m_pCamera->ComputeNormalMatrix(modelViewMatrixStack.Top()));
	// Render your object here
	m_pTreeMesh->Render();
	modelViewMatrixStack.Pop();

	//Render the trees 10
	modelViewMatrixStack.Push();
		modelViewMatrixStack.Translate(glm::vec3(-1000, -45, 400));
		modelViewMatrixStack.Scale(glm::vec3(10, 10, 10));
		pTreeProgram->SetUniform("bUseTexture", true); // turn on/off texturing
		pTreeProgram->SetUniform("matrices.modelViewMatrix", modelViewMatrixStack.Top());
		pTreeProgram->SetUniform("matrices.normalMatrix", m_pCamera->ComputeNormalMatrix(modelViewMatrixStack.Top()));
		// Render your object here
		m_pTreeMesh->Render();
	modelViewMatrixStack.Pop();

	//Render the trees 11
	modelViewMatrixStack.Push();
		modelViewMatrixStack.Translate(glm::vec3(-300, -18, 380));
		modelViewMatrixStack.Scale(glm::vec3(10, 10, 10));
		pTreeProgram->SetUniform("bUseTexture", true); // turn on/off texturing
		pTreeProgram->SetUniform("matrices.modelViewMatrix", modelViewMatrixStack.Top());
		pTreeProgram->SetUniform("matrices.normalMatrix", m_pCamera->ComputeNormalMatrix(modelViewMatrixStack.Top()));
		// Render your object here
		m_pTreeMesh->Render();
	modelViewMatrixStack.Pop();

	//Render the trees 12
	modelViewMatrixStack.Push();
		modelViewMatrixStack.Translate(glm::vec3(600, 120, 600));
		modelViewMatrixStack.Scale(glm::vec3(10, 10, 10));
		pTreeProgram->SetUniform("bUseTexture", true); // turn on/off texturing
		pTreeProgram->SetUniform("matrices.modelViewMatrix", modelViewMatrixStack.Top());
		pTreeProgram->SetUniform("matrices.normalMatrix", m_pCamera->ComputeNormalMatrix(modelViewMatrixStack.Top()));
		// Render your object here
		m_pTreeMesh->Render();
	modelViewMatrixStack.Pop();		


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Use the car shader program

	// Use the car shader program 
	CShaderProgram *pCarProgram = (*m_pShaderPrograms)[4];
	pCarProgram->UseProgram();
	pCarProgram->SetUniform("bUseTexture", true);
	pCarProgram->SetUniform("sampler0", 0);

	// Set the projection matrix
	pCarProgram->SetUniform("matrices.projMatrix", m_pCamera->GetPerspectiveProjectionMatrix());

	// Set light and materials in tree shader program
	pCarProgram->SetUniform("light1.position", viewMatrix * lightPosition1); // Position of light source *in eye coordinates*
	pCarProgram->SetUniform("light1.La", glm::vec3(1, 1, 1));	// Ambient colour of light
	pCarProgram->SetUniform("light1.Ld", glm::vec3(1, 1, 1));	// Diffuse colour of light
	pCarProgram->SetUniform("light1.Ls", glm::vec3(1, 1, 1));	// Specular colour of light
	pCarProgram->SetUniform("material1.Ma", glm::vec3(0.5f));	// Ambient material reflectance
	pCarProgram->SetUniform("material1.Md", glm::vec3(0.5f));	// Diffuse material reflectance
	pCarProgram->SetUniform("material1.Ms", glm::vec3(1.0f));	// Specular material reflectance
	pCarProgram->SetUniform("material1.shininess", 15.0f);		// Shininess material property

	//Render the obstacle car 1
	modelViewMatrixStack.Push();
		modelViewMatrixStack.Translate(m_car1Position);
		modelViewMatrixStack *= m_car1Orientation;
		modelViewMatrixStack.Scale(glm::vec3(1.75f));
		pCarProgram->SetUniform("bUseTexture", true); // turn on/off texturing
		pCarProgram->SetUniform("matrices.modelViewMatrix", modelViewMatrixStack.Top());
		pCarProgram->SetUniform("matrices.normalMatrix", m_pCamera->ComputeNormalMatrix(modelViewMatrixStack.Top()));
		// Render your object here
		m_pCar1Mesh->Render();
	modelViewMatrixStack.Pop();

	//Render the obstacle car 2
	modelViewMatrixStack.Push();
		modelViewMatrixStack.Translate(m_car2Position);
		modelViewMatrixStack *= m_car2Orientation;
		modelViewMatrixStack.Scale(glm::vec3(1.75f));
		pCarProgram->SetUniform("bUseTexture", true); // turn on/off texturing
		pCarProgram->SetUniform("matrices.modelViewMatrix", modelViewMatrixStack.Top());
		pCarProgram->SetUniform("matrices.normalMatrix", m_pCamera->ComputeNormalMatrix(modelViewMatrixStack.Top()));
		// Render your object here
		m_pCar2Mesh->Render();
	modelViewMatrixStack.Pop();

	//Render the obstacle car 3
	modelViewMatrixStack.Push();
		modelViewMatrixStack.Translate(m_car3Position);
		modelViewMatrixStack *= m_car3Orientation;
		modelViewMatrixStack.Scale(glm::vec3(1.75f));
		pCarProgram->SetUniform("bUseTexture", true); // turn on/off texturing
		pCarProgram->SetUniform("matrices.modelViewMatrix", modelViewMatrixStack.Top());
		pCarProgram->SetUniform("matrices.normalMatrix", m_pCamera->ComputeNormalMatrix(modelViewMatrixStack.Top()));
		// Render your object here
		m_pCar3Mesh->Render();
	modelViewMatrixStack.Pop();

	//Render the obstacle car 4
	modelViewMatrixStack.Push();
		modelViewMatrixStack.Translate(m_car4Position);
		modelViewMatrixStack *= m_car4Orientation;
		modelViewMatrixStack.Scale(glm::vec3(1.75f));
		pCarProgram->SetUniform("bUseTexture", true); // turn on/off texturing
		pCarProgram->SetUniform("matrices.modelViewMatrix", modelViewMatrixStack.Top());
		pCarProgram->SetUniform("matrices.normalMatrix", m_pCamera->ComputeNormalMatrix(modelViewMatrixStack.Top()));
		// Render your object here
		m_pCar4Mesh->Render();
	modelViewMatrixStack.Pop();

	// Motion Blur attempt
	// CURRENTLY BROKEN
	// On second pass render a plane to display motion blur
	/*
	if (pass == 1)
	{
		modelViewMatrixStack.Push();
			modelViewMatrixStack.Translate(t * 3.0f);
			modelViewMatrixStack.Rotate(glm::vec3(1.0f, 0.0f, 0.0f), 90.0);
			modelViewMatrixStack.Rotate(glm::vec3(0.0f, 0.0f, 1.0f), 180.0);
			modelViewMatrixStack *= m_playerOrientation;
			modelViewMatrixStack.Scale(-1.0);
			pCarProgram->SetUniform("sampler0", 0);
			pCarProgram->SetUniform("sampler1", 1);
			pCarProgram->SetUniform("invMVP", glm::inverse(*m_pCamera->GetPerspectiveProjectionMatrix()));
			pCarProgram->SetUniform("prevMVP", prevMatrix);
			pCarProgram->SetUniform("matrices.modelViewMatrix", modelViewMatrixStack.Top());
			pCarProgram->SetUniform("matrices.normalMatrix", m_pCamera->ComputeNormalMatrix(modelViewMatrixStack.Top()));
			m_pFBO->BindTexture(0);
			m_pPlane->Render(false);
		modelViewMatrixStack.Pop();
	}
	*/

}

void Game::Render()
{
	// FBO used to create motion blur but motion blur currently not working
	m_pFBO->Bind(true);
	RenderScene(0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	RenderScene(1);

	// Draw the 2D graphics after the 3D graphics
	DisplayFrameRate();

	// Display Points
	DisplayPoints();

	// Display Laps
	DisplayLaps();

	// Display Health
	DisplayHealth();

	// Display End Screen
	DisplayEndScreen();

	// Swap buffers to show the rendered image
	SwapBuffers(m_gameWindow.Hdc());
}

// Update method runs repeatedly with the Render method
void Game::Update() 
{ 
	// Code to work out a TNB frame in order to position and orient the players car
	// Increment distance by time elapsed multiplied by the players speed which can be controlled by key presses
	m_currentDistance = m_currentDistance + (m_dt * m_playerSpeed);
	glm::vec3 p, up;
	m_pCatmullRom->Sample(m_currentDistance, p, up);
	glm::vec3 pNext, upNext;
	m_pCatmullRom->Sample(m_currentDistance + 1, pNext, upNext);
	t = normalize(pNext - p);
	n = normalize(glm::vec3(glm::cross(t, upNext)));
	b = normalize(glm::vec3(glm::cross(n, t)));

	// position the players car and orient it to follow the path
	m_playerPosition = p + (n * (m_playerTurn));
	m_playerOrientation = glm::mat4(glm::mat3(t, b, n));


	// Code to work out the TNB frames for all 4 obstacle cars to set their orientation and position
	// each car is going at a slightly different speed, can be adjusted by the multiplier to m_dt
	// each car is slightly further left or right on the track, can be adjusted by the multiplier to n when setting the cars position
	// CAR 1
	m_car1Distance = m_car1Distance + (m_dt * 0.08f);
	glm::vec3 car1P, car1Up;
	m_pCatmullRom->Sample(m_car1Distance, car1P, car1Up);
	glm::vec3 car1PNext, car1UpNext;
	m_pCatmullRom->Sample(m_car1Distance + 1, car1PNext, car1UpNext);
	glm::vec3 car1T = normalize(car1PNext - car1P);
	glm::vec3 car1N = normalize(glm::vec3(glm::cross(car1T, car1UpNext)));
	glm::vec3 car1B = normalize(glm::vec3(glm::cross(car1N, car1T)));

	m_car1Position = car1P + (n * -16.0f);
	m_car1Orientation = glm::mat4(glm::mat3(car1T, car1B, car1N));

	// CAR 2
	m_car2Distance = m_car2Distance + (m_dt * 0.1f);
	glm::vec3 car2P, car2Up;
	m_pCatmullRom->Sample(m_car2Distance, car2P, car2Up);
	glm::vec3 car2PNext, car2UpNext;
	m_pCatmullRom->Sample(m_car2Distance + 1, car2PNext, car2UpNext);
	glm::vec3 car2T = normalize(car2PNext - car2P);
	glm::vec3 car2N = normalize(glm::vec3(glm::cross(car2T, car2UpNext)));
	glm::vec3 car2B = normalize(glm::vec3(glm::cross(car2N, car2T)));

	m_car2Position = car2P + (n * 9.0f);
	m_car2Orientation = glm::mat4(glm::mat3(car2T, car2B, car2N));

	// CAR 3
	m_car3Distance = m_car3Distance + (m_dt * 0.12f);
	glm::vec3 car3P, car3Up;
	m_pCatmullRom->Sample(m_car3Distance, car3P, car3Up);
	glm::vec3 car3PNext, car3UpNext;
	m_pCatmullRom->Sample(m_car3Distance + 1, car3PNext, car3UpNext);
	glm::vec3 car3T = normalize(car3PNext - car3P);
	glm::vec3 car3N = normalize(glm::vec3(glm::cross(car3T, car3UpNext)));
	glm::vec3 car3B = normalize(glm::vec3(glm::cross(car3N, car3T)));

	m_car3Position = car3P + (n * -5.0f);
	m_car3Orientation = glm::mat4(glm::mat3(car3T, car3B, car3N));

	// CAR 4
	m_car4Distance = m_car4Distance + (m_dt * 0.15f);
	glm::vec3 car4P, car4Up;
	m_pCatmullRom->Sample(m_car4Distance, car4P, car4Up);
	glm::vec3 car4PNext, car4UpNext;
	m_pCatmullRom->Sample(m_car4Distance + 1, car4PNext, car4UpNext);
	glm::vec3 car4T = normalize(car4PNext - car4P);
	glm::vec3 car4N = normalize(glm::vec3(glm::cross(car4T, car4UpNext)));
	glm::vec3 car4B = normalize(glm::vec3(glm::cross(car4N, car4T)));

	m_car4Position = car4P + (n * 12.0f);
	m_car4Orientation = glm::mat4(glm::mat3(car4T, car4B, car4N));
	

	// Booleans to check which camera should be active based on what key is pressed
	// set method = camera position, camera look at, camera up vector
	if (m_thirdCam == true)
	{
		// THIRD-PERSON CAMERA
		m_pCamera->Set(m_playerPosition - (t * 50.0f) + glm::vec3(0, 20, 0), m_playerPosition + (t * 30.0f), b);
	}

	else if (m_firstCam == true)
	{
		// FIRST-PERSON CAMERA
		m_pCamera->Set(m_playerPosition + (t * 15.0f) + glm::vec3(0, 3, 0), m_playerPosition + (t * 50.0f), b);
	}

	else if (m_freeCam == true)
	{
		// FREE CAMERA
		// Update the camera using the amount of time that has elapsed to avoid framerate dependent motion
		m_pCamera->Update(m_dt);
	}

	// COLLISION DETECTION
	// works by checking if the player car is below a thrrshold distance to the obstacle cars
	if (glm::length(m_playerPosition - m_car1Position) < 10)
	{
		m_health = m_health - 30;
		m_playerSpeed = 0;
	}

	if (glm::length(m_playerPosition - m_car2Position) < 10)
	{
		m_health = m_health - 30;
		m_playerSpeed = 0;
	}

	if (glm::length(m_playerPosition - m_car3Position) < 10)
	{
		m_health = m_health - 30;
		m_playerSpeed = 0;
	}

	if (glm::length(m_playerPosition - m_car4Position) < 10)
	{
		m_health = m_health - 30;
		m_playerSpeed = 0;
	}

	// Unrenders the car 
	if (m_health <= 0)
	{
		m_pPlayerCarMesh->~COpenAssetImportMesh();
	}

}


void Game::DisplayFrameRate()
{
	CShaderProgram *fontProgram = (*m_pShaderPrograms)[1];

	RECT dimensions = m_gameWindow.GetDimensions();
	int height = dimensions.bottom - dimensions.top;

	// Increase the elapsed time and frame counter
	m_elapsedTime += m_dt;
	m_frameCount++;

	// Now we want to subtract the current time by the last time that was stored
	// to see if the time elapsed has been over a second, which means we found our FPS.
	if (m_elapsedTime > 1000)
    {
		m_elapsedTime = 0;
		m_framesPerSecond = m_frameCount;

		// incrementing player points every second 
		// only increment if player health is above 0, allows player to see the points they ended on at the end screen
		if (m_health > 0)
		{
			m_points = m_points + 1;
		}
		
		// Reset the frames per second
		m_frameCount = 0;
    }

	if (m_framesPerSecond > 0) {
		// Use the font shader program and render the text
		fontProgram->UseProgram();
		glDisable(GL_DEPTH_TEST);
		fontProgram->SetUniform("matrices.modelViewMatrix", glm::mat4(1));
		fontProgram->SetUniform("matrices.projMatrix", m_pCamera->GetOrthographicProjectionMatrix());
		fontProgram->SetUniform("vColour", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		m_pFtFont->Render(20, height - 20, 20, "FPS: %d", m_framesPerSecond);
	}
}

void Game::DisplayPoints()
{
	CShaderProgram* fontProgram = (*m_pShaderPrograms)[1];

	RECT dimensions = m_gameWindow.GetDimensions();
	int height = dimensions.bottom - dimensions.top;
	int width = dimensions.right - dimensions.left;

	// point multiplier incremented by current lap
	// lap 3 = multiplier 4x
	m_pointMultiplier = 1.0f + (m_pCatmullRom->CurrentLap(m_currentDistance));
	int point = m_points * m_pointMultiplier;
	int pointMultiplier = m_pointMultiplier;

	// Use the font shader program and render the text
	fontProgram->UseProgram();
	glDisable(GL_DEPTH_TEST);
	fontProgram->SetUniform("matrices.modelViewMatrix", glm::mat4(1));
	fontProgram->SetUniform("matrices.projMatrix", m_pCamera->GetOrthographicProjectionMatrix());
	fontProgram->SetUniform("vColour", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	m_pFtFont->Render(width / 2, height - 40, 50, "Points: %d", point);
	m_pFtFont->Render(width / 2, height - 80, 50, "Multiplier: %d", pointMultiplier);
}

void Game::DisplayLaps()
{
	CShaderProgram* fontProgram = (*m_pShaderPrograms)[1];

	RECT dimensions = m_gameWindow.GetDimensions();
	int height = dimensions.bottom - dimensions.top;

	// Use the font shader program and render the text
	fontProgram->UseProgram();
	glDisable(GL_DEPTH_TEST);
	fontProgram->SetUniform("matrices.modelViewMatrix", glm::mat4(1));
	fontProgram->SetUniform("matrices.projMatrix", m_pCamera->GetOrthographicProjectionMatrix());
	fontProgram->SetUniform("vColour", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	m_pFtFont->Render(1375, height - 40, 50, "Laps: %d", m_pCatmullRom->CurrentLap(m_currentDistance));

}

void Game::DisplayHealth()
{
	CShaderProgram* fontProgram = (*m_pShaderPrograms)[1];

	RECT dimensions = m_gameWindow.GetDimensions();
	int height = dimensions.bottom - dimensions.top;
	int width = dimensions.right - dimensions.left;

	// Use the font shader program and render the text
	fontProgram->UseProgram();
	glDisable(GL_DEPTH_TEST);
	fontProgram->SetUniform("matrices.modelViewMatrix", glm::mat4(1));
	fontProgram->SetUniform("matrices.projMatrix", m_pCamera->GetOrthographicProjectionMatrix());
	fontProgram->SetUniform("vColour", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	m_pFtFont->Render(300, height - 40, 50, "Car Health: %d", m_health);
}

void Game::DisplayEndScreen()
{
	// only display end screen when health is at or below 0

	if (m_health <= 0)
	{
		CShaderProgram* fontProgram = (*m_pShaderPrograms)[1];

		RECT dimensions = m_gameWindow.GetDimensions();
		int height = dimensions.bottom - dimensions.top;
		int width = dimensions.right - dimensions.left;

		m_pointMultiplier = 1.0f + (m_pCatmullRom->CurrentLap(m_currentDistance));
		int point = m_points * m_pointMultiplier;

		// Use the font shader program and render the text
		fontProgram->UseProgram();
		glDisable(GL_DEPTH_TEST);
		fontProgram->SetUniform("matrices.modelViewMatrix", glm::mat4(1));
		fontProgram->SetUniform("matrices.projMatrix", m_pCamera->GetOrthographicProjectionMatrix());
		fontProgram->SetUniform("vColour", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		m_pFtFont->Render(width/2 - 250, height/2 , 100, "GAME OVER!");
		m_pFtFont->Render(width / 2 - 250, height / 2 - 200, 100, "Points = %d", point);
	}
	
}

// The game loop runs repeatedly until game over
void Game::GameLoop()
{
	/*
	// Fixed timer
	m_dt = m_pHighResolutionTimer->Elapsed();
	if (m_dt > 1000.0 / (double) Game::FPS) {
		m_pHighResolutionTimer->Start();
		Update();
		Render();
	}
	*/
	
	// Variable timer
	m_pHighResolutionTimer->Start();
	Update();
	Render();
	m_dt = m_pHighResolutionTimer->Elapsed();
	
	
}


WPARAM Game::Execute() 
{
	m_pHighResolutionTimer = new CHighResolutionTimer;
	m_gameWindow.Init(m_hInstance);

	if(!m_gameWindow.Hdc()) {
		return 1;
	}

	Initialise();

	m_pHighResolutionTimer->Start();

	
	MSG msg;

	while(1) {													
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) { 
			if(msg.message == WM_QUIT) {
				break;
			}

			TranslateMessage(&msg);	
			DispatchMessage(&msg);
		} else if (m_appActive) {
			GameLoop();
		} 
		else Sleep(200); // Do not consume processor power if application isn't active
	}

	m_gameWindow.Deinit();

	return(msg.wParam);
}

LRESULT Game::ProcessEvents(HWND window, UINT message, WPARAM w_param, LPARAM l_param)
{
	LRESULT result = 0;

	switch (message) {


	case WM_ACTIVATE:
	{
		switch (LOWORD(w_param))
		{
		case WA_ACTIVE:
		case WA_CLICKACTIVE:
			m_appActive = true;
			m_pHighResolutionTimer->Start();
			break;
		case WA_INACTIVE:
			m_appActive = false;
			break;
		}
		break;
	}

	case WM_SIZE:
		RECT dimensions;
		GetClientRect(window, &dimensions);
		m_gameWindow.SetDimensions(dimensions);
		break;

	case WM_PAINT:
		PAINTSTRUCT ps;
		BeginPaint(window, &ps);
		EndPaint(window, &ps);
		break;

	case WM_KEYDOWN:
		switch (w_param) {
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;

		case '1':
			// FIRST PERSON CAMERA
			m_firstCam = true;
			m_thirdCam = false;
			m_freeCam = false;
			break;
		case '2':
			// THIRD-PERSON CAMERA
			m_firstCam = false;
			m_thirdCam = true;
			m_freeCam = false;
			break;
		case '3':
			// FREE CAMERA
			// Set free camera at a point, looking at a point, with an up vector
			// Camera is set() because if the free camera is called when the other cameras are tilted, it causes the free cam to be tilted
			// this resets that for a better experience using the free cam
			m_pCamera->Set(glm::vec3(0,30,0), glm::vec3(100,30,0), glm::vec3(0,1,0));
			m_firstCam = false;
			m_thirdCam = false;
			m_freeCam = true;
			break;

		// WASD CONTROLS
		// barricade collsions done here with the turns left and right clamped within 30 and -30
		case 'W':
			if (m_playerSpeed < 0.4f)
			{
				// ACCELERATE
				m_playerSpeed = m_playerSpeed + 0.001f;
			}
			break;
		case 'S':
			if (m_playerSpeed > 0.003f)
			{
				// BRAKE / SLOW DOWN
				m_playerSpeed = m_playerSpeed - 0.003f;
			}
			else if (m_playerSpeed < 0.003f)
			{
				// STOP
				m_playerSpeed = 0;
			}
			break;
		case 'A':
			if (m_playerTurn > (-30.0f))
			{
				// TURN LEFT
				m_playerTurn = m_playerTurn - 2.0f;
				m_playerRotation = 15.0f;
			}
			break;
		case 'D':
			if (m_playerTurn < 30.0f)
			{
				// TURN RIGHT
				m_playerTurn = m_playerTurn + 2.0f;
				m_playerRotation = -15.0f;
			}
			break;
		}
		break;

	// Player rotation animation reverted after key released
	case WM_KEYUP:
		switch (w_param)
		{
		case 'A':
			m_playerRotation = 0.0f;
			break;
		case 'D':
			m_playerRotation = 0.0f;
			break;
		}
		break;


	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		result = DefWindowProc(window, message, w_param, l_param);
		break;
	}

	return result;
}

Game& Game::GetInstance() 
{
	static Game instance;

	return instance;
}

void Game::SetHinstance(HINSTANCE hinstance) 
{
	m_hInstance = hinstance;
}

LRESULT CALLBACK WinProc(HWND window, UINT message, WPARAM w_param, LPARAM l_param)
{
	return Game::GetInstance().ProcessEvents(window, message, w_param, l_param);
}

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE, PSTR, int) {
	Game &game = Game::GetInstance();
	game.SetHinstance(hinstance);

	return int(game.Execute());
}
