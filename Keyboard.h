/*############################################################################
##																			##
##	Keyboard																##
##																			##
##	Holds keyboard values and sets globals directly or can be polled		##
##	by objects																##
##																			##
##	Author:		Justin Bentley										 ##  ## ##
##	Date:		12/2018	- 03/19										##  ##  ##
##	Version:	1.0												   ######   ##
##																# ##  ##    ##
#############################################################################*/

#ifndef Keyboard
#define Keyboard

struct keyboard {
	bool w = false;
	bool s = false;
	bool a = false;
	bool d = false;
	bool r = false;
	bool f = false;
	bool q = false;
	bool e = false;
	bool t = false;
	bool g = false;
	bool z = false;
	bool x = false;
	bool c = false;
	bool v = false;
	//end kb movement and look
	bool n = false;
	bool m = false;

	bool p = true; // vsync
	bool o = false; // fps_readout
} kb;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS) {
		switch (key)
		{
		case GLFW_KEY_1: { state = 1; InstaciateChildP(); break; }
		case GLFW_KEY_2: { state = 2; InstaciateChildP(); break; }
		case GLFW_KEY_ESCAPE: { glfwSetWindowShouldClose(window, GLFW_TRUE); break; }
		case GLFW_KEY_W: { kb.w = true; break; }
		case GLFW_KEY_S: { kb.s = true; break; }
		case GLFW_KEY_A: { kb.a = true; break; }
		case GLFW_KEY_D: { kb.d = true; break; }
		case GLFW_KEY_R: { kb.r = true; break; }
		case GLFW_KEY_F: { kb.f = true; break; }
		case GLFW_KEY_Q: { kb.q = true; break; }
		case GLFW_KEY_E: { kb.e = true; break; }
		case GLFW_KEY_T: { kb.t = true; break; }
		case GLFW_KEY_G: { kb.g = true; break; }
		case GLFW_KEY_Z: { kb.z = true; break; }
		case GLFW_KEY_X: { kb.x = true; break; }
		case GLFW_KEY_C: { kb.c = true; break; }
		case GLFW_KEY_V: { kb.v = true; break; }
		//end kb movement and look
		case GLFW_KEY_N: { kb.n = true; break; }
		case GLFW_KEY_M: { kb.m = true; break; }
		default: { break; }
		}
	}
	if (action == GLFW_RELEASE) {
		switch (key)
		{
		case GLFW_KEY_W: { kb.w = false; break; }
		case GLFW_KEY_S: { kb.s = false; break; }
		case GLFW_KEY_A: { kb.a = false; break; }
		case GLFW_KEY_D: { kb.d = false; break; }
		case GLFW_KEY_R: { kb.r = false; break; }
		case GLFW_KEY_F: { kb.f = false; break; }
		case GLFW_KEY_Q: { kb.q = false; break; }
		case GLFW_KEY_E: { kb.e = false; break; }
		case GLFW_KEY_T: { kb.t = false; break; }
		case GLFW_KEY_G: { kb.g = false; break; }
		case GLFW_KEY_Z: { kb.z = false; break; }
		case GLFW_KEY_X: { kb.x = false; break; }
		case GLFW_KEY_C: { kb.c = false; break; }
		case GLFW_KEY_V: { kb.v = false; break; }
		//end kb movement and look
		case GLFW_KEY_N: { kb.n = false; break; }
		case GLFW_KEY_M: { kb.m = false; break; }

		case GLFW_KEY_P: { kb.p = !kb.p; break; }	//vsync
		case GLFW_KEY_O: { kb.o = !kb.o; break; }	//fps readout

		default: { break; }
		}
	}
}
void MovePlayer() {

	GLfloat movespeed = 0.1f;
	GLfloat turnspeed = 0.033f;
	//Quaternian and Matrix based, Negative Z forward

	glm::quat q = glm::angleAxis(0.0f, glm::vec3(0, 1, 0));;
	glm::quat y = glm::angleAxis(0.0f, glm::vec3(0, 1, 0));;

	//********************MOVEMENT_TRANSFORMS***********************************
	if (kb.w == true) { eyepos += frontvector *  movespeed; }	//move up
	if (kb.s == true) { eyepos -= frontvector *  movespeed; }	//move down
	if (kb.a == true) { q = glm::angleAxis(turnspeed, glm::vec3(0, 1, 0));/* frontvector = y * frontvector; */}//turn left (yaw)
	if (kb.d == true) { q = glm::angleAxis(-turnspeed, glm::vec3(0, 1, 0)); /*frontvector = y * frontvector; */}//turn right (yaw)
	if (kb.q == true) { eyepos -= glm::normalize(glm::cross(frontvector, flatupvec)) * movespeed; }	//strafe left
	if (kb.e == true) { eyepos += glm::normalize(glm::cross(frontvector, flatupvec)) * movespeed; }	//strafe right
	if (kb.t == true) { eyepos += flatupvec * movespeed; }	//move up
	if (kb.g == true) { eyepos -= flatupvec * movespeed; }	//move down

//	frontvector = q * frontvector;

	if (kb.r == true && frontvector.y <  0.99f) { y = glm::angleAxis(turnspeed, glm::vec3(glm::normalize(glm::cross(frontvector, flatupvec)))); }/*frontvector = q * frontvector;*/	//pitch up
	if (kb.f == true && frontvector.y > -0.99f) { y = glm::angleAxis(-turnspeed, glm::vec3(glm::normalize(glm::cross(frontvector, flatupvec)))); }/* frontvector = q * frontvector;*///pitch down

//	y = y * q;

	frontvector = y * q *frontvector;
	if (frontvector.y < -9) { frontvector.y = -0.9f; }


//	glm::mat4 rotation = glm::toMat4(glm::normalize(q * y));

	//glm::quat r = y * q;
	//r = glm::normalize(r);
	//glm::vec3

	//q = glm::rotate(glm::mat4(1.0f), glm::radians(7), glm::vec3(0, 1, 0));

	//frontvector *= q;



	//if (kb.w == true) { eyepos += frontvector *  movespeed; }	//move up
	//if (kb.s == true) { eyepos -= frontvector *  movespeed; }	//move down
	//if (kb.a == true) { glm::quat y = glm::angleAxis(turnspeed, glm::vec3(0, 1, 0)); frontvector = y * frontvector; }//turn left (yaw)
	//if (kb.d == true) { glm::quat y = glm::angleAxis(-turnspeed, glm::vec3(0, 1, 0)); frontvector = y * frontvector; }//turn right (yaw)
	//if (kb.q == true) { eyepos -= glm::normalize(glm::cross(frontvector, flatupvec)) * movespeed; }	//strafe left
	//if (kb.e == true) { eyepos += glm::normalize(glm::cross(frontvector, flatupvec)) * movespeed; }	//strafe right
	//if (kb.r == true) { eyepos += flatupvec * movespeed; }	//move up
	//if (kb.f == true) { eyepos -= flatupvec * movespeed; }	//move down
	//if (kb.t == true) { glm::quat q = glm::angleAxis(turnspeed, glm::vec3(1, 0, 0)); frontvector = q * frontvector; }	//pitch up
	//if (kb.g == true) { glm::quat q = glm::angleAxis(-turnspeed, glm::vec3(1, 0, 0)); frontvector = q * frontvector; }//pitch down




	//********************ROTATIONS_EYEPOINT************************************


	if (kb.z == true) { glm::quat q = glm::angleAxis(-turnspeed, glm::vec3(0, 0, 1)); upvec = q * upvec; }	//roll left
	if (kb.x == true) { glm::quat q = glm::angleAxis(turnspeed, glm::vec3(0, 0, 1)); upvec = q * upvec; }	//roll right
	if (kb.c == true) { glm::quat q = glm::angleAxis(turnspeed, glm::vec3(0, 1, 0)); lookvector = q * lookvector; }	//yaw left
	if (kb.v == true) { glm::quat q = glm::angleAxis(-turnspeed, glm::vec3(0, 1, 0)); lookvector = q * lookvector; }//yaw right

	viewmatrix = glm::lookAt( eyepos, eyepos + frontvector/* + lookvector*/, upvec);
	projectionmatrix = glm::perspective(45.0f, 1.8f, 0.1f, 700.0f);	//curently redundant
//	projectionmatrix = glm::perspective(45.0f, (GLfloat)(WINWIDTH / WINHEIGHT), 0.0001f, 5000.0f);

	//********************TESTING_KEYS**************************************
	//if (kb.n == true) { pushback += 0.05f; }
	//if (kb.m == true) { pushback -= 0.05f; }





//	viewmatrix = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	//	viewmatrix = glm::rotate(glm::mat4(), yaw, glm::vec3(0, 1, 0));
	//	glm::mat4 viewmatrixeye = glm::rotate(glm::mat4(), yaw, glm::vec3(0, 1, 0));

	

	//glm::mat3 urmom = glm::rotate(glm::mat3(), yaw, glm::vec3(0, 1, 0));
	//	projectionmatrix = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -0.001f, 500.0f);//ortho may imply 0 fov angle //this is 2D

}


#endif
