#pragma once
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
extern Camera camera;
extern bool keys[1024];

extern GLfloat lastX , lastY;
extern bool firstMouse;

extern GLfloat deltaTime;
extern GLfloat lastFrame;

// Rotation:
extern float rotation_speed ;
extern void rotate_parts();

extern float rLeg_left1_x;
extern float rLeg_left1_y ;
extern float rLeg_left1_z;

extern float rLeg_right1_x;
extern float rLeg_right1_y;
extern float rLeg_right1_z;

extern float rLeg_left2_x;
extern float rLeg_left2_y;
extern float rLeg_left2_z;

extern float rLeg_right2_x;
extern float rLeg_right2_y;
extern float rLeg_right2_z ;

extern float rArm_right1_x;
extern float rArm_right1_y;
extern float rArm_right1_z;

extern float rArm_left1_x;
extern float rArm_left1_y;
extern float rArm_left1_z;

extern float rArm_right2_x;
extern float rArm_right2_y;
extern float rArm_right2_z;

extern float rArm_left2_x;
extern float rArm_left2_y;
extern float rArm_left2_z;

extern float rTorso_x;
extern float rTorso_y;
extern float rTorso_z;

extern float rHead_x;
extern float rHead_y;
extern float rHead_z;


extern bool mode_1;
extern bool mode_2;
extern bool mode_3;
extern bool mode_4;

extern int first_animation_time;

// Modes:

extern glm::mat4 snapshot_buffer[100];
extern int snapshot_counter;
extern bool first_loop;

// Properties
extern GLuint screenWidth, screenHeight;