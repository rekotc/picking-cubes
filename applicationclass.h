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
#include <D3dx9math.h>

using namespace DirectX;

/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
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
	bool Render(float);
	void TestIntersection();
	bool RaySphereIntersect(D3DXVECTOR3, D3DXVECTOR3, float);
	bool RayAABBIntersect(bool, CollisionClass*, int, D3DXVECTOR3, D3DXVECTOR3, AabbClass*);
	
	bool setColor(int, D3DXVECTOR4);
	bool handleIntersection();
	bool resetSelection(int);
	bool moveObject();

	bool completeRotation(int,char);
	float calculateDelta(float, float);

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
	TextClass* m_Text2;
	TextClass* m_Text3;
	BitmapClass* m_Bitmap;

	BitmapClass* m_ArrowUp;
	bool m_LeftButtonIsBeingKeptPressed;
	bool m_isDraggingWithLeftMouseButton;
	bool m_cubeIsBeingRotated;

	
	D3DXVECTOR3 instantRotation,fixedRotation;
	D3DXMATRIX rotationMatrix;
	D3DXMATRIX rotX, rotY, rotZ;

	float m_cubeCurrentRotationAroundY;
	float m_cubeCurrentRotationAroundX;
	
	float m_cubeLastRotationAroundX;
	float m_cubeLastRotationAroundY;

	bool m_isUpsideDown;
	int m_upsideDownMultiplier;
	float m_oldRotationX;

	bool m_cubeDraggedOnYAxisClockwise;
	bool m_cubeDraggedOnXAxisClockwise;

	bool m_rotationIsAroundX;
	bool m_rotationIsAroundY;
	bool m_rotationLock;

	char m_axis;

	bool m_YaxisIsPosZ;
	bool m_YaxisIsNegZ;
	bool m_YaxisIsPosY;
	bool m_YaxisIsNegY;

	bool m_leftButtonIsClicked;
	bool m_leftButtonWasClicked;
	bool m_leftButtonIsBeingDragged;
	int m_mouseX, m_mouseY;

	D3DXQUATERNION m_qRotation;

	int m_screenWidth, m_screenHeight;

	//AabbClass* bCube;
	//AabbClass* bCube2;
	D3DXVECTOR4 pickedUpColor;
	D3DXVECTOR4 pickedUpColor2;
	D3DXVECTOR4 pickedUpColors[2];

	CollisionClass* selectionState;


};

#endif