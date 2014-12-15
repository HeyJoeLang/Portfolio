#pragma once
#include <time.h>
#include <windows.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9tex.h>
#include <dinput.h>
#include <iostream>
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dinput8.lib")
#include <stdlib.h>
#include <stdio.h>
#pragma comment(lib, "winmm.lib")
#include "fmod.hpp"
#pragma comment(lib, "fmodex_vc.lib")
#include <dshow.h>
#pragma comment(lib, "strmiids.lib")
using namespace std;

#define SCREEN_WIDTH  1300
#define SCREEN_HEIGHT 900
#define DIRECTINPUT_VERSION 0x0800

//game state

const int GAME = 1;
const int MENU = 2;
const int CREDITS = 3;
const int QUIT = 4;

int GAMESTATE = GAME;

#define SAFE_RELEASE(x) if(x){x->Release(); x = 0;}
/*DirectX class */
class DirectX
{
private:
	bool				m_bVsync;		// Boolean for vertical syncing
	HWND				m_hwnd;			// Handle to the window
	double				m_currTime;		// Time to render current frame
	double				m_prevTime;		// Time to render previous frame
	D3DCAPS9			m_D3DCaps;		// Device Capabilitie		

	IDirect3D9*			pd3dObject;	// Direct3D 9 Object
	IDirect3DDevice9*	pd3dDevice;	// Direct3D 9 Device

	/* Variables used for finding Frames Per Second */
	int frameCount;
	double deltaTime;
	int	m_FPS;			// Frames per second
	char framesPerSecond[255];
	char pongScore[255];

	long lastMouseX;
	long lastMouseY;

	LPDIRECT3DVERTEXBUFFER9 vertexBuffer;

	ID3DXSprite* m_Sprite; // Should be declared global
	IDirect3DTexture9* m_texture, * m_textureBall, * m_backgroundTexture;
	D3DXIMAGE_INFO m_imageInfo, m_imageInfoBall, m_backgroundImageInfo;

	ID3DXFont* m_Font; // Should be declared global

	D3DXMATRIX matView;					// the view matrix
	D3DXMATRIX matProj;					// the projection matrix
	D3DXMATRIX transMat, rotMat, scaleMat, worldMat;


	/* Input Devices */
	IDirectInput8* m_DIObject;
	IDirectInputDevice8* m_DIKeyboard;	
	IDirectInputDevice8* m_DIMouse;	
	bool m_bKeyDown[256];// Check if key was down last frame

	DIMOUSESTATE2 mouseState;

	
	RECT rct, Frames, backgroundRect;
	void identityMatrix();

	RECT winLose;
	

	/* Sprite Characteristics */
	struct Characteristics
	{
		float posX,posY,posZ;
		float rotation;
		float scaling;
		D3DXCOLOR color;
	};
	Characteristics paddle[2], ball, background;

	float ballDirX, ballDirY, ballScale;
	bool ballInPaddle;
	int P1Score,P2Score;
	int waitTime;
	bool stillPlaying;
	
	char buffer[256];

	//menu
	RECT m_rectMenu, m_rectGame, m_rectOptions, m_rectQuit, m_rectCredits;
	int menuChoice;

	//Credits
	RECT m_rectCreditsDisplay;
	char string_credits[655];
	
	IDirect3DTexture9* m_menuTexture;
	D3DXIMAGE_INFO m_menuImageInfo;

	/* FMOD */
#define ERRCHECK(x) if(x != FMOD_OK) {MessageBox(m_hwnd, (LPCSTR)x, "Fmod Error", MB_OK);}

	FMOD::System*	 	system;
	FMOD_RESULT      	result;
	unsigned int     	version;
	int              	numdrivers;
	FMOD_SPEAKERMODE 	speakermode;
	FMOD_CAPS        	caps;
	char             	name[256];
	bool				m_bVideoPlaying;
	bool startBackGround;


	FMOD::Sound*		sound[6];
	FMOD::Channel*		channel[6];

	/* Direct Show */
	IGraphBuilder*		m_pGraphBuilder; // GraphBuilder
	IMediaControl*		m_pMediaControl; // MediaControl
	IMediaEvent*		m_pMediaEvent;	 // MediaEvent
	IVideoWindow*		m_pVideoWindow;	 // VideoWindow


	void MatrixTransform(float scaleX, float scaleY, float scaleZ, float radianRotation, float translateX, float translateY, float translateZ );

public:
	DirectX(void);

	bool Init(HWND& hwnd, HINSTANCE& hInst, bool bWindowed) ;
	bool Update(bool playerQuit) ;
	void Render() ;
	void Shutdown(void);

