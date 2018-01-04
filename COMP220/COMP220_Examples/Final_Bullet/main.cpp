//main.cpp - defines the entry point of the application

#include "main.h"

int main(int argc, char* args[])
{

#pragma region Init

	//Initialises the SDL Library, passing in SDL_INIT_VIDEO to only initialise the video subsystems
	//https://wiki.libsdl.org/SDL_Init
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		//Display an error message box
		//https://wiki.libsdl.org/SDL_ShowSimpleMessageBox
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, SDL_GetError(), "SDL_Init failed", NULL);
		return 1;
	}

	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

	//Create a window, note we have to free the pointer returned using the DestroyWindow Function
	//https://wiki.libsdl.org/SDL_CreateWindow
	SDL_Window* window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	//Checks to see if the window has been created, the pointer will have a value of some kind
	if (window == nullptr)
	{
		//Show error
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, SDL_GetError(), "SDL_CreateWindow failed", NULL);
		//Close the SDL Library
		//https://wiki.libsdl.org/SDL_Quit
		SDL_Quit();
		return 1;
	}

	//lets ask for a 3.2 core profile version of OpenGL
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_GLContext GL_Context = SDL_GL_CreateContext(window);
	if (GL_Context == nullptr)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, SDL_GetError(), "SDL GL Create Context failed", NULL);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}
	//Initialize GLEW
	glewExperimental = GL_TRUE;
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, (char*)glewGetErrorString(glewError), "GLEW Init Failed", NULL);
	}

#pragma endregion

#pragma region Mesh Properties

	// GameObject list
	std::vector<GameObject*> gameObjectList;

	for (int i = 0; i < 3; i++)
	{
		// Create GameObject
		GameObject * droid = new GameObject();
		droid->loadMeshes("GNK_Droid.FBX");
		droid->loadDiffuseMap("GNK_BaseColor.png");
		droid->setPosition(vec3(0.0f, (float)i*11.5f, 0.0f));
		droid->setScale(vec3(0.1f, 0.1f, 0.1f));
		droid->setRotation(vec3(radians(-90.0f), 0.0f, 0.0f));
		droid->loadShaderProgram("lightingVert.glsl", "lightingFrag.glsl");
		gameObjectList.push_back(droid);
	}
		
	/*droid = new GameObject();
	droid->loadMeshes("GNK_Droid.FBX");
	droid->loadDiffuseMap("GNK_BaseColor.png");
	droid->setPosition(vec3(0.0f, 2.0f, 0.0f));
	droid->setScale(vec3(0.1f, 0.1f, 0.1f));
	droid->setRotation(vec3(radians(-90.0f), 0.0f, 0.0f));
	droid->loadShaderProgram("lightingVert.glsl", "lightingFrag.glsl");
	gameObjectList.push_back(droid);*/

	GameObject * coffee = new GameObject();
	coffee->loadMeshes("Coffee.FBX");
	coffee->loadDiffuseMap("Coffee.tga");
	coffee->setPosition(vec3(2.0f, 15.0f, 5.0f));
	coffee->setScale(vec3(0.3f, 0.3f, 0.3f));
	coffee->setRotation(vec3(0.0f, radians(-90.0f), 0.0f));
	coffee->loadShaderProgram("lightingVert.glsl", "lightingFrag.glsl");
	gameObjectList.push_back(coffee);

	//unsigned int numberOfVerts = 0;
	//unsigned int numberOfIndices = 0;
	//loadModelFromFile("Tank1.FBX", vertexbuffer, elementbuffer, numberOfVerts, numberOfIndices);

	/*std::vector<Mesh*> meshes;
	loadMeshesFromFile("GNK_Droid.FBX", meshes);

	GLuint textureID = loadTextureFromFile("GNK_BaseColor.png");*/

	/*vec3 objPosition = vec3(0.0f,10.0f,0.0f);
	vec3 objScale = vec3(0.1f, 0.1f, 0.1f);
	vec3 objRotation = vec3(radians(-90.0f), 0.0f, 0.0f);*/

	// Coffee transform
	/*vec3 objPosition = vec3(0.0f, 0.0f, 35.0f);
	vec3 objScale = vec3(0.7f, 0.7f, 0.7f);
	vec3 objRotation = vec3(0.0f, radians(-90.0f), 0.0f);*/

	
	/*mat4 translationMatrix = translate(objPosition);
	mat4 scaleMatrix = scale(objScale);
	mat4 rotationMatrix= rotate(objRotation.x, vec3(1.0f, 0.0f, 0.0f))*rotate(objRotation.y, vec3(0.0f, 1.0f, 0.0f))*rotate(objRotation.z, vec3(0.0f, 0.0f, 1.0f));

	mat4 modelMatrix = translationMatrix*rotationMatrix*scaleMatrix;*/

	// Camera Properties
	vec3 cameraPosition = vec3(0.0f, 8.0f, -30.0f);
	vec3 cameraTarget = vec3(0.0f, 0.0f, 0.0f);
	vec3 cameraUp = vec3(0.0f, 1.0f, 0.0f);
	vec3 cameraDirection = vec3(0.0f);
	vec3 FPScameraPos = vec3(0.0f);	
	float CameraX = 0.0f;
	float CameraY = 0.0f;
	float CameraDistance = (float)(cameraTarget - cameraPosition).length();	

	mat4 viewMatrix = lookAt(cameraPosition, cameraTarget, cameraUp);
	mat4 projectionMatrix = perspective(radians(90.0f), float(800 / 600), 0.1f, 100.0f);
