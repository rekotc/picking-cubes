////////////////////////////////////////////////////////////////////////////////
// Filename: applicationclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "applicationclass.h"


ApplicationClass::ApplicationClass()
{
	m_Input = 0;
	m_D3D = 0;
	m_Camera = 0;

	m_ModelList = 0;

	m_Models[0] = 0;
	m_Models[1] = 0;
	m_Models[2] = 0;
	m_Models[3] = 0;
	m_Models[4] = 0;
	m_Models[5] = 0;
	m_Models[6] = 0;
	m_Models[7] = 0;
	m_Models[8] = 0;

	m_Model = 0;
	m_Model2 = 0;
	m_Arrows = 0;

	m_TextureShader = 0;
	m_LightShader = 0;
	m_Light = 0;
	m_Text = 0;
	m_Bitmap = 0;
	m_ArrowUp = 0;
	//bCube = 0;
	//bCube2 = 0;
	
	selectionState = 0;

	rotation = 0.0f;
}


ApplicationClass::ApplicationClass(const ApplicationClass& other)
{
}


ApplicationClass::~ApplicationClass()
{
}


bool ApplicationClass::Initialize(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight)
{
	bool result;
	D3DXMATRIX baseViewMatrix;
	
	// Store the screen width and height.
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	// Create the input object.
	m_Input = new InputClass;
	if(!m_Input)
	{
		return false;
	}

	// Initialize the input object.
	result = m_Input->Initialize(hinstance, hwnd, screenWidth, screenHeight);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the input object.", L"Error", MB_OK);
		return false;
	}

	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if(!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new CameraClass;
	if(!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	m_Camera->SetPosition(10.0f, 10.0f, -10.0f);
	m_Camera->Render();
	m_Camera->GetViewMatrix(baseViewMatrix);

	// Create the model list object.
	m_ModelList = new ModelListClass;
	if (!m_ModelList)
	{
		return false;
	}

	// Initialize the model list object.
	result = m_ModelList->Initialize(25);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model list object.", L"Error", MB_OK);
		return false;
	}


	for (int id = 0; id < NUM_CUBES; id++){
		// Create the model object.
		m_Models[id] = new ModelClass;
		if (!m_Models[id])
		{
			return false;
		}
		m_Models[id]->setId(id);

		// Initialize the model object.
		result = m_Models[id]->Initialize(m_D3D->GetDevice(), "../data/crate.txt", L"../data/crate.dds");
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
			return false;
		}
		
	}

	m_Models[0]->setPosition(D3DXVECTOR3(10.0f, 10.0f, 10.0f));
	m_Models[1]->setPosition(D3DXVECTOR3(12.0f, 10.0f, 10.0f));
	m_Models[2]->setPosition(D3DXVECTOR3(14.0f, 10.0f, 10.0f));
	m_Models[3]->setPosition(D3DXVECTOR3(10.0f, 12.0f, 10.0f));
	m_Models[4]->setPosition(D3DXVECTOR3(12.0f, 12.0f, 10.0f));
	m_Models[5]->setPosition(D3DXVECTOR3(14.0f, 12.0f, 10.0f));
	m_Models[6]->setPosition(D3DXVECTOR3(10.0f, 14.0f, 10.0f));
	m_Models[7]->setPosition(D3DXVECTOR3(12.0f, 14.0f, 10.0f));
	m_Models[8]->setPosition(D3DXVECTOR3(14.0f, 14.0f, 10.0f));
	

	// Create the model object.
	m_Model = new ModelClass;
	if(!m_Model)
	{
		return false;
	}
	m_Model->setId(0);
	// Initialize the model object.
	result = m_Model->Initialize(m_D3D->GetDevice(), "../data/crate.txt", L"../data/crate.dds");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Create the second model object.
	m_Model2 = new ModelClass;
	if (!m_Model2)
	{
		return false;
	}
	m_Model2->setId(1);

	// Initialize the model object.
	result = m_Model2->Initialize(m_D3D->GetDevice(), "../data/sphere.txt", L"../data/blue.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the second model object.", L"Error", MB_OK);
		return false;
	}

	// Create the Arrows
	m_Arrows = new ModelClass;
	if (!m_Arrows)
	{
		return false;
	}
	//m_Arrows->setId(1);

	// Initialize the model object.
	result = m_Arrows->InitializeFlatRectangle(m_D3D->GetDevice(),10.0f,10.0f, L"../data/up.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the arrows object.", L"Error", MB_OK);
		return false;
	}

	// Create the texture shader object.
	m_TextureShader = new TextureShaderClass;
	if(!m_TextureShader)
	{
		return false;
	}

	// Initialize the texture shader object.
	result = m_TextureShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the light shader object.
	m_LightShader = new LightShaderClass;
	if(!m_LightShader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_LightShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the light object.
	m_Light = new LightClass;
	if(!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetDirection(0.0f, 0.0f, 1.0f);

	// Create the text object.
	m_Text = new TextClass;
	if(!m_Text)
	{
		return false;
	}

	// Initialize the text object.
	result = m_Text->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), hwnd, screenWidth, screenHeight, baseViewMatrix);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the text object.", L"Error", MB_OK);
		return false;
	}

	// Create the bitmap object.
	m_Bitmap = new BitmapClass;
	if(!m_Bitmap)
	{
		return false;
	}

	// Initialize the bitmap object.
	result = m_Bitmap->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, L"../data/mouse.dds", 32, 32);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the bitmap object.", L"Error", MB_OK);
		return false;
	}

	m_ArrowUp = new BitmapClass;
	if (!m_ArrowUp)
	{
		return false;
	}

	// Initialize the bitmap object.
	result = m_ArrowUp->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, L"../data/mouse.dds", 100, 100);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the bitmap object.", L"Error", MB_OK);
		return false;
	}

	// Initialize that the user has not clicked on the screen to try an intersection test yet.
	m_beginCheck = false;

	//bCube = new AabbClass();
	//bCube2 = new AabbClass();
	selectionState = new CollisionClass();

	return true;
}


