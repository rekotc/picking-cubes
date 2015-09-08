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