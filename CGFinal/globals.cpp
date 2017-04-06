#pragma once
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GL includes
#include "Shader.hpp"
#include "Camera.hpp"
#include "Model.hpp"

// GLM Mathemtics
// Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

bool keys[1024];
GLfloat lastX = 800, lastY = 600;
bool firstMouse = true;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

// Rotation:
float rotation_speed = 5.0f;
void rotate_parts();

float rLeg_left1_x = 0.0f;
float rLeg_left1_y = 0.0f;
float rLeg_left1_z = 0.0f;

float rLeg_right1_x = 0.0f;
float rLeg_right1_y = 0.0f;
float rLeg_right1_z = 0.0f;

float rLeg_left2_x = 0.0f;
float rLeg_left2_y = 0.0f;
float rLeg_left2_z = 0.0f;

float rLeg_right2_x = 0.0f;
float rLeg_right2_y = 0.0f;
float rLeg_right2_z = 0.0f;

float rArm_right1_x = 0.0f;
float rArm_right1_y = 0.0f;
float rArm_right1_z = 0.0f;

float rArm_left1_x = 0.0f;
float rArm_left1_y = 0.0f;
float rArm_left1_z = 0.0f;

float rArm_right2_x = 0.0f;
float rArm_right2_y = 0.0f;
float rArm_right2_z = 0.0f;

float rArm_left2_x = 0.0f;
float rArm_left2_y = 0.0f;
float rArm_left2_z = 0.0f;

float rTorso_x = 0.0f;
float rTorso_y = 0.0f;
float rTorso_z = 0.0f;

float rHead_x = 0.0f;
float rHead_y = 0.0f;
float rHead_z = 0.0f;

// Animation:
void do_animation();
bool mode_1 = false;
bool mode_2 = false;
bool mode_3 = false;
bool mode_4 = false;

int first_animation_time = 5;

// Modes:

glm::mat4 snapshot_buffer[100];
int snapshot_counter = 0;
bool first_loop = true;

// Properties
GLuint screenWidth = 1000, screenHeight = 800;