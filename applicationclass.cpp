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
	m_Text2 = 0;
	m_Bitmap = 0;
	m_ArrowUp = 0;
	//bCube = 0;
	//bCube2 = 0;
	
	m_isDraggingWithLeftMouseButton = false;

	selectionState = 0;

	m_leftButtonIsClicked = false;
	m_leftButtonWasClicked = false;
	m_leftButtonIsBeingDragged = false;

	m_cubeCurrentRotationAroundY = 0.0f;
	m_cubeCurrentRotationAroundX = 0.0f;




	m_cubeIsBeingRotated = false;
	m_cubeDraggedOnYAxisClockwise = false;
	m_cubeDraggedOnXAxisClockwise = false;

	m_isUpsideDown = false;
	m_oldRotationX = 0.0f;

	m_YaxisIsPosZ = false;
	m_YaxisIsNegZ = false;
	m_YaxisIsPosY = true;
	m_YaxisIsNegY = false;

	//m_mouseX, m_mouseY;

	
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
		result = m_Models[id]->Initialize(m_D3D->GetDevice(), "../data/dice.txt", L"../data/dice.dds");
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
	
	/*
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
	*/
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
	result = m_Text->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), hwnd, screenWidth, screenHeight, baseViewMatrix, 20,20);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the text object.", L"Error", MB_OK);
		return false;
	}

	// Create the text object 2.
	m_Text2 = new TextClass;
	if (!m_Text2)
	{
		return false;
	}

	// Initialize the text object.
	result = m_Text2->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), hwnd, screenWidth, screenHeight, baseViewMatrix, 20, 40);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the text 2 object.", L"Error", MB_OK);
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
	m_LeftButtonIsBeingKeptPressed = false;

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


	static float rotation = 0.0f;


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
	result = Render(rotation);
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
	m_leftButtonIsClicked = m_Input->IsLeftMouseButtonDown();

	//se ho cliccato
	if (m_leftButtonIsClicked == true){
		//e prima il mouse era premuto
		if (m_leftButtonWasClicked == true){
			//significa che sto trascinando un oggetto
			m_leftButtonIsBeingDragged = true;
		}
		else{
			m_leftButtonWasClicked = true;
		}
		
	}
	//altrimenti vuol dire che non ho cliccato, quindi il mouse eventualmente � stato rilasciato, o � rimasto non premuto.
	else if (m_leftButtonIsClicked == false) {
		m_leftButtonWasClicked = false;
		m_leftButtonIsBeingDragged = false;

		//devo completare la rotazione del cubo se questo flag � settato
		if (m_cubeIsBeingRotated==true){

			result = completeRotation();
		}

		
	}

	m_Input->GetMouseLocation(m_mouseX, m_mouseY);

	//se non ho cliccato o se non stavo trascinando devo comunque aggiornare l'interfaccia
	//se invece il pulsante del mouse fosse cliccato e stessi trascinando, non dovrei aggiornare nulla.

	if (m_leftButtonIsClicked == false || m_leftButtonIsBeingDragged == false){

		//resetto la selezione corrente
		resetSelection(selectionState->getClosestId());
		m_Text->SetIntersection(false, selectionState->getClosestId(), m_D3D->GetDeviceContext());
		//resetto le coordinate del mouse necessarie per calcolare lo spostamento dell'oggetto selezionato.
		m_Input->setOldMouseX(-1);
		m_Input->setOldMouseY(-1);
		//Eseguo il test per l'intersezione
		TestIntersection();
		//se ho trovato una qualche intersezione
		if (selectionState->getClosestId() != -1){
			result = handleIntersection();
		}
		

	}
	//altrimenti vuol dire che sto trascinando l'oggetto, devo spostarlo di conseguenza.
	else if (m_leftButtonIsClicked == true && m_leftButtonIsBeingDragged == true && selectionState->getClosestId()!=-1) {
	
		moveObject();
	}



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
			//se l'id � diverso da 0, � stato selezionato un cubo, allora imposta a true il disegno delle icone di rotazione.

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