void ApplicationClass::Shutdown()
{
	// Release the bitmap object.
	if(m_Bitmap)
	{
		m_Bitmap->Shutdown();
		delete m_Bitmap;
		m_Bitmap = 0;
	}

	// Release the text object.
	if(m_Text)
	{
		m_Text->Shutdown();
		delete m_Text;
		m_Text = 0;
	}

	// Release the light object.
	if(m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the light shader object.
	if(m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}

	// Release the texture shader object.
	if(m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}

	// Release the model object.
	if(m_Model)
	{
		m_Model->Shutdown();
		delete m_Model;
		m_Model = 0;
	}

	// Release the model object.
	if (m_Model2)
	{
		m_Model2->Shutdown();
		delete m_Model2;
		m_Model2 = 0;
	}

	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the D3D object.
	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	// Release the input object.
	if(m_Input)
	{
		m_Input->Shutdown();
		delete m_Input;
		m_Input = 0;
	}

	return;
}


bool ApplicationClass::Frame()
{
	bool result;


	//rotation = 0.0f;


	// Update the rotation variable each frame.
	rotation += (float)D3DX_PI * 0.01f;
	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}


	// Handle the input processing.
	result = HandleInput();
	if(!result)
	{
		return false;
	}

	// Render the graphics scene.
	result = Render();
	if(!result)
	{
		return false;
	}

	return true;
}