#pragma endregion

#pragma region Light and Material

	//light
	vec3 lightDirection = vec3(0.0f, 0.0f, -1.0f);
	vec4 diffuseLightColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	vec4 specularLightColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	vec4 ambientLightColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);

	//material
	/*vec4 diffuseMaterialColour = vec4(0.9f, 0.9f, 0.9f, 1.0f);
	vec4 specularMaterialColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	vec4 ambientMaterialColour = vec4(0.1f, 0.1f, 0.1f, 1.0f);
	float specularPower = 25.0f;*/

#pragma endregion

#pragma region PostProcessBuffers

	// Colour Buffer Texture
	GLuint colourBufferID = createTexture(800, 600);

	// Create Depth Buffer
	GLuint depthRenderBufferID;
	glGenRenderbuffers(1, &depthRenderBufferID);
	glBindRenderbuffer(GL_RENDERBUFFER, depthRenderBufferID);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, 800, 600);

	// Create Frame Buffer
	GLuint frameBufferID;
	glGenFramebuffers(1, &frameBufferID);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthRenderBufferID);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, colourBufferID, 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Unable to create frame buffer for post processing", "Frame Buffer Error", NULL);
	}

	// create screen aligned quad
	GLfloat screenVerts[] =
	{
		-1, -1,
		1, -1,
		-1, 1,
		1, 1
	};

	GLuint screenQuadVBOID;
	glGenBuffers(1, &screenQuadVBOID);
	glBindBuffer(GL_ARRAY_BUFFER, screenQuadVBOID);
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(GLfloat), screenVerts, GL_STATIC_DRAW);

	GLuint screenVAO;
	glGenVertexArrays(1, &screenVAO);
	glBindVertexArray(screenVAO);
	glBindBuffer(GL_ARRAY_BUFFER, screenQuadVBOID);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);

#pragma endregion

#pragma region Load Shaders

	GLuint postProcessingProgramID = LoadShaders("passThroughVert.glsl", "postTextureFrag.glsl");
	GLint texture0Location = glGetUniformLocation(postProcessingProgramID, "texture0");

	//glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// GLuint programID = LoadShaders("lightingVert.glsl", "lightingFrag.glsl");

	static const GLfloat fragColour[] = { 0.0f,1.0f,0.0f,1.0f };

#pragma endregion

#pragma region GetUniformLocations

	/*GLint fragColourLocation = glGetUniformLocation(programID, "fragColour");
	GLint currentTimeLocation= glGetUniformLocation(programID, "time");
	GLint modelMatrixLocation = glGetUniformLocation(programID, "modelMatrix");
	GLint viewMatrixLocation = glGetUniformLocation(programID, "viewMatrix");
	GLint projectionMatrixLocation = glGetUniformLocation(programID, "projectionMatrix");
	GLint textureLocation = glGetUniformLocation(programID, "baseTexture");
	GLint cameraPositionLocation = glGetUniformLocation(programID, "cameraPosition");

	GLint lightDirectionLocation = glGetUniformLocation(programID, "lightDirection");
	GLint ambientLightColourLocation = glGetUniformLocation(programID, "ambientLightColour");
	GLint diffuseLightColourLocation = glGetUniformLocation(programID, "diffuseLightColour");
	GLint specularLightColourLocation = glGetUniformLocation(programID, "specularLightColour");

	GLint ambientMaterialColourLocation = glGetUniformLocation(programID, "ambientMaterialColour");
	GLint diffuseMaterialColourLocation = glGetUniformLocation(programID, "diffuseMaterialColour");
	GLint specularMaterialColourLocation = glGetUniformLocation(programID, "specularMaterialColour");
	GLint specularPowerLocation = glGetUniformLocation(programID, "specularPower");*/

