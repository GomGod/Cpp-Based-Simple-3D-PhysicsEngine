#pragma once
#ifndef SIMPLEPHYSICSENGINE_MAIN_H
#define SIMPLEPHYSICSENGINE_MAIN_H
#define STB_IMAGE_IMPLEMENTATION
#include "stb-master/stb_image.h"

#include <thread>
#include <iostream>
#include <vector>
#include "glad/glad.h"		
#include "GLFW/glfw3.h" 
#include "PhysicsEngine.h"
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"
#include "Objects.h"
#include <list>
#include "Rigidbody.h"


//GLFW
void ProcessInput(GLFWwindow* window);
void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
//callbacks
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
//GLFW

//PhysicsEngine
void AddPlaneToPhyscisWorld(SimplePhysicsEngine::Transform* transform, SimplePhysicsEngine::RigidBody* rigidBody, SimplePhysicsEngine::Material* material, float width, float height, float thickness);
void AddSphereToPhysicsWorld(SimplePhysicsEngine::Transform* transform, SimplePhysicsEngine::RigidBody* rigidBody, SimplePhysicsEngine::Material* material, float radius, int sectorCount, int stackCount);
glm::vec3 zero(0, 0, 0);

const char* vertexShaderPath = "vertexShader.vs";
const char* fragmentShaderPath = "fragmentShader.fs";
const char* lampFragmentShaderPath = "lampFragmentShader.fs";

using namespace std;

#endif //SIMPLEPHYSICSENGINE_MAIN_H
