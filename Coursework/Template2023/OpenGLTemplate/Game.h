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
class CPlane;
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

class Game {
private:
	// Three main methods used in the game.  Initialise runs once, while Update and Render run repeatedly in the game loop.
	void Initialise();
	void Update();
	void Render();

	// Pointers to game objects.  They will get allocated in Game::Initialise()
	CSkybox *m_pSkybox;
	CCamera *m_pCamera;
	vector <CShaderProgram *> *m_pShaderPrograms;
	CFreeTypeFont *m_pFtFont;
	COpenAssetImportMesh *m_pPlayerCarMesh;
	CTreeMesh *m_pTreeMesh;
	CHighResolutionTimer *m_pHighResolutionTimer;
	CAudio *m_pAudio;
	CCatmullRom *m_pCatmullRom;
	CBarricadeSpline *m_pBarricadeSpline;
	CTunnel *m_pTunnel;
	COverpass *m_pOverpass; 
	CHeightMapTerrain *m_pHeightMapTerrain;

	// Some other member variables
	float m_dt;
	int m_framesPerSecond;
	bool m_appActive;
	float m_currentDistance;

	float m_playerSpeed;
	float m_playerTurn;
	float m_playerRotation;

	bool freeCam;
	bool thirdCam;
	bool firstCam;

	glm::vec3 m_playerPosition;
	glm::mat4 m_playerOrientation;

public:
	Game();
	~Game();
	static Game& GetInstance();
	LRESULT ProcessEvents(HWND window,UINT message, WPARAM w_param, LPARAM l_param);
	void SetHinstance(HINSTANCE hinstance);
	WPARAM Execute();

private:
	static const int FPS = 60;
	void DisplayFrameRate();
	void GameLoop();
	GameWindow m_gameWindow;
	HINSTANCE m_hInstance;
	int m_frameCount;
	double m_elapsedTime;


};
