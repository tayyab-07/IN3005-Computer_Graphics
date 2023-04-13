#pragma once

#include "Common.h"
#include "GameWindow.h"

// Classes used in game.  For a new class, declare it here and provide a pointer to an object of this class below.  Then, in Game.cpp, 
// include the header.  In the Game constructor, set the pointer to NULL and in Game::Initialise, create a new object.  Don't forget to 
// delete the object in the destructor.   
class CCamera;
class CSkybox;
class CShader;
class CShaderProgram;
class CFreeTypeFont;
class CHighResolutionTimer;
class COpenAssetImportMesh;
class CTreeMesh;
class CAudio;
class CCatmullRom;
class CBarricadeSpline;
class CTunnel;
class COverpass;
class CHeightMapTerrain;
class CFrameBufferObject;
class CPlane;

class Game {
private:
	// Three main methods used in the game.  Initialise runs once, while Update and Render run repeatedly in the game loop.
	void Initialise();
	void Update();
	void RenderScene(int pass);
	void Render();

	// Pointers to game objects.  They will get allocated in Game::Initialise()
	CSkybox *m_pSkybox;
	CCamera *m_pCamera;
	vector <CShaderProgram *> *m_pShaderPrograms;
	CFreeTypeFont *m_pFtFont;
	COpenAssetImportMesh *m_pPlayerCarMesh;
	COpenAssetImportMesh *m_pCar1Mesh;
	COpenAssetImportMesh* m_pCar2Mesh;
	COpenAssetImportMesh* m_pCar3Mesh;
	COpenAssetImportMesh* m_pCar4Mesh;
	CTreeMesh *m_pTreeMesh;
	CHighResolutionTimer *m_pHighResolutionTimer;
	CAudio *m_pAudio;
	CCatmullRom *m_pCatmullRom;
	CBarricadeSpline *m_pBarricadeSpline;
	CTunnel *m_pTunnel;
	COverpass *m_pOverpass; 
	CHeightMapTerrain *m_pHeightMapTerrain;
	CFrameBufferObject* m_pFBO;
	CPlane *m_pPlane;

	// Some other member variables
	float m_dt;
	int m_framesPerSecond;
	bool m_appActive;
	float m_currentDistance;

	float m_car1Distance;
	float m_car2Distance;
	float m_car3Distance;
	float m_car4Distance;

	// Camera
	bool m_freeCam;
	bool m_thirdCam;
	bool m_firstCam;

	// Player Car
	glm::vec3 t;
	glm::vec3 n;
	glm::vec3 b;
	glm::vec3 m_playerPosition;
	glm::mat4 m_playerOrientation;
	float m_playerSpeed;
	float m_playerTurn;
	float m_playerRotation;
	float m_points;
	float m_pointMultiplier;
	int m_health;

	// Obstacle cars 
	glm::vec3 m_car1Position;
	glm::mat4 m_car1Orientation;

	glm::vec3 m_car2Position;
	glm::mat4 m_car2Orientation;

	glm::vec3 m_car3Position;
	glm::mat4 m_car3Orientation;

	glm::vec3 m_car4Position;
	glm::mat4 m_car4Orientation;

public:
	Game();
	~Game();
	static Game& GetInstance();
	LRESULT ProcessEvents(HWND window,UINT message, WPARAM w_param, LPARAM l_param);
	void SetHinstance(HINSTANCE hinstance);
	WPARAM Execute();

private:
	static const int FPS = 60;

	// Display HUD items functions
	void DisplayFrameRate();
	void DisplayPoints();
	void DisplayLaps();
	void DisplayHealth();
	void DisplayEndScreen();

	void GameLoop();
	GameWindow m_gameWindow;
	HINSTANCE m_hInstance;
	int m_frameCount;
	double m_elapsedTime;
};
