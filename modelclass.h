////////////////////////////////////////////////////////////////////////////////
// Filename: modelclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _MODELCLASS_H_
#define _MODELCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <d3dx10math.h>
//#include <directxmath.h>
#include <fstream>
#include "aabbclass.h"
using namespace std;
//using namespace DirectX;

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "textureclass.h"



////////////////////////////////////////////////////////////////////////////////
// Class name: ModelClass
////////////////////////////////////////////////////////////////////////////////
class ModelClass
{
private:
	struct VertexType
	{
		D3DXVECTOR3 position;
	    D3DXVECTOR2 texture;
		D3DXVECTOR3 normal;
	};

	struct ModelType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
	};

public:
	ModelClass();
	ModelClass(const ModelClass&);
	~ModelClass();

	bool Initialize(ID3D11Device*, char*, WCHAR*);
	bool InitializeFlatRectangle(ID3D11Device*, float width, float height, WCHAR*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);
	
	void setPosition(D3DXVECTOR3);
	void updatePosition(D3DXVECTOR3);
	D3DXVECTOR3 getPosition();

	int GetIndexCount();
	ID3D11ShaderResourceView* GetTexture();
	AabbClass* getBoundingBox();
	void updateBoundingBoxPos(D3DXVECTOR3);

	void setId(int);
	int getId();

	void setColor(D3DXVECTOR4);
	D3DXVECTOR4 getColor();

	D3DXVECTOR3 getInstantRotation();
	D3DXVECTOR3 getFixedRotation();

	void setInstantRotation(D3DXVECTOR3);
	void setInstantRotationX(float);
	void setInstantRotationY(float);
	void setInstantRotationZ(float);

	void setFixedRotation(D3DXVECTOR3);
	void setFixedRotationX(float);
	void setFixedRotationY(float);
	void setFixedRotationZ(float);

	D3DXMATRIX* getRotationMatrix();
	void setRotationMatrix(D3DXMATRIX);

private:
	bool InitializeBuffers(ID3D11Device*);
	bool InitializeBuffersFlatRectangle(ID3D11Device*);

	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

	bool LoadTexture(ID3D11Device*, WCHAR*);
	void ReleaseTexture();

	bool LoadModel(char*);
	void ReleaseModel();

	

private:
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;
	TextureClass* m_Texture;
	ModelType* m_model;
	AabbClass* m_boundingBox;
	int m_id;

	D3DXMATRIX m_rotationMatrix;
	D3DXMATRIX rotX, rotY, rotZ;
	D3DXVECTOR3 instantRotation;
	D3DXVECTOR3 fixedRotation;
	D3DXVECTOR3 position;
	D3DXVECTOR4 pickedUpColor;
};

#endif