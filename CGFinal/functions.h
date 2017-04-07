#pragma once
// Function prototypes



// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>


#include  "shader.hpp"
#include "Model.hpp"



// Animation:
void do_animation();
/**
 key press function
*/
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

/**
 scroll function
*/
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

/**
 mouse callback
*/
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

/**
 roate, move etc
*/
void do_movement();

/**
Default danimation start
*/
glm::mat4 do_default_animation(glm::mat4 model, float part_x, float part_y, float part_z, int id);

/**
select what operation to do
*/
glm::mat4 select_transformation(glm::mat4 model, float part_x, float part_y, float part_z, int id);

/**

draw all models

*/
glm::mat4 draw_all_models(glm::mat4 model, Shader shader, Model model_torso, Model model_limb, Model model_leg, Model model_arm, Model model_head);

/**
print instructions
*/
void print_help();