bool ApplicationClass::HandleInput()
{
	bool result, onClick;
	int mouseX, mouseY;


	// Do the input frame processing.
	result = m_Input->Frame();
	if(!result)
	{
		return false;
	}

	// Check if the user pressed escape and wants to exit the application.
	if(m_Input->IsEscapePressed() == true)
	{
		return false;
	}

	//salvo lo stato del left mouse button
	onClick = m_Input->IsLeftMouseButtonDown();	

	//se ho cliccato
	if (onClick == true){
		//e prima il mouse non era premuto
		if (m_beginCheck == false){
			//inizio a considerarlo premuto
			m_beginCheck = true;
		}
	}
	//altrimenti vuol dire che non ho cliccato, quindi il mouse eventualmente è stato rilasciato, o è rimasto non premuto.
	else{
		m_beginCheck = false;
		
	}


	m_Input->GetMouseLocation(mouseX, mouseY);
	TestIntersection(mouseX, mouseY, onClick);



	/*
	// Check if the left mouse button has been pressed.
	if(m_Input->IsLeftMouseButtonDown() == true)
	{
		// If they have clicked on the screen with the mouse then perform an intersection test.
		if(m_beginCheck == false)
		{
			m_beginCheck = true;
			m_Input->GetMouseLocation(mouseX, mouseY);
			//qui devi restituire l'id del cubo selezionato, altrimenti -1
			TestIntersection(mouseX, mouseY, true);
			//se l'id è diverso da 0, è stato selezionato un cubo, allora imposta a true il disegno delle icone di rotazione.

		}
	}
	else
	{
		m_Input->GetMouseLocation(mouseX, mouseY);
		TestIntersection(mouseX, mouseY, false);
	}
	*/
	// Check if the left mouse button has been released.
/*	if(m_Input->IsLeftMouseButtonDown() == false)
	{
		m_beginCheck = false;
	}*/

	return true;
}