#pragma endregion

#pragma region BulletPhysics

	///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
	btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();

	///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
	btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);

	///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
	btBroadphaseInterface* overlappingPairCache = new btDbvtBroadphase();

	///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
	btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;

	btDiscreteDynamicsWorld* dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);

	dynamicsWorld->setGravity(btVector3(0, -10, 0));


	btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(50.), btScalar(2.), btScalar(50.)));
	// Create Dynamic Objects
	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(0, -15, 0));

	btScalar groundMass(0.);

	btVector3 groundInertia(0, 0, 0);

	//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
	btDefaultMotionState* groundMotionState = new btDefaultMotionState(groundTransform);
	btRigidBody::btRigidBodyConstructionInfo groundRbInfo(groundMass, groundMotionState, groundShape, groundInertia);
	btRigidBody* groundRigidBody = new btRigidBody(groundRbInfo);

	//add the body to the dynamics world
	dynamicsWorld->addRigidBody(groundRigidBody);
	
	btCollisionShape* coffeeCollisionShape = new btBoxShape(btVector3(2, 2, 2));
	// Create Dynamic Objects
	btTransform coffeeTransform;
	coffeeTransform.setIdentity();
	btScalar coffeeMass(1.f);

	//droidTransform.setOrigin(btVector3(droid->getPosition.x, droid->getPosition.y, droid->getPosition.z));

	//rigidbody is dynamic if and only if mass is non zero, otherwise static
	bool isDynamic = (coffeeMass != 0.f);

	btVector3 coffeeInertia(0, 0, 0);
	if (isDynamic)
		coffeeCollisionShape->calculateLocalInertia(coffeeMass, coffeeInertia);

	btDefaultMotionState* coffeeMotionState = new btDefaultMotionState(coffeeTransform);
	btRigidBody::btRigidBodyConstructionInfo coffeeRbInfo(coffeeMass, coffeeMotionState, coffeeCollisionShape, coffeeInertia);
	btRigidBody* coffeeRigidBody = new btRigidBody(coffeeRbInfo);

	dynamicsWorld->addRigidBody(coffeeRigidBody);

	btVector3 coffeeForce = btVector3(5, 10, 0);
	btVector3 coffeeImpulse = btVector3(0, 4, -2);
	btVector3 coffeeTorque = btVector3(0, 4, -2);
	int InvertGravity = -10;

#pragma endregion

