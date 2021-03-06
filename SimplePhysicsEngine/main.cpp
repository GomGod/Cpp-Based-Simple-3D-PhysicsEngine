#include"main.h"
#include<Windows.h>

float deltaTime = 0.0f;
float lastFrame = 0.0f;

float lastX = 400, lastY = 300;

bool firstMouse = true;
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

//prepare physics
SimplePhysicsEngine::PhysicsEngine pEngine;

Shader* defaultShader;

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//OpenGL 3.3 버전을 사용한다는 의미
	//       _ => Major
	//         - => Minor
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//OpenGL Core_Profile 모드를 이용하여 개발	

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create window\n";
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "failed to initialize GLAD\n";
		return -1;
	}

	//initialize glfw window options
	glViewport(0, 0, 800, 600);
	glEnable(GL_DEPTH_TEST);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	//compile shader
	Shader ourShader(vertexShaderPath, fragmentShaderPath);
	Shader lightShader(vertexShaderPath, lampFragmentShaderPath);

	defaultShader = &ourShader;

	glm::vec3 lightPos(-30.0f, 30.0f, -30.0f);
	ourShader.use();	
	ourShader.SetVec3("light.lightColor", 1.0f, 1.0f, 1.0f);
	ourShader.SetVec3("light.lightPos", lightPos.x, lightPos.y, lightPos.z);

	pEngine.RunPhysicsThread();
	//add light
	SimplePhysicsEngine::Transform* transform = new SimplePhysicsEngine::Transform(lightPos);
	SimplePhysicsEngine::RigidBody* rigidBody = new SimplePhysicsEngine::RigidBody(10.0f, 0.0f, zero, zero, true);
	SimplePhysicsEngine::Material* material = new SimplePhysicsEngine::Material(&lightShader);
	AddSphereToPhysicsWorld(transform, rigidBody, material, 1.0f, 36, 18);

	//add plane(ground)
	//transform = new SimplePhysicsEngine::Transform(glm::vec3(0,-30.0f, 0));
	glm::vec3 eulerAngles = glm::vec3(glm::radians(-10.0f), glm::radians(-5.0f), glm::radians(-1.0f));
	transform = new SimplePhysicsEngine::Transform(glm::vec3(0, -30.0f, 0), glm::quat(eulerAngles));
	rigidBody = new SimplePhysicsEngine::RigidBody(10.0f, 0.0f, zero, zero, true);
	material = new SimplePhysicsEngine::Material(defaultShader, glm::vec4(0.7f, 0.7f, 0.7f,1));
	AddPlaneToPhyscisWorld(transform, rigidBody, material, 100.0f, 100.0f, 30.0f);
		
	//rendering loop
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		ProcessInput(window);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT); //Clear

		//Camera Setting
		float radius = 20.0f;
		float camX = sin(glfwGetTime()) * radius;
		float camZ = cos(glfwGetTime()) * radius;
		
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 projection = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -30.0f));
		projection = glm::perspective(glm::radians(camera.Zoom), (float)800 / 600, 0.001f, 100000.0f);
		//Camera Setting

		//Objects
		auto objects = pEngine.GetLatestBuffer();
		for (SimplePhysicsEngine::Object* obj : objects)
		{
			obj->Draw(camera.Position, view, projection);			
		}
		//Objects

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
	
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{	
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		SimplePhysicsEngine::Transform* transform1 = new SimplePhysicsEngine::Transform();
		SimplePhysicsEngine::RigidBody* rigidBody1 = new SimplePhysicsEngine::RigidBody();
		SimplePhysicsEngine::Material* material1 = new SimplePhysicsEngine::Material(defaultShader, glm::vec4(0.8f, 0.1f, 0.1f,1.0f));
		//rigidBody1->velocity = glm::vec3(0.0f, 0.0f, 0.0f);
		//rigidBody1->mass = 25.0f;
		rigidBody1->velocity = glm::vec3(2.5f, 5.0f, 2.5f);
		AddSphereToPhysicsWorld(transform1, rigidBody1, material1, 1.5f, 36, 18);
		
		SimplePhysicsEngine::Transform* transform2 = new SimplePhysicsEngine::Transform();
		transform2->position = glm::vec3(5.0f, 0.0f, 5.0f);
		SimplePhysicsEngine::RigidBody* rigidBody2 = new SimplePhysicsEngine::RigidBody();
		SimplePhysicsEngine::Material* material2 = new SimplePhysicsEngine::Material(defaultShader, glm::vec4(0.1f, 0.1f, 0.8f, 1.0f));		
		rigidBody2->velocity = glm::vec3(-2.5f, 5.0f, -2.5f);
		AddSphereToPhysicsWorld(transform2, rigidBody2, material2, 1.5f, 36, 18);
	}
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // y 좌표의 범위는 밑에서부터 위로가기 때문에 반대로 바꿉니다.
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.3f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height); //창 크기가 변경되면 viewport를 창 크기에 맞춤	
}

void ProcessInput(GLFWwindow* window)
{
	float cameraSpeed = 2.5f * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void AddSphereToPhysicsWorld(SimplePhysicsEngine::Transform* transform, SimplePhysicsEngine::RigidBody* rigidBody, SimplePhysicsEngine::Material* material, float radius, int sectorCount, int stackCount)
{
	SimplePhysicsEngine::Sphere* newSphere = new SimplePhysicsEngine::Sphere(transform, rigidBody, material, radius, sectorCount, stackCount);
	pEngine.AddObject(newSphere);
}

void AddPlaneToPhyscisWorld(SimplePhysicsEngine::Transform* transform, SimplePhysicsEngine::RigidBody* rigidBody, SimplePhysicsEngine::Material* material, float width, float height, float thickness)
{
	SimplePhysicsEngine::Plane* newPlane = new SimplePhysicsEngine::Plane(transform, rigidBody, material, width, height, thickness);
	pEngine.AddObject(newPlane);
}