bool ApplicationClass::Render(float rotationB)
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix, translateMatrix, rotateMatrix;
	bool result;
	int renderCount, modelCount, index;
	int mouseX, mouseY;
	D3DXVECTOR4 color;
	float positionX, positionY, positionZ, radius;

	D3DXVECTOR3 position,rotation;
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
		rotation = m_Models[index]->getRotation();
		D3DXMATRIX MatRotY,MatRotX;
		D3DXMATRIX MatTran;
		D3DXMATRIX MatTransf;


		/*if (index == 0){
			//D3DXMatrixRotationY(&MatRot, XM_PIDIV4);
			D3DXMatrixRotationY(&MatRot, rotation);
			D3DXMatrixTranslation(&MatTran, position.x, position.y, position.z);
			D3DXMatrixMultiply(&MatTransf, &MatRot, &MatTran);
			D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &MatTransf);
		}
		else{
			D3DXMatrixTranslation(&worldMatrix, position.x, position.y, position.z);
		}*/

		D3DXMatrixRotationY(&MatRotY, rotation.y);
		D3DXMatrixRotationX(&MatRotX, rotation.x);
		D3DXMatrixTranslation(&MatTran, position.x, position.y, position.z);

		D3DXMatrixMultiply(&MatTransf, &MatRotY, &MatRotX);
		D3DXMatrixMultiply(&MatTransf, &MatTransf, &MatTran);

		D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &MatTransf);

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

	int selected = selectionState->getClosestId();
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

	// Render the text 2 strings.
	result = m_Text2->Render(m_D3D->GetDeviceContext(), worldMatrix, orthoMatrix);
	if (!result)
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


void ApplicationClass::TestIntersection()
{

	float pointX, pointY;
	D3DXMATRIX projectionMatrix, viewMatrix, inverseViewMatrix, worldMatrix, translateMatrix, inverseWorldMatrix;
	D3DXVECTOR3 direction, origin, rayOrigin, rayDirection;
	bool intersect, result;

	bool debug = false;
	int lastHoverId, lastSelectedId;

	D3DXVECTOR4 color;
	float positionX, positionY, positionZ, radius;
	int modelCount, index;

	// Move the mouse cursor coordinates into the -1 to +1 range.
	pointX = ((2.0f * (float)m_mouseX) / (float)m_screenWidth) - 1.0f;
	pointY = (((2.0f * (float)m_mouseY) / (float)m_screenHeight) - 1.0f) * -1.0f;
		
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

	
	
	// Get the number of models that will be rendered.
	modelCount = m_ModelList->GetModelCount();

	/*if (mouseX >= 500 && mouseY >= 10){

		debug = true;
	}*/

	

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

	// Now perform the ray-sphere intersection test.
	//intersect = RaySphereIntersect(rayOrigin, rayDirection, 1.0f);
	intersect = RayAABBIntersect(selectionState, m_Model->getId(), rayOrigin, rayDirection, m_Model->getBoundingBox());
	
	// Reset the world matrix.
	m_D3D->GetWorldMatrix(worldMatrix);

	
	*/

	




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

	//se c'� l'intersezione, e il nuovo oggetto si trova ad una distanza inferiore rispetto a quello correntemente selezionato
	//aggiorna selectionState con le informazioni sul nuovo oggetto
	if (	(tmax >= tmin) && (selectionState->getCurrentMinDistance()>tmin)	){

		selectionState->setClosestId(currentid);
		selectionState->setCurrentMinDistance(tmin);
		return  true;

	}
	else
	return false;
	
}


bool ApplicationClass::setColor(int id, D3DXVECTOR4 color){


	m_Models[id]->setColor(color);

	return true;

}

bool ApplicationClass::handleIntersection(){

	bool result;
	int id = selectionState->getClosestId();

	//se l'intersezione non � vuota
	if ( id != -1){

		//se ho cliccato, aggiorno l'oggetto selezionato con il colore clicked.
		if (m_leftButtonIsClicked == true){
			m_Text->SetIntersection(true, selectionState->getClosestId(), m_D3D->GetDeviceContext());
			result = setColor(id, D3DXVECTOR4(0.5f, 0.6f, 0.34f, 1.0f));
		}
		//se non ho cliccato, aggiorno l'oggetto selezionato con il colore hover.
		else if (m_leftButtonIsClicked == false){
			m_Text->SetIntersection(true, selectionState->getClosestId(), m_D3D->GetDeviceContext());
			result = setColor(id, D3DXVECTOR4(0.1f, 0.9f, 0.64f, 1.0f));
		}


	}

	return true;
}