#pragma region Event Loop

	//SDL_ShowCursor(SDL_DISABLE);
	SDL_SetRelativeMouseMode(SDL_bool(SDL_ENABLE));

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	int lastTicks = SDL_GetTicks();
	int currentTicks = SDL_GetTicks();

	//Event loop, we will loop until running is set to false, usually if escape has been pressed or window is closed
	bool running = true;
	//SDL Event structure, this will be checked in the while loop
	SDL_Event ev;
	while (running)
	{
		//Poll for the events which have happened in this frame
		//https://wiki.libsdl.org/SDL_PollEvent
		while (SDL_PollEvent(&ev))
		{
			//Switch case for every message we are intereted in
			switch (ev.type)
			{
				//QUIT Message, usually called when the window has been closed
			case SDL_QUIT:
				running = false;
				break;

			case SDL_MOUSEMOTION:
				// Get Mouse Motion of X and Y
				CameraX += ev.motion.xrel / 200.0f;
				CameraY += -ev.motion.yrel / 200.0f;
				// Limit camera range
				if (CameraY > 150.0f) CameraY = 150.0f; else if (CameraY < -150.0f) CameraY = -150.0f;
				// Calculate camera target using CameraX and CameraY
				cameraTarget = cameraPosition + CameraDistance * vec3(cos(CameraX), tan(CameraY), sin(CameraX));
				// Normalised camera direction
				cameraDirection = normalize(cameraTarget - cameraPosition);
				
				break;

				//KEYDOWN Message, called when a key has been pressed down
			case SDL_KEYDOWN:
				//Check the actual key code of the key that has been pressed
				switch (ev.key.keysym.sym)
				{
					// Keys
				case SDLK_ESCAPE:
					running = false;
					break;

				case SDLK_w:
					FPScameraPos = cameraDirection * 0.2f;
					break;
				case SDLK_s:
					FPScameraPos = -cameraDirection * 0.2f;
					break;
				case SDLK_a:
					FPScameraPos = -cross(cameraDirection, cameraUp) * 0.5f;
					break;
				case SDLK_d:
					FPScameraPos = cross(cameraDirection, cameraUp) * 0.5f;
					break;

				case SDLK_SPACE:
					//Invert Gravity
					InvertGravity *= -1;
					dynamicsWorld->setGravity(btVector3(0.0, InvertGravity, 0.0));
					std::cout << "G = " << InvertGravity << " ";
					break;
				case SDLK_LEFT:
					//Apply a force
					coffeeRigidBody->applyCentralForce(coffeeForce);
					break;
				case SDLK_RIGHT:
					//Apply a force
					coffeeRigidBody->applyCentralForce(btVector3(-5, 10, 0) * 50);
					break;
				case SDLK_DOWN:
					//Apply an impulse
					coffeeRigidBody->applyCentralImpulse(coffeeImpulse);
					printf("J");
					break;
				case SDLK_UP:
					//Apply an torque impulse
					coffeeRigidBody->applyTorqueImpulse(coffeeTorque);
					break;


				}
				cameraPosition += FPScameraPos;
				cameraTarget += FPScameraPos;
			}
		}
		//Update Game and Draw with OpenGL!!		

		currentTicks = SDL_GetTicks();
		float deltaTime = (float)(currentTicks - lastTicks) / 1000.0f;

		#pragma region Physics

		dynamicsWorld->stepSimulation(10.0f / 60.0f, 1);

		coffeeTransform = coffeeRigidBody->getWorldTransform();
		btVector3 coffeeOrigin = coffeeTransform.getOrigin();
		btQuaternion coffeeRotation = coffeeTransform.getRotation();

		coffee->setPosition(vec3(coffeeOrigin.getX(), coffeeOrigin.getY(), coffeeOrigin.getZ()));
		coffee->setRotation(vec3(coffeeRotation.getX(), coffeeRotation.getY(), coffeeRotation.getZ()));

		//mat4 translationMatrix = coffee->getPosition;
		//mat4 scaleMatrix = coffee->getScale;
		//mat4 rotationMatrix = coffee.get //(coffee->getRotation.x, vec3(1.0f, 0.0f, 0.0f))*(coffee->getRotation.y, vec3(0.0f, 1.0f, 0.0f))*(coffee->getRotation.z, vec3(0.0f, 0.0f, 1.0f));
		//mat4 modelMatrix = translationMatrix*rotationMatrix*scaleMatrix;

		viewMatrix = lookAt(cameraPosition, cameraTarget, cameraUp);

		// old code
		/*btTransform trans;
		fallRigidBody->getMotionState()->getWorldTransform(trans);
		btVector3 rigidBodyPos = trans.getOrigin();
		objectPosition = vec3(rigidBodyPos.x(), rigidBodyPos.y(), rigidBodyPos.z());

		mat4 translationMatrix = translate(objectPosition);
		mat4 scaleMatrix = scale(objectScale);
		mat4 rotationMatrix = rotate(objectRotation.x, vec3(1.0f, 0.0f, 0.0f))*rotate(objectRotation.y, vec3(0.0f, 1.0f, 0.0f))*rotate(objectRotation.z, vec3(0.0f, 0.0f, 1.0f));*/



		#pragma endregion		

		glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClearDepth(1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT);

		// DROID
		//droid->Update();
		for (GameObject * pObj : gameObjectList)
		{
			pObj->Update();
		}

		//droid->preRender();
		for (GameObject * pObj : gameObjectList)
		{
			pObj->preRender();
			GLuint currentShaderProgramID = pObj->getShaderProgramID();

			GLint viewMatrixLocation = glGetUniformLocation(currentShaderProgramID, "viewMatrix");
			GLint projectionMatrixLocation = glGetUniformLocation(currentShaderProgramID, "projectionMatrix");

			GLint cameraPositionLocation = glGetUniformLocation(currentShaderProgramID, "cameraPosition");

			GLint lightDirectionLocation = glGetUniformLocation(currentShaderProgramID, "lightDirection");
			GLint ambientLightColourLocation = glGetUniformLocation(currentShaderProgramID, "ambientLightColour");
			GLint diffuseLightColourLocation = glGetUniformLocation(currentShaderProgramID, "diffuseLightColour");
			GLint specularLightColourLocation = glGetUniformLocation(currentShaderProgramID, "specularLightColour");

			glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, value_ptr(viewMatrix));
			glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, value_ptr(projectionMatrix));
			glUniform3fv(cameraPositionLocation, 1, value_ptr(cameraPosition));
			glUniform3fv(lightDirectionLocation, 1, value_ptr(lightDirection));
			glUniform4fv(diffuseLightColourLocation, 1, value_ptr(diffuseLightColour));
			glUniform4fv(specularLightColourLocation, 1, value_ptr(specularLightColour));
			glUniform4fv(ambientLightColourLocation, 1, value_ptr(ambientLightColour));
			pObj->Render();
		}

		/*GLuint currentShaderProgramID = droid->getShaderProgramID();

		GLint viewMatrixLocation = glGetUniformLocation(currentShaderProgramID, "viewMatrix");
		GLint projectionMatrixLocation = glGetUniformLocation(currentShaderProgramID, "projectionMatrix");

		GLint cameraPositionLocation = glGetUniformLocation(currentShaderProgramID, "cameraPosition");

		GLint lightDirectionLocation = glGetUniformLocation(currentShaderProgramID, "lightDirection");
		GLint ambientLightColourLocation = glGetUniformLocation(currentShaderProgramID, "ambientLightColour");
		GLint diffuseLightColourLocation = glGetUniformLocation(currentShaderProgramID, "diffuseLightColour");
		GLint specularLightColourLocation = glGetUniformLocation(currentShaderProgramID, "specularLightColour");

		glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, value_ptr(viewMatrix));
		glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, value_ptr(projectionMatrix));
		glUniform3fv(cameraPositionLocation, 1, value_ptr(cameraPosition));
		glUniform3fv(lightDirectionLocation,1,value_ptr(lightDirection));
		glUniform4fv(diffuseLightColourLocation, 1, value_ptr(diffuseLightColour));
		glUniform4fv(specularLightColourLocation, 1, value_ptr(specularLightColour));
		glUniform4fv(ambientLightColourLocation, 1, value_ptr(ambientLightColour));
		droid->Render();*/

		// COFFEE
		/*coffee->Update();
		coffee->preRender();
		currentShaderProgramID = coffee->getShaderProgramID();

		viewMatrixLocation = glGetUniformLocation(currentShaderProgramID, "viewMatrix");
		projectionMatrixLocation = glGetUniformLocation(currentShaderProgramID, "projectionMatrix");

		cameraPositionLocation = glGetUniformLocation(currentShaderProgramID, "cameraPosition");

		lightDirectionLocation = glGetUniformLocation(currentShaderProgramID, "lightDirection");
		ambientLightColourLocation = glGetUniformLocation(currentShaderProgramID, "ambientLightColour");
		diffuseLightColourLocation = glGetUniformLocation(currentShaderProgramID, "diffuseLightColour");
		specularLightColourLocation = glGetUniformLocation(currentShaderProgramID, "specularLightColour");

		glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, value_ptr(viewMatrix));
		glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, value_ptr(projectionMatrix));
		glUniform3fv(cameraPositionLocation, 1, value_ptr(cameraPosition));
		glUniform3fv(lightDirectionLocation, 1, value_ptr(lightDirection));
		glUniform4fv(diffuseLightColourLocation, 1, value_ptr(diffuseLightColour));
		glUniform4fv(specularLightColourLocation, 1, value_ptr(specularLightColour));
		glUniform4fv(ambientLightColourLocation, 1, value_ptr(ambientLightColour));
		coffee->Render();*/

		//glActiveTexture(GL_TEXTURE);
		//glBindTexture(GL_TEXTURE_2D, textureID);

		//glUseProgram(programID);

		//glUniform4fv(fragColourLocation, 1, fragColour);
		//glUniform1f(currentTimeLocation, (float)(currentTicks) / 1000.0f);
		//glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, value_ptr(modelMatrix));
		//glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, value_ptr(viewMatrix));
		//glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, value_ptr(projectionMatrix));

		//glUniform3fv(cameraPositionLocation, 1, value_ptr(cameraPosition));

		//glUniform1i(textureLocation, 0);

		//glUniform3fv(lightDirectionLocation,1,value_ptr(lightDirection));
		//glUniform4fv(diffuseLightColourLocation, 1, value_ptr(diffuseLightColour));
		//glUniform4fv(specularLightColourLocation, 1, value_ptr(specularLightColour));
		//glUniform4fv(ambientLightColourLocation, 1, value_ptr(ambientLightColour));

		//glUniform4fv(diffuseMaterialColourLocation, 1, value_ptr(diffuseMaterialColour));
		//glUniform4fv(specularMaterialColourLocation, 1, value_ptr(specularMaterialColour));
		//glUniform1f(specularPowerLocation, specularPower);
		//glUniform4fv(ambientMaterialColourLocation, 1, value_ptr(ambientMaterialColour));

		//// Draw
		//for (Mesh* currentMesh : meshes)
		//{
		//	currentMesh->render();
		//}
		//glDisable(GL_DEPTH_TEST);
		

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Bind Post Processing Shaders
		glUseProgram(postProcessingProgramID);

		// Activate texture unit 0 for the colour buffer
		glActiveTexture(GL_TEXTURE);
		glBindTexture(GL_TEXTURE_2D, colourBufferID);
		glUniform1i(texture0Location, 0);

		// Draw!
		glBindVertexArray(screenVAO);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		SDL_GL_SwapWindow(window);

	}

