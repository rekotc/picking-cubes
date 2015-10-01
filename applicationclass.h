////////////////////////////////////////////////////////////////////////////////
// Filename: applicationclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _APPLICATIONCLASS_H_
#define _APPLICATIONCLASS_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "inputclass.h"
#include "d3dclass.h"
#include "cameraclass.h"
#include "modelclass.h"
#include "textureshaderclass.h"
#include "lightshaderclass.h"
#include "lightclass.h"
#include "textclass.h"
#include "bitmapclass.h"
//#include "aabbclass.h"
#include "collisionclass.h"
#include "modellistclass.h"
#include <math.h>
#include <DirectXMath.h>

using namespace DirectX;

/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = true;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

const int NUM_CUBES = 9;

////////////////////////////////////////////////////////////////////////////////
// Class name: ApplicationClass
////////////////////////////////////////////////////////////////////////////////
class ApplicationClass
{
public:
	ApplicationClass();
	ApplicationClass(const ApplicationClass&);
	~ApplicationClass();

	bool Initialize(HINSTANCE, HWND, int, int);
	void Shutdown();
	bool Frame();

private:
	bool HandleInput();
	bool Render();
	void TestIntersection(int, int, bool);
	bool RaySphereIntersect(D3DXVECTOR3, D3DXVECTOR3, float);
	bool RayAABBIntersect(bool, CollisionClass*, int, D3DXVECTOR3, D3DXVECTOR3, AabbClass*);
	bool setSelectionState(CollisionClass*, bool);
	bool setColor(int, D3DXVECTOR4);

private:
	InputClass* m_Input;
	D3DClass* m_D3D;
	CameraClass* m_Camera;

	// Create the model list object.
	ModelListClass* m_ModelList;


	ModelClass* m_Models[NUM_CUBES];

	ModelClass* m_Model;
	ModelClass* m_Model2;

	ModelClass* m_Arrows;

	TextureShaderClass* m_TextureShader;
	LightShaderClass* m_LightShader;
	LightClass* m_Light;
	TextClass* m_Text;
	BitmapClass* m_Bitmap;

	BitmapClass* m_ArrowUp;
	bool m_beginCheck;
	int m_screenWidth, m_screenHeight;

	//AabbClass* bCube;
	//AabbClass* bCube2;
	D3DXVECTOR4 pickedUpColor;
	D3DXVECTOR4 pickedUpColor2;
	D3DXVECTOR4 pickedUpColors[2];

	CollisionClass* selectionState;

	float rotation;
};

#endif