bool ApplicationClass::resetSelection(int closestId){

	//resetto l'ultimo oggetto selezionato, se esiste, cio� se !=-1
	if (closestId != -1){
		setColor(closestId, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f));
		selectionState->setClosestId(-1);
		selectionState->setCurrentMinDistance(999999999);
	}

	return true;
}


bool ApplicationClass::moveObject(){

	int oldX = m_Input->getOldMouseX();
	int oldY = m_Input->getOldMouseY();
	m_cubeIsBeingRotated = true;
		//D3DXVECTOR3 offset = m_Models[selectionState->getCurrentSelectedId()]->getPosition();
	D3DXVECTOR3 offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 rotation = m_Models[selectionState->getClosestId()]->getRotation();

	int distanceY,distanceX;	

	distanceY = m_mouseY - oldY;
	distanceX = m_mouseX - oldX;

	
	//ROTAZIONE ASSE X
		if (oldY != -1){
			
			//se distance � negativo significa che mi sto spostando verso alto
			if (distanceY < 0){
				//offset.x = 0.01f;
				rotation.x += (float)XM_PI*0.03*(-distanceY)*0.2;
				//rotation.y -= (float)XM_PI*0.03*distance*0.2;
				m_cubeCurrentRotationAroundX += (float)XM_PI*0.03*(-distanceY)*0.2;

				if (rotation.x > XM_2PI)
				{
					rotation.x = 0.0f;
					m_cubeCurrentRotationAroundX = 0.0f;
				}


			}
			//mi sto spostando verso basso
			else if (distanceY > 0){
				//offset.x = -0.01f;

				rotation.x -= (float)XM_PI*0.03*distanceY*0.2;
				m_cubeCurrentRotationAroundX -= (float)XM_PI*0.03*distanceY*0.2;


				if (rotation.x < -XM_2PI)
				{
					rotation.x = 0.0f;
					m_cubeCurrentRotationAroundX = 0.0f;
				}

				//verifico se ho capovolto l'oggetto mentre lo ruotavo verso il basso, le successive rotazioni su Y
				//devono allora avvenire su Y negativo

			/*	if (rotation.x <= -XM_PI){

					m_YaxisIsNegY == true;
					m_YaxisIsPosY == false;
				
				}*/

				/*else if (rotation.x <= -XM_PI){

					m_YaxisIsNegY == false;
					m_YaxisIsPosY == true;
				}
				*/


			}
		}
	
	
			//se == -1 vuol dire che � il primo click su quell'oggetto, in quel caso non faccio niente.
			if (oldX != -1){


	//FINE ROTAZIONE ASSE X


				//ROTAZIONE ASSE Y
				//mi sto spostando verso dx 
				if (distanceX > 0){
					//offset.x = 0.01f;

					if (m_isUpsideDown==false){
						rotation.y -= (float)XM_PI*0.03*distanceX*0.2;
						m_cubeCurrentRotationAroundY -= (float)XM_PI*0.03*distanceX*0.2;

						if (rotation.y < -XM_2PI)
						{
							rotation.y = 0.0f;
							m_cubeCurrentRotationAroundY = 0.0f;
						}
					}
					else if (m_isUpsideDown == true){
						rotation.y += (float)XM_PI*0.03*distanceX*0.2;
						m_cubeCurrentRotationAroundY += (float)XM_PI*0.03*distanceX*0.2;

						if (rotation.y > XM_2PI)
						{
							rotation.y = 0.0f;
							m_cubeCurrentRotationAroundY = 0.0f;
						}
					}



				}
				//mi sto spostando verso sx
				else if (distanceX < 0){

					if (m_isUpsideDown == false){
						//offset.x = -0.01f;
						rotation.y += (float)XM_PI*0.03*(-distanceX)*0.2;
						m_cubeCurrentRotationAroundY += (float)XM_PI*0.03*(-distanceX)*0.2;

						if (rotation.y > XM_2PI)
						{
							rotation.y = 0.0f;
							m_cubeCurrentRotationAroundY = 0.0f;
						}
					}
					else if (m_isUpsideDown == true){

						rotation.y -= (float)XM_PI*0.03*(-distanceX)*0.2;
						m_cubeCurrentRotationAroundY -= (float)XM_PI*0.03*(-distanceX)*0.2;

						if (rotation.y < -XM_2PI)
						{
							rotation.y = 0.0f;
							m_cubeCurrentRotationAroundY = 0.0f;
						}
					}
					


				}
			}

			if (m_cubeCurrentRotationAroundY >= 0.0f)	//maggiore di zero significa rotazione in senso orario su Y
				m_cubeDraggedOnYAxisClockwise = true;
			else m_cubeDraggedOnYAxisClockwise = false;

			if (m_cubeCurrentRotationAroundX >= 0.0f)	//maggiore di zero significa rotazione in senso orario su X
				m_cubeDraggedOnXAxisClockwise = true;
			else m_cubeDraggedOnXAxisClockwise = false;

		
	//SAVE STATE

	m_Text2->SetDistance(m_cubeCurrentRotationAroundY, m_cubeCurrentRotationAroundX, m_D3D->GetDeviceContext());

	//aggiorno sempre la posizione
	m_Models[selectionState->getClosestId()]->updatePosition(offset);
	m_Models[selectionState->getClosestId()]->setRotation(rotation);
	//m_Models[selectionState->getClosestId()]->updateBoundingBoxPos(offset);
	//salvo le coordinate correnti per la prossima iterazione
	m_Input->setOldMouseX(m_mouseX);
	m_Input->setOldMouseY(m_mouseY);

	return true;
}