bool ApplicationClass::Render()
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix, translateMatrix, rotateMatrix;
	bool result;
	int renderCount, modelCount, index;
	int mouseX, mouseY;
	D3DXVECTOR4 color;
	float positionX, positionY, positionZ, radius;

	D3DXVECTOR3 position;
	D3DXMATRIX translation, combine;

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);
	
	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	m_D3D->GetOrthoMatrix(orthoMatrix);

	for (index = 0; index < NUM_CUBES; index++)
	{
		// Get the position and color of the sphere model at this index.
		//m_ModelList->GetData(index, positionX, positionY, positionZ, color);

		// Set the radius of the sphere to 1.0 since this is already known.
		//radius = 1.0f;
		position = m_Models[index]->getPosition();

		/*
		//COPIA INCOLLA
		// translate the world matrix 
		D3DXMATRIX MatTemp;  // Temp matrix for rotations.
		D3DXMATRIX MatRot;   // Final rotation matrix, applied to // pMatWorld.

		// Using the left-to-right order of matrix concatenation,
		// apply the translation to the object's world position
		// before applying the rotations.
		//D3DXMatrixTranslation(&worldMatrix, -1.5f, -1.5f, 5.0f);
		
		D3DXMatrixIdentity(&MatRot);
		D3DXMatrixIdentity(&MatTemp);

		// Now, apply the orientation variables to the world matrix
		D3DXMatrixRotationY(&MatTemp, XM_PIDIV2);           // Yaw
		D3DXMatrixMultiply(&MatRot, &MatRot, &MatTemp);
		// Apply the rotation matrices to complete the world matrix.
		D3DXMatrixMultiply(&worldMatrix, &MatRot, &worldMatrix);
		*/
		//FINE COPIA INCOLLA
		
		//D3DXMatrixRotationY(&rotation, XM_PIDIV2);
		//D3DXMatrixTranslation(&translation,position.x, position.y, position.z);
		// Move the model to the location it should be rendered at.
		//D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &rotation);
		
		//D3DXMatrixTranslation(&worldMatrix, position.x, position.y, position.z);
		D3DXMatrixRotationY(&worldMatrix, rotation);
		D3DXMatrixTranslation(&worldMatrix, position.x, position.y, position.z);

		// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
		m_Models[index]->Render(m_D3D->GetDeviceContext());
		// Render the model using the light shader.
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Models[index]->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Models[index]->GetTexture(), m_Light->GetDirection(), m_Models[index]->getColor());

		// Reset to the original world matrix.
		m_D3D->GetWorldMatrix(worldMatrix);

		// Since this model was rendered then increase the count for this frame.
		//renderCount++;

	}



	/*
	// Get the number of models that will be rendered.
	modelCount = m_ModelList->GetModelCount();

	// Initialize the count of models that have been rendered.
	renderCount = 0;

	
	for (index = 0; index < modelCount; index++)
	{
		// Get the position and color of the sphere model at this index.
		m_ModelList->GetData(index, positionX, positionY, positionZ, color);

		// Set the radius of the sphere to 1.0 since this is already known.
		radius = 1.0f;
		
		// Move the model to the location it should be rendered at.
		D3DXMatrixTranslation(&worldMatrix, positionX, positionY, positionZ);

		// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
		m_Model->Render(m_D3D->GetDeviceContext());

		// Render the model using the light shader.
		

		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Model->GetTexture(), m_Light->GetDirection(), color);

		// Reset to the original world matrix.
		m_D3D->GetWorldMatrix(worldMatrix);

		// Since this model was rendered then increase the count for this frame.
		renderCount++;
		
	}
	*/
	/*
	// Translate to the location of the sphere.
	D3DXMatrixTranslation(&translateMatrix, 10.0f, 10.0f, 10.0f);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix); 


	// Render the model using the light shader.
	m_Model->Render(m_D3D->GetDeviceContext());
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Model->GetTexture(), m_Light->GetDirection(),pickedUpColors[0]);
	if(!result)
	{
		return false;
	}
	

	
	// Reset the world matrix.
	m_D3D->GetWorldMatrix(worldMatrix);

	// Translate to the location of the sphere.
	D3DXMatrixTranslation(&translateMatrix,12.0f, 12.0f, 10.0f);
	D3DXMatrixRotationY(&rotateMatrix, XM_PIDIV2);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &rotateMatrix);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
	*/
	/*
	// Render the SECOND model using the light shader.
	m_Model2->Render(m_D3D->GetDeviceContext());
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model2->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Model2->GetTexture(), m_Light->GetDirection(), pickedUpColors[1]);
	if (!result)
	{
		return false;
	}
	*/

	/*
	if (selectionState->getCurrentId() != -2){
		result = m_ArrowUp->Render(m_D3D->GetDeviceContext(), 6.0f, 6.0f);  if (!result) { return false; }
		//result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_ArrowUp->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_ArrowUp->GetTexture());
		m_LightShader->Render(m_D3D->GetDeviceContext(), m_ArrowUp->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_ArrowUp->GetTexture(), m_Light->GetDirection(), pickedUpColors[0]);
	}
	*/

	// Reset the world matrix.
	m_D3D->GetWorldMatrix(worldMatrix);
	int selected = selectionState->getCurrentSelectedId();
	if (selected != -1){
		// Translate to the location of the sphere.

		position = m_Models[selected]->getPosition();
		// Move the model to the location it should be rendered at.
		D3DXMatrixTranslation(&translateMatrix, position.x, position.y+2.0f, position.z);
		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
		// Render the Arrows model using the light shader.
		m_Arrows->Render(m_D3D->GetDeviceContext());
		//result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Arrows->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Arrows->GetTexture(), m_Light->GetDirection(), pickedUpColors[1]);
		m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Arrows->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Arrows->GetTexture());

		if (!result)
		{
			return false;
		}
		
	}
	
	// Reset the world matrix.
	m_D3D->GetWorldMatrix(worldMatrix);

	// Turn off the Z buffer to begin all 2D rendering.
	m_D3D->TurnZBufferOff();

	// Turn on alpha blending.
	m_D3D->EnableAlphaBlending();

	// Get the location of the mouse from the input object,
	m_Input->GetMouseLocation(mouseX, mouseY);
	


	// Render the mouse cursor with the texture shader.
	result = m_Bitmap->Render(m_D3D->GetDeviceContext(), mouseX, mouseY);  if(!result) { return false; }
	result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Bitmap->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, m_Bitmap->GetTexture());

	

	// Render the text strings.
	result = m_Text->Render(m_D3D->GetDeviceContext(), worldMatrix, orthoMatrix);
	if(!result)
	{
		return false;
	}

	// Turn of alpha blending.
	m_D3D->DisableAlphaBlending();

	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_D3D->TurnZBufferOn();

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}


