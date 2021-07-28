#pragma once
#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>



#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include <iostream>
#include "glm/gtx/matrix_transform_2d.hpp"
#include <thread>
#include <vector>
#include "glm/vec3.hpp"
#include "glm/vec2.hpp"
#include "glm/glm.hpp"
#include <array>
#include <vector>
#include <iostream>
#include "MaterialFactory.h"
#include "Mesh.h"
#include "MeshRenderer.h"
#include <GL/glew.h>
#include "Block.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Camera.h"
#include "CameraController.h"
#include "Keyboard.h"
#include "Time.h"
#include "Chunk.h"
#include "StandardBlock.h"
#include "ChunkRenderer.h"
#include "World.h"
#include "WorldRenderer.h"
#include "Player.h"
#include "Mouse.h"
#include "MainPlayerController.h"
#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main1(int argc, char* argv[])
{
	try
	{
		if (argc != 2)
		{
			std::cerr << "Usage: client <host>" << std::endl;
			return 1;
		}

		boost::asio::io_service io_service;

		tcp::resolver resolver(io_service);
		tcp::resolver::query query(argv[1], "daytime");
		tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
		tcp::resolver::iterator end;

		tcp::socket socket(io_service);
		boost::system::error_code error = boost::asio::error::host_not_found;
		while (error && endpoint_iterator != end)
		{
			socket.close();
			socket.connect(*endpoint_iterator++, error);
		}
		if (error)
			throw boost::system::system_error(error);

		for (;;)
		{
			boost::array<char, 128> buf;
			boost::system::error_code error;

			size_t len = socket.read_some(boost::asio::buffer(buf), error);

			if (error == boost::asio::error::eof)
				break; // Connection closed cleanly by peer.
			else if (error)
				throw boost::system::system_error(error); // Some other error.

			std::cout.write(buf.data(), len);
		}
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}

auto shapes = std::vector<std::unique_ptr<sf::Shape>>();



void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}


void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	mouse.xoffset = xpos - mouse.lastX;
	mouse.yoffset = mouse.lastY - ypos; // reversed since y-coordinates range from bottom to top
	mouse.lastX = xpos;
	mouse.lastY = ypos;
}






void key_callback(GLFWwindow* window, int keyCode, int scancode, int action, int mods)
{
	auto& key = keys[keyCode];
	if (action == GLFW_PRESS) {
		key.pressed = true;
		key.released = false;
		key.heldDown = true;
	}
		
	if (action == GLFW_RELEASE) {
		key.pressed = false;
		key.released = true;
		key.heldDown = false;
	}
}


int main()
{
	glfwInit();


	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);



	glewInit();

	glViewport(0, 0, 800, 800);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetKeyCallback(window, key_callback);

	
	auto camera = std::make_shared<Camera>(glm::vec3(0.2, 4.5, 0.5));
	materialFactory.setCamera(camera);	
	
	auto worldGenerator = std::make_shared<WorldGenerator>();

	auto chunkLoader = std::make_shared<ChunkLoader>(worldGenerator);

	auto world = std::make_shared<World>(chunkLoader);
	



	auto player = std::make_shared<Player>(world, glm::vec3(0.2,4.5,0.5));
	MainPlayerController mainPlayer = MainPlayerController(player, camera);



	while (!glfwWindowShouldClose(window))
	{
		
		mainTime.update();
		glfwPollEvents();
		player->update();
		mainPlayer.update();
		
		glfwSwapBuffers(window);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		mouse.xoffset = mouse.yoffset = 0;
	}


	

	
	

	glfwTerminate();
	return 0;
}