bool ApplicationClass :: completeRotation(){

	D3DXVECTOR3 rotation = m_Models[selectionState->getClosestId()]->getRotation();


	float angles[5] = { 0.0f, XM_PIDIV2, XM_PI, 1.5f*XM_PI, XM_2PI };
	//valore arbitrario, pi� grande dei valori ottenibili con calculateDelta();
	float delta = 4*XM_PI;
	float temp;
	float chosenAngle = 0.0f;

	//ROTAZIONE ASSE Y

	for (int i = 0; i < 5; i++){

		temp = calculateDelta(m_cubeCurrentRotationAroundY, angles[i]);

		if (temp < delta){
			delta = temp;
			chosenAngle = angles[i];
		}

	}

	if (m_cubeDraggedOnYAxisClockwise == false) {
		chosenAngle = -chosenAngle;
		//m_cubeCurrentRotation = -m_cubeCurrentRotation;
	}

	rotation.y += (chosenAngle - m_cubeCurrentRotationAroundY);

	//ROTAZIONE ASSE X

	delta = 4 * XM_PI;
	chosenAngle = 0.0f;

	for (int i = 0; i < 5; i++){

		temp = calculateDelta(m_cubeCurrentRotationAroundX, angles[i]);

		if (temp < delta){
			delta = temp;
			chosenAngle = angles[i];
		}

	}

	if (m_cubeDraggedOnXAxisClockwise == false) {
		chosenAngle = -chosenAngle;
		//m_cubeCurrentRotation = -m_cubeCurrentRotation;
	}

	rotation.x += (chosenAngle - m_cubeCurrentRotationAroundX);
	

	//se ho capovolto l'oggetto, la rotazione su Y deve avvenire su Y negativo
/*	if (m_YaxisIsNegY == true){


	}*/

	//devo verificare su quali assi il cubo si trova in questo momento.

	//se l'angolo di rotazione su X � cambiato rispetto all'iterazione precedente, controllo l'orientamento dell'asse Y
	if (rotation.x != m_oldRotationX){
		//se ho ruotato il cubo in modo da aver invertito l'asse di rotazione Y (cio� se ho ruotato il cubo sottosopra)
		if (rotation.x == -XM_PI || rotation.x == XM_PI || rotation.x == 0.0f || rotation.x == XM_2PI){

			if (m_isUpsideDown == false)m_isUpsideDown = true;
			else m_isUpsideDown = false;

			m_YaxisIsNegY = true;
			m_YaxisIsPosY = false;
			int test = 5;
		}
	}

	m_oldRotationX = rotation.x;
	m_Models[selectionState->getClosestId()]->setRotation(rotation);
	//resetto la variabile di controllo
	m_cubeIsBeingRotated = false;
	m_cubeCurrentRotationAroundY = 0.0f;
	m_cubeCurrentRotationAroundX = 0.0f;
	


	return true;
}

float ApplicationClass::calculateDelta(float r, float a){

	float angle = a;
	float delta = angle - abs(r);

	return abs(delta);
}