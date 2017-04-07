#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

// Std. Includes
#include <string>
#include <iostream>
#include <irrklang/irrKlang.h>
using namespace irrklang;



// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>




// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other Libs
#include <SOIL.h>

#include "functions.h"

#include "globals.h"






using namespace std;







// The MAIN function, from here we start our application and run our Game loop
int main()
{
	
	print_help();
	
	// Init GLFW
	glfwInit();



	GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Ninja", nullptr, nullptr); 

	glfwMakeContextCurrent(window);

	// Set the required callback functions
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// Options
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Initialize GLEW to setup the OpenGL Function pointers
	glewExperimental = GL_TRUE;
	glewInit();

	// Define the viewport dimensions
	glViewport(0, 0, screenWidth, screenHeight);

	// Setup some OpenGL options
	glEnable(GL_DEPTH_TEST);

	// Setup and compile our shaders
	Shader shader("vertex_shader.vs", "frag_shader.frag");

	// Load models

	Model model_torso("model/torso2.obj");
	Model model_arm("model/arm2.obj");
	Model model_leg("model/leg2.obj");
	Model model_limb("model/limb2.obj");
	Model model_head("model/head2.obj");

	

	// Game loop

	// load sound
	ISoundEngine *SoundEngine = createIrrKlangDevice();
	SoundEngine->play2D("audio/ninja.wav", false);
	
	while (!glfwWindowShouldClose(window))
	{
		// models
		glm::mat4 model;
		glm::mat4 model_save;
	

		
		// Set frame time
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;


		//cout << glfwGetTime()<<endl;

		// Check and call events
		glfwPollEvents();
		do_movement();
		rotate_parts();
		do_animation();

		// Clear the colorbuffer
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.Use();   // <-- Don't forget this one!
						// Transformation matrices
		glm::mat4 projection = glm::perspective(camera.Zoom, (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

		// draw all models
		model = draw_all_models(model, shader, model_torso, model_limb, model_leg, model_arm, model_head);

		first_loop = false;
		// Swap the buffers
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}

#pragma region "User input"

#pragma endregion

