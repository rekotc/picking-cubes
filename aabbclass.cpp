#include "aabbclass.h"

AabbClass::AabbClass()
{
	/*m_Input = 0;
	m_D3D = 0;
	m_Camera = 0;
	m_Model = 0;
	m_TextureShader = 0;
	m_LightShader = 0;
	m_Light = 0;
	m_Text = 0;
	m_Bitmap = 0;*/

	//xmin
	min[0] = -1.0f;
	min[1] = -1.0f;
	min[2] = -1.0f;
	//xmax
	max[0] = 1.0f;
	max[1] = 1.0f;
	max[2] = 1.0f;

}


AabbClass::AabbClass(const AabbClass& other)
{
}


AabbClass::~AabbClass()
{
}

void AabbClass::BuildBoundingBox(float minX, float minY, float minZ, float maxX, float maxY, float maxZ)
{
	//min x y z
	min[0] = minX;
	min[1] = minY;
	min[2] = minZ;
	//max x y z
	max[0] = maxX;
	max[1] = maxY;
	max[2] = maxZ;


}

void AabbClass :: updatePosition(D3DXVECTOR3 offset){

	min[0] += offset.x;
	min[1] += offset.y;
	min[2] += offset.z;

	max[0] += offset.x;
	max[1] += offset.y;
	max[2] += offset.z;

}