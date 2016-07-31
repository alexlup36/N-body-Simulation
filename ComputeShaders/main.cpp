#include <SDL.h>
#include <gl\glew.h>
#include <SDL_opengl.h>
#include <gl\GLU.h>
#include <stdio.h>
#include <string>
#include <memory>
#include <SDL_ttf.h>

// Current directory
#include <windows.h>
#include <tchar.h>

#include "Shader.h"
#include "ShaderMan.h"
#include "MeshManager.h"
#include "CameraMan.h"
#include "Common.h"
#include "SDLInit.h"
#include "DebugOutput.h"
#include "Texture.h"
#include "ComputeParticles.h"

#include "Triangle.h"
#include "Quad.h"

// ----------------------------------------------------------------------------

bool initGL()
{
	bool bSuccess = true;

	// Initialize the clear color
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Enable multisampling
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

#ifdef _DEBUG

	glDebugMessageCallback(DebugOutput::debugOutput, NULL);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);

#endif // DEBUG

	return bSuccess;
}

// ----------------------------------------------------------------------------

void render(MeshManager& meshManager, CameraMan& cameraManager)
{
	// Clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw meshes
	meshManager.Draw(cameraManager.GetActiveCamera());
}

// ----------------------------------------------------------------------------

void handleKeys(unsigned char key)
{
	if (key = 'q')
	{
	}
}

// ----------------------------------------------------------------------------