void ApplicationClass::TestIntersection(int mouseX, int mouseY, bool onClick)
{

	float pointX, pointY;
	D3DXMATRIX projectionMatrix, viewMatrix, inverseViewMatrix, worldMatrix, translateMatrix, inverseWorldMatrix;
	D3DXVECTOR3 direction, origin, rayOrigin, rayDirection;
	bool intersect, result;

	bool debug = false;


	D3DXVECTOR4 color;
	float positionX, positionY, positionZ, radius;
	int modelCount, index, lastSelectedId, lastHoverId;

	// Move the mouse cursor coordinates into the -1 to +1 range.
	pointX = ((2.0f * (float)mouseX) / (float)m_screenWidth) - 1.0f;
	pointY = (((2.0f * (float)mouseY) / (float)m_screenHeight) - 1.0f) * -1.0f;
		
	// Adjust the points using the projection matrix to account for the aspect ratio of the viewport.
	m_D3D->GetProjectionMatrix(projectionMatrix);
	pointX = pointX / projectionMatrix._11;
	pointY = pointY / projectionMatrix._22;

	// Get the inverse of the view matrix.
	m_Camera->GetViewMatrix(viewMatrix);
	D3DXMatrixInverse(&inverseViewMatrix, NULL, &viewMatrix);

	// Calculate the direction of the picking ray in view space.
	direction.x = (pointX * inverseViewMatrix._11) + (pointY * inverseViewMatrix._21) + inverseViewMatrix._31;
	direction.y = (pointX * inverseViewMatrix._12) + (pointY * inverseViewMatrix._22) + inverseViewMatrix._32;
	direction.z = (pointX * inverseViewMatrix._13) + (pointY * inverseViewMatrix._23) + inverseViewMatrix._33;

	// Get the origin of the picking ray which is the position of the camera.
	origin = m_Camera->GetPosition();

	lastSelectedId = selectionState->getCurrentSelectedId();
	lastHoverId = selectionState->getCurrentHoverId();
	//resetto SEMPRE il colore dell'ultimo box hover, qualora ve ne sia uno
	if (lastHoverId != -1){
		setColor(lastHoverId, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f));
		selectionState->setCurrentHoverId(-1);
		selectionState->setCurrentMinDistance(999999999);
	}
	//resetto SEMPRE il colore dell'ultimo box selected, qualora ve ne sia uno
	if (lastSelectedId != -1){
		setColor(lastSelectedId, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f));
		selectionState->setCurrentSelectedId(-1);
		selectionState->setCurrentMinDistance(999999999);
	}
	


	/*
	//salvo il currentId come lastId
	selectionState->setLastId(selectionState->getCurrentId());

	//resetto la selectionState
	selectionState->setCurrentId(-1);
	selectionState->setCurrentMinDistance(999999999);
	*/

	// Get the number of models that will be rendered.
	modelCount = m_ModelList->GetModelCount();

	if (mouseX >= 500 && mouseY >= 10){

		debug = true;
	}


	for (index = 0; index < NUM_CUBES; index++)
	{
		// Get the world matrix and translate to the location of the sphere.
		m_D3D->GetWorldMatrix(worldMatrix);

		D3DXVECTOR3 position = m_Models[index]->getPosition();
		// Move the model to the location it should be rendered at.
		D3DXMatrixTranslation(&worldMatrix, position.x, position.y, position.z);
		
		// Now get the inverse of the translated world matrix.
		D3DXMatrixInverse(&inverseWorldMatrix, NULL, &worldMatrix);

		// Now transform the ray origin and the ray direction from view space to world space.
		D3DXVec3TransformCoord(&rayOrigin, &origin, &inverseWorldMatrix);
		D3DXVec3TransformNormal(&rayDirection, &direction, &inverseWorldMatrix);

		// Normalize the ray direction.
		D3DXVec3Normalize(&rayDirection, &rayDirection);
			
		
		// Now perform the ray-sphere intersection test.
		//intersect = RaySphereIntersect(rayOrigin, rayDirection, 1.0f);
		intersect = RayAABBIntersect(debug,selectionState, index, rayOrigin, rayDirection, m_Models[index]->getBoundingBox());

	}

	/*

	// Get the world matrix and translate to the location of the sphere.
	m_D3D->GetWorldMatrix(worldMatrix);

	D3DXMatrixTranslation(&translateMatrix, 10.0f, 10.0f, 10.0f);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix); 

	// Now get the inverse of the translated world matrix.
	D3DXMatrixInverse(&inverseWorldMatrix, NULL, &worldMatrix);

	// Now transform the ray origin and the ray direction from view space to world space.
	D3DXVec3TransformCoord(&rayOrigin, &origin, &inverseWorldMatrix);
	D3DXVec3TransformNormal(&rayDirection, &direction, &inverseWorldMatrix);

	// Normalize the ray direction.
	D3DXVec3Normalize(&rayDirection, &rayDirection);

	//salvo il currentId come lastId
	selectionState->setLastId(selectionState->getCurrentId());

	//resetto la selectionState
	selectionState->setCurrentId(-1);
	selectionState->setCurrentMinDistance(999999999);

	// Now perform the ray-sphere intersection test.
	//intersect = RaySphereIntersect(rayOrigin, rayDirection, 1.0f);
	intersect = RayAABBIntersect(selectionState, m_Model->getId(), rayOrigin, rayDirection, m_Model->getBoundingBox());
	
	// Reset the world matrix.
	m_D3D->GetWorldMatrix(worldMatrix);

	//seconda sfera
	
	// Get the world matrix and translate to the location of the sphere.
	//m_D3D->GetWorldMatrix(worldMatrix);
	D3DXMatrixTranslation(&translateMatrix, 12.0f, 12.0f, 10.0f);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);

	// Now get the inverse of the translated world matrix.
	D3DXMatrixInverse(&inverseWorldMatrix, NULL, &worldMatrix);

	// Now transform the ray origin and the ray direction from view space to world space.
	D3DXVec3TransformCoord(&rayOrigin, &origin, &inverseWorldMatrix);
	D3DXVec3TransformNormal(&rayDirection, &direction, &inverseWorldMatrix);

	// Normalize the ray direction.
	D3DXVec3Normalize(&rayDirection, &rayDirection);

	intersect = RayAABBIntersect(selectionState, m_Model2->getId(), rayOrigin, rayDirection, m_Model2->getBoundingBox());
	*/

	

	//se ho trovato una intersezione 
	if (selectionState->getClosestId() != -1){

		//se avevo cliccato
		if (onClick==true){
			selectionState->setCurrentSelectedId(selectionState->getClosestId());
			m_Text->SetIntersection(true, selectionState->getCurrentSelectedId(), m_D3D->GetDeviceContext());
			result = setSelectionState(selectionState, onClick);	
		//devo anche eventualmente ruotare l'oggetto selezionato, nella direzione di spostamento del mouse.
		//se true vuol dire che sto tenendo premuto il pulsante del mouse, allora procedo a ruotare nella direzione dello spostamento	
			if (m_beginCheck == true){

				int oldX = m_Input->getOldMouseX();
				//se == -1 vuol dire che è il primo click su quell'oggetto, in quel caso non faccio niente.
				if ( oldX != -1){

					D3DXVECTOR3 test = m_Models[selectionState->getCurrentSelectedId()]->getPosition();
					//mi sto spostando verso dx
					if (oldX<mouseX)
						test.x += 0.01f;
					else if (oldX>mouseX)
						test.x -= 0.01f;
					else if (oldX == mouseX)
						test.x = test.x;


					m_Models[selectionState->getCurrentSelectedId()]->setPosition(test);

				}
				//salvo le coordinate correnti per la prossima iterazione
				m_Input->setOldMouseX(mouseX);
				m_Input->setOldMouseY(mouseY);
			}
			//se false vuol dire che ho rilasciato il mouse, o che non l'ho mai premuto, in ogni caso resetto la oldMouseX,Y
			else if (m_beginCheck == false){
				m_Input->setOldMouseX(-1);
				m_Input->setOldMouseY(-1);
			}


		}
		else{
			selectionState->setCurrentHoverId(selectionState->getClosestId());
			m_Text->SetIntersection(true, selectionState->getCurrentHoverId(), m_D3D->GetDeviceContext());
			result = setSelectionState(selectionState, onClick);
		}
	}
	//altrimenti non c'è alcuna intersezione, aggiorno semplicemente l'interfaccia
	else{

		m_Text->SetIntersection(false, selectionState->getCurrentSelectedId(), m_D3D->GetDeviceContext());
	}



	//result = setselectionState(selectionState, onClick);

	return;
}

