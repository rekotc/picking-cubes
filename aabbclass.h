////////////////////////////////////////////////////////////////////////////////
// Filename: aabbclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _AABBCLASS_H_
#define _AABBCLASS_H

#include <d3dx10math.h>

class AabbClass
{
private:
	/*struct FontType
	{
		float left, right;
		int size;
	};

	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
	};*/



public:
	float min[3];
	float max[3];

	AabbClass();
	AabbClass(const AabbClass&);
	~AabbClass();

	void Shutdown();

	//void BuildVertexArray(void*, char*, float, float);
	void BuildBoundingBox(float,float,float,float,float,float);
	void updatePosition(D3DXVECTOR3);
	

private:

	
	

	bool LoadFontData(char*);
	void ReleaseFontData();
	
	void ReleaseTexture();
	
};

#endif