int main(int argc, char* argv[])
{
	// ------------------------------------------------------------------------
	// Fill structure information
	ContextInfo context;
	memset(&context, 0, sizeof(ContextInfo));
	context.Core = true;
	context.MajorVersion = 4;
	context.MinorVersion = 4;

	WindowInfo window;
	memset(&window, 0, sizeof(WindowInfo));
	window.AllowReshape = true;
#ifdef X_FULLSCREEN
	window.FullScreen = false;
#endif // X_FULLSCREEN
	window.WindowPosX = 100;
	window.WindowPosY = 100;
	window.WindowWidth = WINDOW_WIDTH;
	window.WindowHeight = WINDOW_HEIGHT;
	window.WindowName = "RenderingEngine";

	FrameBufferInfo frameBuffer;
	memset(&frameBuffer, 0, sizeof(FrameBufferInfo));
	frameBuffer.EnableMSAA = true;
	frameBuffer.EnableSRGB = true;
	frameBuffer.EnableVSync = true;
	frameBuffer.MSAASampleCount = 16;

	// ------------------------------------------------------------------------
	// Get current directory
	const int BufferSize = MAX_PATH;
	TCHAR buffer[BufferSize];
	DWORD dwRet = GetCurrentDirectory(BufferSize, buffer);

	// ------------------------------------------------------------------------
	// Initialization and main loop
	if (!SDLInit::Init(context, window, frameBuffer))
	{
		printf("Failed to initialize SDL\n");
		return -1;
	}
	else
	{
		glGetError();

		check_gl_error();

		// Get the window
		SDL_Window* window = SDLInit::GetWindow();
		check_gl_error();

		// ------------------------------------------------------------------------
		// Initialize managers
		// ------------------------------------------------------------------------
		
		// Managers
		std::shared_ptr<ShaderMan> shaderManager = std::make_shared<ShaderMan>();
		std::shared_ptr<MeshManager> meshManager = nullptr;
		std::shared_ptr<CameraMan> cameraManager = std::make_shared<CameraMan>();

		// ------------------------------------------------------------------------
		// Initialize shaders
		// ------------------------------------------------------------------------
		Shader* solidColorQuadShader		= new Shader();
		Shader* solidColorTriangleShader	= new Shader();
		Shader* computeShader				= new Shader();
		Shader* textureQuadShader			= new Shader();
		Shader* computeParticleShader		= new Shader();
		Shader* renderParticleShader		= new Shader();

		solidColorQuadShader->AddSource(Shader::ShaderType::Vertex, "solidColorQuadShader.vert");
		solidColorQuadShader->AddSource(Shader::ShaderType::Fragment, "solidColorQuadShader.frag");
		solidColorQuadShader->SetupShaders();

		solidColorTriangleShader->AddSource(Shader::ShaderType::Vertex, "solidColorTriangleShader.vert");
		solidColorTriangleShader->AddSource(Shader::ShaderType::Fragment, "solidColorTriangleShader.frag");
		solidColorTriangleShader->SetupShaders();

		computeShader->AddSource(Shader::ShaderType::Compute, "compute.comp");
		computeShader->SetupShaders();

		textureQuadShader->AddSource(Shader::ShaderType::Vertex, "textureQuadShader.vert");
		textureQuadShader->AddSource(Shader::ShaderType::Fragment, "textureQuadShader.frag");
		textureQuadShader->SetupShaders();

		renderParticleShader->AddSource(Shader::ShaderType::Vertex, "renderParticles.vert");
		renderParticleShader->AddSource(Shader::ShaderType::Fragment, "renderParticles.frag");
		renderParticleShader->SetupShaders();

		computeParticleShader->AddSource(Shader::ShaderType::Compute, "computeParticles.comp");
		computeParticleShader->SetupShaders();

		shaderManager->AddShader("SolidColorQuadShader", solidColorQuadShader);
		shaderManager->AddShader("SolidColorTriangleShader", solidColorTriangleShader);
		shaderManager->AddShader("ComputeShader", computeShader);
		shaderManager->AddShader("TextureQuadShader", textureQuadShader);
		shaderManager->AddShader("RenderParticlesShader", renderParticleShader);
		shaderManager->AddShader("ComputeParticleShader", computeParticleShader);

		check_gl_error();
		
		// Set the uniform in the compute shader to be image unit 0
		GLuint triangleProgram = shaderManager->GetShader("SolidColorTriangleShader");
		glUseProgram(triangleProgram);
		glGetUniformLocation(triangleProgram, "destTex");

		check_gl_error();

		// --------------------------------------------------------------------
		// --------------------------------------------------------------------
		// --------------------------------------------------------------------
		// Create texture
		std::shared_ptr<Texture> wallTexture = std::make_shared<Texture>(
			"wall.jpg",
			TextureType::Diffuse,
			true,
			true,
			GL_TEXTURE_2D,
			GL_LINEAR
			);

		//glUseProgram(shaderManager->GetShader("TextureQuadShader"));
		//wallTexture->Bind(0, shaderManager->GetShader("TextureQuadShader"));

		check_gl_error();

		std::shared_ptr<Texture> computeShaderTexture = std::make_shared<Texture>(
			512, 512,
			GL_R32F,
			GL_RED,
			GL_FLOAT,
			GL_TEXTURE_2D,
			GL_LINEAR
			);

		glUseProgram(shaderManager->GetShader("ComputeShader"));
		computeShaderTexture->BindImage(0, shaderManager->GetShader("ComputeShader"));

		check_gl_error();

		// --------------------------------------------------------------------
		// --------------------------------------------------------------------
		// --------------------------------------------------------------------
		// Compute shader setup

		// dispatch work group structure
		static struct
		{
			GLuint num_groups_x;
			GLuint num_groups_y;
			GLuint num_groups_z;
		} dispatch_params;

		// --------------------------------------------------------------------
		// Get max work group size
		GLint maxSizeX, maxSizeY, maxSizeZ;
		glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 0, &maxSizeX);
		glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 1, &maxSizeY);
		glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 2, &maxSizeZ);

		check_gl_error();

		// Get work group size
		GLint workGroupCountX, workGroupCountY, workGroupCountZ;
		glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 0, &workGroupCountX);
		glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 1, &workGroupCountY);
		glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 2, &workGroupCountZ);

		check_gl_error();

		// Get max shared memory 
		GLint maxSharedMemory;
		glGetIntegerv(GL_MAX_COMPUTE_SHARED_MEMORY_SIZE, &maxSharedMemory);

		check_gl_error();

		int textureSizeX = 512;
		int textureSizeY = 512;

		// Set dispatch_params
		dispatch_params.num_groups_x = textureSizeX > workGroupCountX ? workGroupCountX : textureSizeX;
		dispatch_params.num_groups_y = textureSizeY > workGroupCountY ? workGroupCountY : textureSizeY;
		dispatch_params.num_groups_z = 1;

		// --------------------------------------------------------------------
		// Activate shader
		glUseProgram(shaderManager->GetShader("ComputeShader"));

		check_gl_error();

		// --------------------------------------------------------------------
		// Create dispatch buffer and bind it
		GLuint dispatch_buffer;
		glGenBuffers(1, &dispatch_buffer);
		glBindBuffer(GL_DISPATCH_INDIRECT_BUFFER, dispatch_buffer);

		check_gl_error();

		// --------------------------------------------------------------------
		// Set dispatch buffer data
		glBufferData(GL_DISPATCH_INDIRECT_BUFFER, sizeof(dispatch_params), &dispatch_params, GL_STATIC_DRAW);

		check_gl_error();

		glDispatchComputeIndirect(0);

		check_gl_error();	

		// --------------------------------------------------------------------
		// --------------------------------------------------------------------
		// --------------------------------------------------------------------

		// Bind the result of the compute shader to the textureQuadShader
		glUseProgram(shaderManager->GetShader("TextureQuadShader"));
		computeShaderTexture->Bind(0, shaderManager->GetShader("TextureQuadShader"));

		// --------------------------------------------------------------------
		// --------------------------------------------------------------------
		// --------------------------------------------------------------------
		// Particle setup
		check_gl_error();

		std::shared_ptr<ComputeParticles> computeParticles = std::make_shared<ComputeParticles>();
		computeParticles->Initialize(shaderManager->GetShader("ComputeParticleShader"), 
			shaderManager->GetShader("RenderParticlesShader"));

		check_gl_error();

		// --------------------------------------------------------------------
		// --------------------------------------------------------------------
		// --------------------------------------------------------------------

		// ------------------------------------------------------------------------
		// Create mesh manager
		meshManager = std::make_shared<MeshManager>();

		// ------------------------------------------------------------------------
		// Create camera
		cameraManager->CreateCamera("mainCamera", 45.0f, 0.01f, 3000.0f);
		cameraManager->SetActiveCamera("mainCamera");

		cameraManager->CreateCamera("secondCamera", 45.0f, 0.01f, 3000.0f);

		// ------------------------------------------------------------------------
		// Create a quad and a triangle
		std::shared_ptr<Triangle> pTriangle		= std::make_shared<Triangle>();
		std::shared_ptr<Quad> pQuad				= std::make_shared<Quad>();
		std::shared_ptr<Quad> pQuadFullScreen	= std::make_shared<Quad>();

		pTriangle->SetProgram(shaderManager->GetShader("SolidColorTriangleShader"));
		pQuad->SetProgram(shaderManager->GetShader("SolidColorQuadShader"));
		pQuadFullScreen->SetProgram(shaderManager->GetShader("TextureQuadShader"));

		pTriangle->Create();
		pQuad->Create();
		pQuadFullScreen->CreateScreenPercentage(0.5f);

		// ------------------------------------------------------------------------ 

		// Initialize OpenGL
		if (initGL() == false)
		{
			printf("Unable to initialize OpenGL\n");
			return -1;
		}
		else
		{
			// Main loop
			bool bQuit = false;

			float dt = 0.0f;

			// Event handler
			SDL_Event e;
			// Enable text input
			SDL_StartTextInput();

			// Initialize the performance counter
			// Get the performance counter frequency (seconds per count)
			float secondPerCount = 1.0f / (float)SDL_GetPerformanceFrequency();
			Uint64 prevTimeStamp = 0;

			while (!bQuit)
			{
				// Get the initial value for the counter
				prevTimeStamp = SDL_GetPerformanceCounter();
				// Get the current time stamp
				Uint64 currentTimeStamp = SDL_GetPerformanceCounter();
				// Calculate the time difference between the two measurements
				dt = (currentTimeStamp - prevTimeStamp) * secondPerCount;

				// While there are pending events
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						bQuit = true;
					}
				}

				// Clear buffers
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				// Update input
				cameraManager->Update(dt, e);

				check_gl_error();

				// Draw particles
				computeParticles->Draw(dt,
					cameraManager->GetActiveCamera(),
					shaderManager->GetShader("ComputeParticleShader"),
					shaderManager->GetShader("RenderParticlesShader"));

				check_gl_error();

				// No events to handle => do the rendering
				//render(*meshManager, *cameraManager);
				//pTriangle->Draw(cameraManager->GetActiveCamera());
				//pQuad->Draw(cameraManager->GetActiveCamera());
				//pQuadFullScreen->Draw(cameraManager->GetActiveCamera());

				// Update the previous time stamp
				prevTimeStamp = currentTimeStamp;

				// Update screen
				SDL_GL_SwapWindow(window);
			}

			// Disable text input
			SDL_StopTextInput();
		}
	}

	return 0;
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------