//DA AGGIORNARE!
bool ApplicationClass::RaySphereIntersect(D3DXVECTOR3 rayOrigin, D3DXVECTOR3 rayDirection, float radius)
{
	float a, b, c, discriminant;


	// Calculate the a, b, and c coefficients.
	a = (rayDirection.x * rayDirection.x) + (rayDirection.y * rayDirection.y) + (rayDirection.z * rayDirection.z);
	b = ((rayDirection.x * rayOrigin.x) + (rayDirection.y * rayOrigin.y) + (rayDirection.z * rayOrigin.z)) * 2.0f;
	c = ((rayOrigin.x * rayOrigin.x) + (rayOrigin.y * rayOrigin.y) + (rayOrigin.z * rayOrigin.z)) - (radius * radius);

	// Find the discriminant.
	discriminant = (b * b) - (4 * a * c);

	// if discriminant is negative the picking ray missed the sphere, otherwise it intersected the sphere.
	if (discriminant < 0.0f)
	{
		return false;
	}

	return true;
}



bool ApplicationClass::RayAABBIntersect(bool debug, CollisionClass* selectionState, int currentid, D3DXVECTOR3 rayOrigin, D3DXVECTOR3 rayDirection, AabbClass* bCube)
{

	

	//rayOrigin = D3DXVECTOR3(10.0f, 10.0f, -5.0f);
	double tmin = -INFINITY, tmax = INFINITY;

	if (rayDirection.x != 0.0) {
		double tx1 = (bCube->min[0] - rayOrigin.x) / rayDirection.x;
		double tx2 = (bCube->max[0] - rayOrigin.x) / rayDirection.x;

		tmin = max(tmin, min(tx1, tx2));
		tmax = min(tmax, max(tx1, tx2));
	}

	if (rayDirection.y != 0.0) {
		double ty1 = (bCube->min[1] - rayOrigin.y) / rayDirection.y;
		double ty2 = (bCube->max[1] - rayOrigin.y) / rayDirection.y;

		tmin = max(tmin, min(ty1, ty2));
		tmax = min(tmax, max(ty1, ty2));
	}

	if (rayDirection.z != 0.0) {
		double tz1 = (bCube->min[2] - rayOrigin.z) / rayDirection.z;
		double tz2 = (bCube->max[2] - rayOrigin.z) / rayDirection.z;

		tmin = max(tmin, min(tz1, tz2));
		tmax = min(tmax, max(tz1, tz2));
	}
	
	if (debug == true){
		int ciao = 23;
	}

	//se c'è l'intersezione, e il nuovo oggetto si trova ad una distanza inferiore rispetto a quello correntemente selezionato
	//aggiorna selectionState con le informazioni sul nuovo oggetto
	if (	(tmax >= tmin) && (selectionState->getCurrentMinDistance()>tmin)	){

		selectionState->setClosestId(currentid);
		selectionState->setCurrentMinDistance(tmin);
		return  true;

	}
	else
	return false;
	
}

bool ApplicationClass::setSelectionState(CollisionClass* selectionState, bool onClick){

	bool result;

	//se ho cliccato sull'oggetto uso il colore selezione
	if (onClick  ){
	
		selectionState->setClicked(true);
		result = setColor(selectionState->getCurrentSelectedId(), D3DXVECTOR4(0.5f, 0.6f, 0.34f, 1.0f));

		
	}
	//altrimenti uso un colore diverso per l'hover
	else 
	{

		selectionState->setClicked(false);
		result = setColor(selectionState->getCurrentHoverId(), D3DXVECTOR4(0.1f, 0.9f, 0.64f, 1.0f));
		return result;

	}


	
}

bool ApplicationClass::setColor(int id, D3DXVECTOR4 color){


	m_Models[id]->setColor(color);

	return true;

}