#pragma endregion

#pragma region GarbageCollection/Quit

	//dynamicsWorld->removeRigidBody(droidRigidBody);
	//delete droidCollisionShape;
	//delete droidRigidBody->getMotionState();
	//delete droidRigidBody;

	//dynamicsWorld->removeRigidBody(groundRigidBody);
	//// delete ground
	//delete groundShape;
	//delete groundRigidBody->getMotionState();
	//delete groundRigidBody;

	////delete dynamics world
	//delete dynamicsWorld;

	////delete solver
	//delete solver;

	////delete broadphase
	//delete overlappingPairCache;

	////delete dispatcher
	//delete dispatcher;

	//delete collisionConfiguration;

	/*auto iter = meshes.begin();
	while (iter != meshes.end())
	{
		if ((*iter))
		{
			(*iter)->destroy();
			delete (*iter);
			iter = meshes.erase(iter);
		}
		else
		{
			iter++;
		}
	}*/

	auto gameObjectIter = gameObjectList.begin();
	while (gameObjectIter != gameObjectList.end())
	{
		if ((*gameObjectIter))
		{
			(*gameObjectIter)->destroy();
			delete (*gameObjectIter);
			gameObjectIter = gameObjectList.erase(gameObjectIter);
		}
	}
	glDeleteProgram(postProcessingProgramID);
	glDeleteVertexArrays(1, &screenVAO);
	glDeleteBuffers(1, &screenQuadVBOID);
	glDeleteFramebuffers(1, &frameBufferID);
	glDeleteRenderbuffers(1, &depthRenderBufferID);
	glDeleteTextures(1, &colourBufferID);

	/*meshes.clear();

	glDeleteProgram(programID);
	glDeleteTextures(1, &textureID);*/
	/*if (droid)
	{
		droid->destroy();
		delete droid;
		droid = nullptr;
	}
*/
	//Delete context
	SDL_GL_DeleteContext(GL_Context);

	//Destroy the window and quit SDL2, NB we should do this after all cleanup in this order!!!
	//https://wiki.libsdl.org/SDL_DestroyWindow
	SDL_DestroyWindow(window);

	IMG_Quit();

	//https://wiki.libsdl.org/SDL_Quit
	SDL_Quit();

#pragma endregion

	return 0;
}