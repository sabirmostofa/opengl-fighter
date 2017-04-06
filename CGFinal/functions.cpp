
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>




// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "globals.h"




glm::mat4 do_default_animation(glm::mat4 model, float part_x, float part_y, float part_z, int id) {

	float angle = 0.0;


	switch (id)
	{
	case 1: // Torso

		angle = sin((GLfloat)glfwGetTime()) * 40.0f;
		cout << "doing animation default" << "  ID: " << angle << endl;
		if (angle > 0)
			model = glm::rotate(model, angle, glm::vec3(1.0f, 0.0f, 0.0f));
		else
			model = glm::rotate(model, 0.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		break;
		//case 2: // Right Upper Leg
		//	angle = sin((GLfloat)glfwGetTime()) * 80.0f;
		//	if (angle < 50)
		//		model = glm::rotate(model, angle, glm::vec3(1.0f, 0.0f, 0.0f));
		//	else
		//		model = glm::rotate(model, 50.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		//	break;
		//case 3: // Right Lower Leg
		//	angle = sin((GLfloat)glfwGetTime()) * -80.0f;
		//	if (angle > 0)
		//		model = glm::rotate(model, angle, glm::vec3(1.0f, 0.0f, 0.0f));
		//	break;
		//case 4: // Left Upper Leg
		//	angle = sin((GLfloat)glfwGetTime()) * 80.0f;
		//	if (angle < 50)
		//		model = glm::rotate(model, angle, glm::vec3(1.0f, 0.0f, 0.0f));
		//	else
		//		model = glm::rotate(model, 50.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		//	break;
		//case 5: // Left Lower Leg
		//	angle = sin((GLfloat)glfwGetTime()) * -80.0f;
		//	if (angle > 0)
		//		model = glm::rotate(model, angle, glm::vec3(1.0f, 0.0f, 0.0f));
		//	break;
	case 6: // Right Upper Arm
		angle = sin((GLfloat)glfwGetTime()) * 80.0f;
		if (angle < 50)
			model = glm::rotate(model, angle, glm::vec3(1.0f, 0.0f, 1.0f));
		else
			model = glm::rotate(model, 50.0f, glm::vec3(1.0f, 0.0f, 1.0f));
		break;
	case 7: // Right Lower Arm
		angle = sin((GLfloat)glfwGetTime()) * -300.0f;
		if (angle > 0)
			model = glm::rotate(model, angle, glm::vec3(1.0f, 0.0f, 0.0f));
		break;
	case 8: // Left Upper Arm
		angle = -sin((GLfloat)glfwGetTime()) * -80.0f;
		model = glm::rotate(model, 180.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		if (angle < 50)
			model = glm::rotate(model, angle, glm::vec3(0.0f, 1.0f, 1.0f));
		else
			model = glm::rotate(model, 50.0f, glm::vec3(0.0f, 1.0f, 1.0f));
		break;
	case 9: // Left Lower Arm
		angle = -sin((GLfloat)glfwGetTime()) * 80.0f;
		if (angle > 0)
			model = glm::rotate(model, angle, glm::vec3(1.0f, 0.0f, 1.0f));
		break;
	case 10: // Head
		angle = sin((GLfloat)glfwGetTime()) * -80.0f;
		if (angle > -20)
			model = glm::rotate(model, 0.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		else
			model = glm::rotate(model, angle, glm::vec3(1.0f, 0.0f, 0.0f));
		break;
	default:
		break;

	}
	return model;

}


// Moves/alters the camera positions based on user input
void do_movement()
{
	// Camera controls
	if (keys[GLFW_KEY_UP])
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (keys[GLFW_KEY_DOWN])
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (keys[GLFW_KEY_LEFT])
		camera.ProcessKeyboard(RIGHT, deltaTime);
	if (keys[GLFW_KEY_RIGHT])
		camera.ProcessKeyboard(LEFT, deltaTime);
}

glm::mat4 select_transformation(glm::mat4 model, float part_x, float part_y, float part_z, int id)
{
	if (glfwGetTime() >1 && glfwGetTime() < 10 && first_loop == false) {

		model = do_default_animation(model, part_x, part_y, part_z, id);

		return model;
	}

	if (mode_1) // Keyboard mode:
	{
		model = glm::rotate(model, part_x, glm::vec3(1.0f, 0.0f, 0.0));
		model = glm::rotate(model, part_y, glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::rotate(model, part_z, glm::vec3(0.0f, 0.0f, 1.0));
	}

	if (mode_2) // take snapshot:
	{

		model = glm::rotate(model, part_x, glm::vec3(1.0f, 0.0f, 0.0));
		model = glm::rotate(model, part_y, glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::rotate(model, part_z, glm::vec3(0.0f, 0.0f, 1.0));
		snapshot_buffer[snapshot_counter] = model;
		std::cout << snapshot_counter;
		++snapshot_counter;


		if (snapshot_counter == 99) // Only save a couple of snapshots.
			snapshot_counter = 0;

		if (id == 10)
			mode_2 = false;
	}

	if (mode_3) // play snapshots:
	{
		if (snapshot_counter == 99) // play snapshots in loop
			snapshot_counter = 0;

		model = snapshot_buffer[snapshot_counter];
	}

	if (mode_4) // predefined animation:
	{
		snapshot_counter = 0;
		float angle = 0.0;

		switch (id)
		{
		case 1: // Torso
			angle = sin((GLfloat)glfwGetTime()) * 40.0f;
			if (angle > 0)
				model = glm::rotate(model, angle, glm::vec3(1.0f, 0.0f, 0.0f));
			else
				model = glm::rotate(model, 0.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			break;
		case 2: // Right Upper Leg
			angle = sin((GLfloat)glfwGetTime()) * 80.0f;
			if (angle < 50)
				model = glm::rotate(model, angle, glm::vec3(1.0f, 0.0f, 0.0f));
			else
				model = glm::rotate(model, 50.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			break;
		case 3: // Right Lower Leg
			angle = sin((GLfloat)glfwGetTime()) * -80.0f;
			if (angle > 0)
				model = glm::rotate(model, angle, glm::vec3(1.0f, 0.0f, 0.0f));
			break;
		case 4: // Left Upper Leg
			angle = sin((GLfloat)glfwGetTime()) * 80.0f;
			if (angle < 50)
				model = glm::rotate(model, angle, glm::vec3(1.0f, 0.0f, 0.0f));
			else
				model = glm::rotate(model, 50.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			break;
		case 5: // Left Lower Leg
			angle = sin((GLfloat)glfwGetTime()) * -80.0f;
			if (angle > 0)
				model = glm::rotate(model, angle, glm::vec3(1.0f, 0.0f, 0.0f));
			break;
		case 6: // Right Upper Arm
			angle = sin((GLfloat)glfwGetTime()) * 80.0f;
			if (angle < 50)
				model = glm::rotate(model, angle, glm::vec3(0.0f, 1.0f, 1.0f));
			else
				model = glm::rotate(model, 50.0f, glm::vec3(0.0f, 1.0f, 1.0f));
			break;
		case 7: // Right Lower Arm
			angle = sin((GLfloat)glfwGetTime()) * -80.0f;
			if (angle > 0)
				model = glm::rotate(model, angle, glm::vec3(1.0f, 0.0f, 1.0f));
			break;
		case 8: // Left Upper Arm
			angle = -sin((GLfloat)glfwGetTime()) * -80.0f;
			model = glm::rotate(model, 180.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			if (angle < 50)
				model = glm::rotate(model, angle, glm::vec3(0.0f, 1.0f, 1.0f));
			else
				model = glm::rotate(model, 50.0f, glm::vec3(0.0f, 1.0f, 1.0f));
			break;
		case 9: // Left Lower Arm
			angle = -sin((GLfloat)glfwGetTime()) * 80.0f;
			if (angle > 0)
				model = glm::rotate(model, angle, glm::vec3(1.0f, 0.0f, 1.0f));
			break;
		case 10: // Head
			angle = sin((GLfloat)glfwGetTime()) * -80.0f;
			if (angle > -20)
				model = glm::rotate(model, angle, glm::vec3(1.0f, 0.0f, 0.0f));
			else
				model = glm::rotate(model, -20.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			break;
		default:
			break;

		}
	}
	return model;
}

void rotate_parts()
{
	// Torso:
	if (keys[GLFW_KEY_J])
		rTorso_x += rotation_speed;
	if (keys[GLFW_KEY_K])
		rTorso_y += rotation_speed;
	if (keys[GLFW_KEY_L])
		rTorso_z += rotation_speed;

	// Left Leg1 (Left Lower Leg):
	if (keys[GLFW_KEY_Z])
		rLeg_left1_x += rotation_speed;
	if (keys[GLFW_KEY_X])
		rLeg_left1_y += rotation_speed;
	if (keys[GLFW_KEY_C])
		rLeg_left1_z += rotation_speed;

	// Left Leg2 (Left Upper Leg):
	if (keys[GLFW_KEY_A])
		rLeg_left2_x += rotation_speed;
	if (keys[GLFW_KEY_S])
		rLeg_left2_y += rotation_speed;
	if (keys[GLFW_KEY_D])
		rLeg_left2_z += rotation_speed;

	// Right Leg1 (Right Upper Leg):
	if (keys[GLFW_KEY_V])
		rLeg_right1_x += rotation_speed;
	if (keys[GLFW_KEY_B])
		rLeg_right1_y += rotation_speed;
	if (keys[GLFW_KEY_N])
		rLeg_right1_z += rotation_speed;

	// Right Leg2 (Right Lower Leg):
	if (keys[GLFW_KEY_F])
		rLeg_right2_x += rotation_speed;
	if (keys[GLFW_KEY_G])
		rLeg_right2_y += rotation_speed;
	if (keys[GLFW_KEY_H])
		rLeg_right2_z += rotation_speed;

	// Left Arm1 (Left Upper Arm):
	if (keys[GLFW_KEY_Q])
		rArm_left1_x += rotation_speed;
	if (keys[GLFW_KEY_W])
		rArm_left1_y += rotation_speed;
	if (keys[GLFW_KEY_E])
		rArm_left1_z += rotation_speed;

	// Left Arm2 (Left Lower Arm):
	if (keys[GLFW_KEY_1])
		rArm_left2_x += rotation_speed;
	if (keys[GLFW_KEY_2])
		rArm_left2_y += rotation_speed;
	if (keys[GLFW_KEY_3])
		rArm_left2_z += rotation_speed;

	// Right Arm1 (Right Upper Arm):
	if (keys[GLFW_KEY_R])
		rArm_right1_x += rotation_speed;
	if (keys[GLFW_KEY_T])
		rArm_right1_y += rotation_speed;
	if (keys[GLFW_KEY_Y])
		rArm_right1_z += rotation_speed;

	// Right Arm2 (Right Lower Arm):
	if (keys[GLFW_KEY_4])
		rArm_right2_x += rotation_speed;
	if (keys[GLFW_KEY_5])
		rArm_right2_y += rotation_speed;
	if (keys[GLFW_KEY_6])
		rArm_right2_z += rotation_speed;

	// Head:
	if (keys[GLFW_KEY_U])
		rHead_x += rotation_speed;
	if (keys[GLFW_KEY_I])
		rHead_y += rotation_speed;
	if (keys[GLFW_KEY_O])
		rHead_z += rotation_speed;
}

void do_animation()
{
	if (keys[GLFW_KEY_7])
	{
		mode_1 = true;
		mode_2 = false;
		mode_3 = false;
		mode_4 = false;
	}



	if (keys[GLFW_KEY_9])
	{
		mode_1 = false;
		mode_2 = false;
		mode_3 = true;
		mode_4 = false;
	}

	if (keys[GLFW_KEY_0])
	{
		mode_1 = false;
		mode_2 = false;
		mode_3 = false;
		mode_4 = true;
	}
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (glfwGetTime() < first_animation_time) return;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	switch (key)
	{
	case GLFW_KEY_8:
		if (mode_1 == true)
		{
			mode_1 = false;
			mode_2 = true;
			mode_3 = false;
			mode_4 = false;
		}
		break;

	default:
		break;
	}

	if (action == GLFW_PRESS)
		keys[key] = true;
	else if (action == GLFW_RELEASE)
		keys[key] = false;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (glfwGetTime() < first_animation_time) return;
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (glfwGetTime() < first_animation_time) return;
	camera.ProcessMouseScroll(yoffset);
}





glm::mat4 draw_all_models(glm::mat4 model, Shader shader, Model model_torso, Model model_limb, Model model_leg, Model model_arm, Model model_head) {
	glm::mat4 model_save;
	// Draw Torso:
	model = select_transformation(model, rTorso_x, rTorso_y, rTorso_z, 1);
	glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
	model_torso.Draw(shader);
	model_save = model;

	// Draw right Leg2:
	model = glm::translate(model, glm::vec3(0.2f, 0.0f, 0.0f));
	model = select_transformation(model, rLeg_right2_x, rLeg_right2_y, rLeg_right2_z, 2);
	model = glm::rotate(model, -90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
	model_limb.Draw(shader);
	model = glm::rotate(model, 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));

	// Draw right Leg1:
	model = glm::translate(model, glm::vec3(-0.02f, -0.7f, 0.0f));
	model = select_transformation(model, rLeg_right1_x, rLeg_right1_y, rLeg_right1_z, 3);
	glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
	model_leg.Draw(shader);
	model = model_save;

	// Draw left Leg2:
	model = glm::translate(model, glm::vec3(-0.2f, 0.0f, 0.0f));
	model = select_transformation(model, rLeg_left2_x, rLeg_left2_y, rLeg_left2_z, 4);
	model = glm::rotate(model, -90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
	model_limb.Draw(shader);
	model = glm::rotate(model, 90.0f, glm::vec3(0.0f, 0.0f, 1.0f));

	// Draw left Leg1:
	model = glm::translate(model, glm::vec3(-0.02f, -0.7f, 0.0f));
	model = select_transformation(model, rLeg_left1_x, rLeg_left1_y, rLeg_left1_z, 5);
	glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
	model_leg.Draw(shader);
	model = model_save;

	// Draw right Arm1:
	model = glm::translate(model, glm::vec3(0.45f, 1.05f, 0.0f));
	model = select_transformation(model, rArm_right1_x, rArm_right1_y, rArm_right1_z, 6);
	glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
	model_limb.Draw(shader);

	// Draw right Arm1:
	model = glm::translate(model, glm::vec3(0.7f, -0.01f, 0.01f));
	model = select_transformation(model, rArm_right2_x, rArm_right2_y, rArm_right2_z, 7);
	glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
	model_arm.Draw(shader);
	model = model_save;

	// Draw left Arm2:
	model = glm::translate(model, glm::vec3(-0.45f, 1.013f, 0.0f));
	model = select_transformation(model, rArm_left1_x, rArm_left1_y, rArm_left1_z, 8);
	model = glm::rotate(model, 180.0f, glm::vec3(0.0f, 0.0f, 1.0));
	glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
	model_limb.Draw(shader);
	model = glm::rotate(model, -180.0f, glm::vec3(0.0f, 0.0f, 1.0));

	// Draw left Arm2:
	model = glm::translate(model, glm::vec3(-0.7f, 0.01f, -0.01f));
	model = select_transformation(model, rArm_left2_x, rArm_left2_y, rArm_left2_z, 9);
	model = glm::rotate(model, 180.0f, glm::vec3(0.0f, 0.0f, 1.0));
	glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
	model_arm.Draw(shader);
	model = model_save;

	// Draw Head:
	model = glm::translate(model, glm::vec3(0.0f, 1.1f, 0.0f));
	model = select_transformation(model, rHead_x, rHead_y, rHead_z, 10);
	glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
	model_head.Draw(shader);

	return model;
}