	void gameInput();
	void FPS();
	void DisplayNameAndFPS();
	void DisplayGame();
	void InitDirXComponents(HWND& hwnd, HINSTANCE& hInst, bool bWindowed);
	void InitInputDevice(HWND& hwnd, HINSTANCE& hInst);
	void InitFont();
	void InitImages();
	void InitSound();
	void DisplayMenu();
	bool menuInput(bool playerQuit);
	void DisplayCredits();
	void creditsInput();

};
DirectX::DirectX(void)
{
	// Init or NULL objects before use to avoid any undefined behavior
	m_bVsync = false;
	pd3dObject = 0;
	pd3dDevice = 0;
	vertexBuffer = 0;
	m_currTime = 0;
	m_prevTime = 0;
	frameCount = 0;
	ballDirX = 0;
	ballDirY = 0;
	ballScale = 32;
	ballInPaddle = false;
	P1Score = 0;
	P2Score = 0;
	stillPlaying = true;
	m_bVideoPlaying	= true;
	startBackGround = true;
	
	background.posX = 0;
	background.posY = 0;
	background.posZ = 0;
	background.color = D3DCOLOR_ARGB(155,155,155,155);
	
	backgroundRect.top = 0;
	backgroundRect.bottom = SCREEN_HEIGHT;
	backgroundRect.left = 0;
	backgroundRect.right = SCREEN_WIDTH;

	m_rectMenu.top = 0;
	m_rectMenu.bottom = m_rectMenu.top + 30;
	m_rectMenu.left = SCREEN_WIDTH * .30;
	m_rectMenu.right = SCREEN_WIDTH * .70;

	m_rectGame.top = SCREEN_HEIGHT * .25;
	m_rectGame.bottom = m_rectGame.top + 30;
	m_rectGame.left = SCREEN_WIDTH * .30;
	m_rectGame.right = SCREEN_WIDTH * .70;
	
	m_rectCredits.top = m_rectGame.bottom + (SCREEN_HEIGHT * .10);
	m_rectCredits.bottom = m_rectCredits.top + 30;
	m_rectCredits.left = SCREEN_WIDTH * .30;
	m_rectCredits.right = SCREEN_WIDTH * .70;
	
	m_rectQuit.top = m_rectCredits.bottom + (SCREEN_HEIGHT * .10);
	m_rectQuit.bottom = m_rectQuit.top + 30;
	m_rectQuit.left = SCREEN_WIDTH * .30;
	m_rectQuit.right = SCREEN_WIDTH * .70;

	m_rectCreditsDisplay.top = 0;
	m_rectCreditsDisplay.bottom = SCREEN_HEIGHT;
	m_rectCreditsDisplay.left = 0;
	m_rectCreditsDisplay.right = SCREEN_WIDTH;

	
	sprintf_s(string_credits,
		"CREDITS \n\n"
		"Trick Shot Video:\n\n\tDirector: \tChris Van Houten\n"
		"\tCast: Johnny Leombruno, Mat Kelley\n\n"
		"Game:\n\n"
		"Game Diretor: \tJoseph Lang\n"
		"Senior Producer:\t Joseph Lang\n"
		"Associate Producer:\t Joseph Lang\n"
		"Lead Programmer:\t Joseph Lang\n"
		"Art Director:\t Joseph Lang\n"
		"Design Diretor:\t Joseph Lang\n"
		"Project Manager:\t Joseph Lang\n"
		"Lead AI Direct:\t Joseph Lang\n"
		"Production Support:\t Joseph Lang\n"
		"Build Engineer:\t Joseph Lang\n"
		"Level Designer:\t Joseph Lang\n"
		"Sound and Music:\t Joseph Lang\n"
		"Collision:\t Joseph Lang\n"
		"Lead Cinematic Animator:\t Joseph Lang\n"
		"Lead Game Tester:\t Joseph Lang\n"
		"Story:\t Joseph Lang\n"
		"Peon:\t Joseph Lang\n\n");
		menuChoice = 1;
	
}
bool DirectX::Init(HWND& hwnd,  HINSTANCE& hInst, bool bWindowed)
{ 
	InitDirXComponents(hwnd, hInst, bWindowed);
	InitInputDevice(hwnd, hInst);
	InitFont();
	InitImages();
	InitSound();
	

	return true;
}
bool DirectX::Update(bool playerQuit)
{
	playerQuit = false;
	m_DIKeyboard->Acquire();
	m_DIMouse->Acquire();
	m_DIKeyboard->GetDeviceState( sizeof(buffer), (LPVOID)&buffer );
	m_DIMouse->GetDeviceState(sizeof(DIMOUSESTATE2), &mouseState);


	if(m_bVideoPlaying)
	{
		//////////////////////////////////////////////////////////////////////////
		// Stop video and continue with application, if Enter pressed [DIK_RETURN]
		//////////////////////////////////////////////////////////////////////////
		if(buffer[DIK_RETURN] & 0x80)
		{
			// Act on exit key here. (Continue with next game state, etc)
			m_pMediaControl->Stop();
			m_bVideoPlaying = false;

			m_pVideoWindow->put_Visible(OAFALSE);
			m_pVideoWindow->put_Owner((OAHWND)m_hwnd);

			// Clean up DirectShow variables now that it is completed.
			SAFE_RELEASE(m_pMediaControl);
			SAFE_RELEASE(m_pVideoWindow);
			SAFE_RELEASE(m_pGraphBuilder);
		}

		//////////////////////////////////////////////////////////////////////////
		// If video has finished playing, continue with application.
		//////////////////////////////////////////////////////////////////////////
		long evCode, param1, param2;

		if(SUCCEEDED(m_pMediaEvent->GetEvent(&evCode, &param1, &param2, 0)))
		{
			m_pMediaEvent->FreeEventParams(evCode, param1, param2);

			// If video is complete (EC_COMPLETE)
			if(evCode == EC_COMPLETE)
			{
				// Act on complete call here. (Continue with next game state, etc)
				m_pMediaControl->Stop();
				m_bVideoPlaying = false;

				m_pVideoWindow->put_Visible(OAFALSE);
				m_pVideoWindow->put_Owner((OAHWND)m_hwnd);

				// Clean up DirectShow variables now that it is completed.
				SAFE_RELEASE(m_pMediaControl);
				SAFE_RELEASE(m_pVideoWindow);
				SAFE_RELEASE(m_pGraphBuilder);

			}
		}
	}
	else if(!playerQuit)
	{
		switch(GAMESTATE)
		{
		case GAME:
			gameInput();
			FPS();
			break;
		case MENU:
			if(menuInput(&playerQuit) == true)
				return true;
			break;
		case CREDITS:
			creditsInput();
			break;
		}
	}
	return false;
}
void DirectX::Render()
{
	if(! m_bVideoPlaying)
	{
		if(!pd3dDevice)
			return;

		// Present the backbuffer contents to the display
		pd3dDevice->Clear(0, 0, D3DCLEAR_TARGET, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f), 1.0f, 0);


		pd3dDevice->BeginScene();

		m_Sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_DEPTH_FRONTTOBACK);

		switch(GAMESTATE)
		{
		case GAME:
			DisplayGame();
			DisplayNameAndFPS();
			break;
		case MENU:
			DisplayMenu();
			break;
		case CREDITS:
			DisplayCredits();
			break;
		case QUIT:
			break;
		}

		m_Sprite->End();
		pd3dDevice->EndScene();
		pd3dDevice->Present( NULL, NULL, NULL, NULL );

	}
}
/* Cleans all the pointers opened and used during the program */
void DirectX::Shutdown(void)
{
    if( pd3dDevice != NULL) 
	{
        pd3dDevice->Release();
		pd3dDevice = NULL;
	}
    if( pd3dObject != NULL)
	{
        pd3dObject->Release();
		pd3dObject = NULL;
	}
	if(m_Sprite != NULL)
	{
		m_Sprite->Release();
		m_Sprite = NULL;
	}

}
void DirectX::InitDirXComponents(HWND& hwnd, HINSTANCE& hInst, bool bWindowed)
{
	//Set up DirectX
	m_hwnd = hwnd;

	srand ((int)time(NULL));
	D3DXMATRIX meshMat, meshScale, meshRotate, meshTranslate;
    
	pd3dObject = Direct3DCreate9(D3D_SDK_VERSION);
	
	D3DPRESENT_PARAMETERS D3Dpp; 
    ZeroMemory( &D3Dpp, sizeof(D3Dpp) );

	/* Components that make sure Direct X is able to be ran properly, based off system requirements */
	D3Dpp.hDeviceWindow					= hwnd;										// Handle to the focus window
	D3Dpp.Windowed						= bWindowed;								// Windowed or Full-screen boolean
	D3Dpp.AutoDepthStencilFormat		= D3DFMT_D24S8;								// Format of depth/stencil buffer, 24 bit depth, 8 bit stencil
	D3Dpp.EnableAutoDepthStencil		= TRUE;										// Enables Z-Buffer (Depth Buffer)
	D3Dpp.BackBufferCount				= 1;										// Change if need of > 1 is required at a later date
	D3Dpp.BackBufferFormat				= D3DFMT_X8R8G8B8;							// Back-buffer format, 8 bits for each pixel
	D3Dpp.BackBufferHeight				= SCREEN_HEIGHT;									// Make sure resolution is supported, use adapter modes
	D3Dpp.BackBufferWidth				= SCREEN_WIDTH;									// (Same as above)
	D3Dpp.SwapEffect					= D3DSWAPEFFECT_DISCARD;					// Discard back-buffer, must stay discard to support multi-sample
	D3Dpp.PresentationInterval			= m_bVsync ? D3DPRESENT_INTERVAL_DEFAULT : D3DPRESENT_INTERVAL_IMMEDIATE; // Present back-buffer immediately, unless V-Sync is on								
	D3Dpp.Flags							= D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;		// This flag should improve performance, if not set to NULL.
	D3Dpp.FullScreen_RefreshRateInHz	= bWindowed ? 0 : D3DPRESENT_RATE_DEFAULT;	// Full-screen refresh rate, use adapter modes or default
	D3Dpp.MultiSampleQuality			= 0;										// MSAA currently off, check documentation for support.
	D3Dpp.MultiSampleType				= D3DMULTISAMPLE_NONE;						// MSAA currently off, check documentation for support.


	// Check device capabilities
	DWORD deviceBehaviorFlags = 0;
	pd3dObject->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &m_D3DCaps);

	// Determine vertex processing mode
	if(m_D3DCaps.DevCaps & D3DCREATE_HARDWARE_VERTEXPROCESSING)
		// Hardware vertex processing supported? (Video Card)
		deviceBehaviorFlags |= D3DCREATE_HARDWARE_VERTEXPROCESSING;	
	else
		// If not, use software (CPU)
		deviceBehaviorFlags |= D3DCREATE_SOFTWARE_VERTEXPROCESSING; 
	
	// If hardware vertex processing is on, check pure device support
	if(m_D3DCaps.DevCaps & D3DDEVCAPS_PUREDEVICE && deviceBehaviorFlags & D3DCREATE_HARDWARE_VERTEXPROCESSING)
		deviceBehaviorFlags |= D3DCREATE_PUREDEVICE;
	
	D3Dpp.BackBufferWidth = SCREEN_WIDTH;									

	// Create the D3D Device with the present parameters and device flags above
	pd3dObject->CreateDevice(
		D3DADAPTER_DEFAULT,		// which adapter to use, set to primary
		D3DDEVTYPE_HAL,			// device type to use, set to hardware rasterization
		hwnd,					// handle to the focus window
		deviceBehaviorFlags,
		&D3Dpp,					// presentation parameters
		&pd3dDevice);			// returned device pointer
}
void DirectX::InitInputDevice(HWND& hwnd, HINSTANCE& hInst)
{
	//Create Input Device
	DirectInput8Create(hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_DIObject, NULL);

	m_DIObject->CreateDevice(
		GUID_SysKeyboard, 
		&m_DIKeyboard,
		NULL
		); 

	//Set up direct inpute object
	m_DIObject->CreateDevice(GUID_SysMouse, &m_DIMouse, NULL);
	
	// Initialize Keyboard and mouse
	m_DIObject->CreateDevice(GUID_SysKeyboard, &m_DIKeyboard, NULL);
	m_DIObject->CreateDevice(GUID_SysMouse, &m_DIMouse, NULL);

	// Set up Keyboard
	m_DIKeyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	m_DIKeyboard->SetDataFormat(&c_dfDIKeyboard);

	// Set up Mouse (c_dfDIMouse2 = 8 button mouse)
	m_DIMouse->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	m_DIMouse->SetDataFormat(&c_dfDIMouse2);

}
void DirectX::InitFont()
{
//Create Font
	D3DXCreateFont(pd3dDevice, 30, 0, FW_BOLD, 0, false, 
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, TEXT("Times New Roman"), 
		&m_Font);
	
//rect
	//Sets rectangle for text
	rct.left=SCREEN_WIDTH * .5 - 10;
	rct.right= rct.left + 50;
	rct.top=10;
	rct.bottom=rct.top+20;

	Frames.left=200;
	Frames.right=Frames.left+100;
	Frames.top=100;
	Frames.bottom=Frames.top+20;
}
void DirectX::InitImages()
{
//Create Sprite/Texture
	D3DXCreateSprite(pd3dDevice, &m_Sprite);

	D3DXCreateTextureFromFileEx(pd3dDevice, "paddle.png", 0, 0,0, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, 
		D3DX_DEFAULT, 
		D3DCOLOR_XRGB(255, 0, 255),
		&m_imageInfo,
		0, &m_texture
		);

	D3DXCreateTextureFromFileEx(pd3dDevice, "partyNight.jpg", SCREEN_WIDTH, SCREEN_HEIGHT,0, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, 
		D3DX_DEFAULT, 
		D3DCOLOR_XRGB(255, 0, 255),
		&m_backgroundImageInfo,
		0, &m_backgroundTexture
		);

	D3DXCreateTextureFromFileEx(pd3dDevice, "pongBall.png", 0, 0, 0, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, 
		D3DX_DEFAULT, 
		D3DCOLOR_XRGB(255, 0, 255),
		&m_imageInfoBall,
		0, &m_textureBall
		);
	
	//Ball
	int ballInitDir = (rand() % 4)+1;
	switch(ballInitDir)
	{
		case 1:
			ballDirX = -.3;
			ballDirY = .5;
			break;
		case 2:
			ballDirX = -.3;
			ballDirY = -.5;
			break;
		case 3:
			ballDirX = .3;
			ballDirY = -.5;
			break;
		case 4:
			ballDirX = .3;
			ballDirY = .5;
			break;
	}

//Set up Characteristics
	paddle[0].color = D3DXCOLOR((float)(rand()%255),(float)(rand()%255),(float)(rand()%255),(float)(rand()%255));
	paddle[0].scaling = .75;
	paddle[0].rotation = 0;
	paddle[0].posX =  SCREEN_WIDTH - 100;
	paddle[0].posY = SCREEN_HEIGHT / 2;
	paddle[0].posZ = 0;
	
	paddle[1].color = D3DXCOLOR((float)(rand()%255),(float)(rand()%255),(float)(rand()%255),(float)(rand()%255));
	paddle[1].scaling = .75;
	paddle[1].rotation = 0;
	paddle[1].posX = 100;
	paddle[1].posY = SCREEN_HEIGHT / 2;
	paddle[1].posZ = 0;
	
	ball.color = D3DXCOLOR((float)(rand()%255),(float)(rand()%255),(float)(rand()%255),(float)(rand()%255));
	ball.rotation = 0;
	ball.posX =  SCREEN_WIDTH /2;
	ball.posY = SCREEN_HEIGHT / 2;
	ball.posZ = 0;


	D3DXCreateTextureFromFileEx(pd3dDevice, "menuImage.png", 0, 0, 0, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, 
		D3DX_DEFAULT, 
		D3DCOLOR_XRGB(255, 0, 255),
		&m_menuImageInfo,
		0, &m_menuTexture
		);
}
void DirectX::InitSound()
{
//FMOD
	result = FMOD::System_Create(&system);
	ERRCHECK(result);

	result = system->getVersion(&version);
	ERRCHECK(result);
	if (version < FMOD_VERSION)
	{
		printf("Error!  You are using an old version of FMOD %08x.  This program requires %08x\n", version, FMOD_VERSION);
		//return 0;
	}

	result = system->getNumDrivers(&numdrivers);
	ERRCHECK(result);

	if (numdrivers == 0)
	{
		result = system->setOutput(FMOD_OUTPUTTYPE_NOSOUND);
		ERRCHECK(result);
	}
	else
	{
		result = system->getDriverCaps(0, &caps, 0, &speakermode);
		ERRCHECK(result);

		result = system->setSpeakerMode(speakermode);       /* Set the user selected speaker mode. */
		ERRCHECK(result);

		if (caps & FMOD_CAPS_HARDWARE_EMULATED)             /* The user has the 'Acceleration' slider set to off!  This is really bad for latency!. */
		{                                                   /* You might want to warn the user about this. */
			result = system->setDSPBufferSize(1024, 10);
			ERRCHECK(result);
		}

		result = system->getDriverInfo(0, name, 256, 0);
		ERRCHECK(result);

		if (strstr(name, "SigmaTel"))   /* Sigmatel sound devices crackle for some reason if the format is PCM 16bit.  PCM floating point output seems to solve it. */
		{
			result = system->setSoftwareFormat(48000, FMOD_SOUND_FORMAT_PCMFLOAT, 0,0, FMOD_DSP_RESAMPLER_LINEAR);
			ERRCHECK(result);
		}
	}

	// This initialization uses 100 'virtual voices'
	result = system->init(100, FMOD_INIT_NORMAL, 0);
	if (result == FMOD_ERR_OUTPUT_CREATEBUFFER)         /* Ok, the speaker mode selected isn't supported by this soundcard.  Switch it back to stereo... */
	{
		result = system->setSpeakerMode(FMOD_SPEAKERMODE_STEREO);
		ERRCHECK(result);

		result = system->init(100, FMOD_INIT_NORMAL, 0);/* ... and re-init. */
		ERRCHECK(result);
	}

	//ball bounce
	result = system->createSound("Place.wav", FMOD_DEFAULT, 0, &sound[0]);
	ERRCHECK(result);

	//player win
	result = system->createSound("Win.wav", FMOD_DEFAULT, 0, &sound[1]);
	ERRCHECK(result);
	
	//player lose
	result = system->createSound("Lose.wav", FMOD_DEFAULT, 0, &sound[2]);
	ERRCHECK(result);
	// Stream - Background music (looping)
	// Start background music, once intro video has finished playing or is interrupted
	result = system->createStream("party.mp3", FMOD_LOOP_NORMAL | FMOD_2D | FMOD_HARDWARE, 0, &sound[3]);
	ERRCHECK(result);

	//////////////////////////////////////////////////////////////////////////
	// Initialize DirectShow
	//////////////////////////////////////////////////////////////////////////

	// Initialize COM
	CoInitialize(NULL);

	// Create out filter graph
	CoCreateInstance( CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void**)&m_pGraphBuilder);

	// Media Control
	m_pGraphBuilder->QueryInterface( 	IID_IMediaControl, 	(void**)&m_pMediaControl);

	// Media Event
	m_pGraphBuilder->QueryInterface( 	IID_IMediaEvent, (void**)&m_pMediaEvent);
	// Stream intro video file
	m_pGraphBuilder->RenderFile(L"trick.wmv", NULL);

	// Video Window
	m_pMediaControl->QueryInterface( IID_IVideoWindow, (void**)&m_pVideoWindow);

	// Setup the window
	m_pVideoWindow->put_Owner((OAHWND)m_hwnd);

	// Set the style
	m_pVideoWindow->put_WindowStyle(WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE);

	// Obtain the size of the window
	RECT WinRect;
	GetClientRect(m_hwnd, &WinRect);

	// Set the video size to the size of the window
	m_pVideoWindow->SetWindowPosition(WinRect.left,WinRect.top,WinRect.right - WinRect.left, WinRect.bottom - WinRect.top);


	// Run (Play) the graph at the end of initialization
	m_pMediaControl->Run();
}
/* modulized version of identity matrx calls. Abstracted from the rest of the code for simplicity */
void DirectX::identityMatrix()
{
	D3DXMatrixIdentity(&transMat);
	D3DXMatrixIdentity(&scaleMat);
	D3DXMatrixIdentity(&rotMat);
	D3DXMatrixIdentity(&worldMat);
}
/* Modulated tranformation funtion - simply send in the argumants you want to change and it does the matrix calls for you.
Reduces and simplifies code*/
void DirectX::MatrixTransform(float scaleX, float scaleY, float scaleZ, float radianRotation, float translateX, float translateY, float translateZ )
{
	D3DXMatrixScaling(&scaleMat, scaleX, scaleY, scaleZ);					// Scaling
	D3DXMatrixRotationZ(&rotMat, radianRotation);							// Adjust speed of rotation by scaling the time value by an amount
	D3DXMatrixTranslation(&transMat,translateX, translateY, translateZ);	// Translation
	D3DXMatrixMultiply(&scaleMat, &scaleMat, &rotMat);						// Multiply scale and rotation, store in scale
	D3DXMatrixMultiply(&worldMat, &scaleMat, &transMat);					// Multiply scale and translation, store in world
}
void DirectX::gameInput()
{
	// buffer - Stores our keyboard device state
	/* Direct Input */
	//keyboard input
	for(int i = 0; i < 2; ++i)
	{
		if(paddle[i].posY < 110) paddle[i].posY = 110;
		if(paddle[i].posY >  SCREEN_HEIGHT - 80) paddle[i].posY = SCREEN_HEIGHT - 80;
	}
	if(buffer[DIK_W] & 0x80)
	{
		paddle[0].posY -= 1;
	}
	if(buffer[DIK_S] & 0x80)
	{
		paddle[0].posY += 1;
	}
	if(buffer[DIK_ESCAPE] & 0x80)
	{
		GAMESTATE = MENU;
	}
	if(buffer[DIK_A] & 0x80)
	{
	}

}
void DirectX::FPS()
{
	// Calculate Frames per Second
	m_currTime = timeGetTime();
	static int frameCount = 0;
	deltaTime = m_currTime - m_prevTime;
	if(deltaTime >= 1000)
	{
		m_prevTime = m_currTime;
		m_FPS = frameCount;
		frameCount = 0;		
	}

	++frameCount;
}
void DirectX::DisplayNameAndFPS()
{
	
	/* Display name and FPS */

	sprintf_s(pongScore,"%d          %d",P2Score,P1Score);
	m_Font->DrawText(0,pongScore ,
		-1,
		&rct, 
		DT_TOP | DT_RIGHT | DT_NOCLIP,
		D3DCOLOR_ARGB(255,255, 255,255)
		);
	sprintf_s(framesPerSecond,"Frames Per Second : %d",m_FPS);
	m_Font->DrawText(0,framesPerSecond,
		-1,
		&Frames, 
		DT_TOP | DT_RIGHT | DT_NOCLIP,
		D3DCOLOR_ARGB(255,0,255,0)
		);
}
void DirectX::DisplayGame()
{
	identityMatrix();


	if(startBackGround == true)
	{
		result = system->playSound(FMOD_CHANNEL_FREE, sound[3], false, &channel[3]);
		ERRCHECK(result);
		startBackGround = false;
	}
	for(int i = 0; i < 2; ++i)
	{
		MatrixTransform(paddle[i].scaling, paddle[i].scaling, 0.0f, D3DXToRadian(paddle[i].rotation), paddle[i].posX, paddle[i].posY, 0.0f);

		// Set Transform
		m_Sprite->SetTransform(&worldMat);

		// Draw the texture with the sprite object
		m_Sprite->Draw(m_texture, 0, &D3DXVECTOR3(m_imageInfo.Width, m_imageInfo.Height, 0.0f),
			0, paddle[i].color
			);
	}

	// Place the ball in the center of the screen
	MatrixTransform(paddle[2].scaling, paddle[2].scaling,0.0f, paddle[2].rotation, paddle[2].posX, paddle[2].posY, 0.0f);

	// Set Transform
	m_Sprite->SetTransform(&worldMat);
	
	//Computer Paddle
	if(ball.posY > paddle[1].posY) paddle[1].posY += 1;
	if(ball.posY < paddle[1].posY) paddle[1].posY -= 1;

	//Ball
	if(waitTime > 0)
	{
		ballScale = 32;

		int ballInitDir = (rand() % 4)+1;
		switch(ballInitDir)
		{
		case 1:
			ballDirX = - (rand() %4 + 2) * .1;
			ballDirY = (rand() %7 + 2) * .1;
			break;
		case 2:
			ballDirX = -(rand() %4 + 2 ) * .1;
			ballDirY = -(rand() %7 + 2) * .1;
			break;
		case 3:
			ballDirX = (rand() %4 + 2) * .1;
			ballDirY = -(rand() %7 + 2) * .1;
			break;
		case 4:
			ballDirX = (rand() %4 + 2) * .1;
			ballDirY = (rand() %7 + 2) * .1;
			break;
		}
		if(P2Score > 10)
		{
			result = system->playSound(FMOD_CHANNEL_FREE, sound[1], false, &channel[1]);
			P1Score = 0;
			P2Score = 0;
		}
		if(P1Score > 10)
		{
			result = system->playSound(FMOD_CHANNEL_FREE, sound[2], false, &channel[2]);
			P1Score = 0;
			P2Score = 0;
		}
		// Calculate Frames per Second
		if(deltaTime >= 1000)
		{
			--waitTime;
		}
	}
	else
	{
		ball.scaling = ballScale;
		ball.posX += ballDirX;
		ball.posY += ballDirY;
	}
	if(ball.posX > SCREEN_WIDTH)
	{
		ERRCHECK(result);
		ball.posX = SCREEN_WIDTH * .5;
		ball.posY = SCREEN_HEIGHT * .5;
		waitTime = 3;
		P2Score++;
	}
	if(ball.posX < 0)
	{
		ERRCHECK(result);
		ball.posX = SCREEN_WIDTH * .5;
		ball.posY = SCREEN_HEIGHT * .5;
		waitTime = 3;
		P1Score++;
		if(P1Score >=10)
		{
			stillPlaying = false;
		}
	}
	if(ball.posY < 0)
	{
		ballDirY *= -1;
		if(ballScale > 10)
			ballScale-=3;
	}

	if(ball.posY + m_imageInfoBall.Height > SCREEN_HEIGHT)
	{
		result = system->playSound(FMOD_CHANNEL_FREE, sound[0], false, &channel[0]);
		ERRCHECK(result);
		ballDirY *= -1;
		if(ballScale > 10)
			ballScale-=3;
	}
	if(ball.posX > 200 && ball.posX < SCREEN_WIDTH - 200)
		ballInPaddle = false;
	if(
		ball.posX >= paddle[0].posX - 70 && 
		ball.posX <= paddle[0].posX + 10 && 
		ball.posY <= paddle[0].posY + 80 &&
		ball.posY >= paddle[0].posY - 110 &&
		!ballInPaddle
		)
	{
		result = system->playSound(FMOD_CHANNEL_FREE, sound[0], false, &channel[0]);
		ERRCHECK(result);
		if(abs(ballDirY) < 2)
			ballDirY *= rand()% 2 + 1;
		if(abs(ballDirX) < 1.25)
			ballDirX *= -1.2;
		else
			ballDirX *= -1;
		ballInPaddle = true;
	}
	else if(
		ball.posX <= paddle[1].posX + 10 && 
		ball.posX >= paddle[1].posX - 40 && 
		ball.posY <= paddle[1].posY + 80 &&
		ball.posY >= paddle[1].posY - 110 &&
		!ballInPaddle
		)
	{
		result = system->playSound(FMOD_CHANNEL_FREE, sound[0], false, &channel[0]);
		ERRCHECK(result);
		if(abs(ballDirY) < 2)
			ballDirY *= rand()% 2 + 1;
		if(abs(ballDirX) < 1.25)
			ballDirX *= -1.2;
		else
			ballDirX *= -1;
		ballInPaddle = true;
	}
	

	// Draw the texture with the sprite object
	m_Sprite->Draw( m_textureBall, 0, &D3DXVECTOR3(0, 0, 0.0f),
		0, ball.color);
}
void DirectX::DisplayMenu()
{
	m_Font->DrawText(0,"MENU",
		-1,
		&m_rectMenu, 
		DT_CENTER,
		D3DCOLOR_ARGB(255,0,255,0)
		);
	m_Font->DrawText(0,"[G]AME",
		-1,
		&m_rectGame, 
		DT_CENTER,
		D3DCOLOR_ARGB(255,0,255,0)
		);
	m_Font->DrawText(0,"[C]REDITS",
		-1,
		&m_rectCredits, 
		DT_CENTER,
		D3DCOLOR_ARGB(255,0,255,0)
		);
	m_Font->DrawText(0,"[Q]UIT",
		-1,
		&m_rectQuit, 
		DT_CENTER,
		D3DCOLOR_ARGB(255,0,255,0)
		);
	switch(menuChoice)
	{
	case 1:
		m_Font->DrawText(0,"-->",
			-1,
			&m_rectGame, 
			DT_LEFT,
			D3DCOLOR_ARGB(255,0,255,0)
			);
		break;
	case 2:
		m_Font->DrawText(0,"-->",
			-1,
			&m_rectCredits, 
			DT_LEFT,
			D3DCOLOR_ARGB(255,0,255,0)
			);
		break;
	case 3:
		m_Font->DrawText(0,"-->",
			-1,
			&m_rectQuit, 
			DT_LEFT,
			D3DCOLOR_ARGB(255,0,255,0)
			);
		break;
	}
}
bool DirectX::menuInput(bool playerQuit)
{

	if(buffer[DIK_G] & 0x80)
	{
		if(!m_bKeyDown[DIK_G])
		{
			m_bKeyDown[DIK_G] = true;
			GAMESTATE = GAME;
		}
	}		
	else
	{
		if(m_bKeyDown[DIK_G])
		{
			m_bKeyDown[DIK_G] = false;
		}
	}

	if(buffer[DIK_C] & 0x80)
	{
		if(!m_bKeyDown[DIK_C])
		{
			m_bKeyDown[DIK_C] = true;
			GAMESTATE = CREDITS;
		}
	}		
	else
	{
		if(m_bKeyDown[DIK_C])
		{
			m_bKeyDown[DIK_C] = false;
		}
	}
	if(buffer[DIK_Q] & 0x80)
	{
		if(!m_bKeyDown[DIK_Q])
		{
			m_bKeyDown[DIK_Q] = true;
			return true;
		}
	}		
	else
	{
		if(m_bKeyDown[DIK_Q])
		{
			m_bKeyDown[DIK_Q] = false;
		}
	}
	if(buffer[DIK_W] & 0x80)
	{
		if(!m_bKeyDown[DIK_W])
		{
			m_bKeyDown[DIK_W] = true;
			--menuChoice;
		}
	}		
	else
	{
		if(m_bKeyDown[DIK_W])
		{
			m_bKeyDown[DIK_W] = false;
		}
	}

	if(buffer[DIK_S] & 0x80)
	{
		if(!m_bKeyDown[DIK_S])
		{
			m_bKeyDown[DIK_S] = true;
			++menuChoice;
		}
	}
	else
	{
		if(m_bKeyDown[DIK_S])
		{
			m_bKeyDown[DIK_S] = false;
		}
	}

	if(menuChoice > 3)
		menuChoice = 1;
	if(menuChoice < 1)
		menuChoice = 3;
	
	if(buffer[DIK_RETURN] & 0x80)
	{
		if(!m_bKeyDown[DIK_RETURN])
		{
			m_bKeyDown[DIK_RETURN] = true;
		switch(menuChoice)
		{
		case 1:
			GAMESTATE = GAME;
			break;
		case 2:
			GAMESTATE = CREDITS;
			break;
		case 3:
			playerQuit = true;
			return playerQuit;
			break;
		}
		}
	}		
	else
	{
		if(m_bKeyDown[DIK_RETURN])
		{
			m_bKeyDown[DIK_RETURN] = false;
		}
	}
	return false;
}
void DirectX::creditsInput()
{
	if(buffer[DIK_RETURN] & 0x80)
	{
		if(!m_bKeyDown[DIK_RETURN])
		{
			m_bKeyDown[DIK_RETURN] = true;
			GAMESTATE = MENU;
		}
	}		
	else
	{
		if(m_bKeyDown[DIK_RETURN])
		{
			m_bKeyDown[DIK_RETURN] = false;
		}
	}
}
void DirectX::DisplayCredits()
{
	m_Font->DrawText(0,string_credits,
		-1,
		&m_rectCreditsDisplay, 
		DT_CENTER,
		D3DCOLOR_ARGB(255,0,255,0)
		);
}
