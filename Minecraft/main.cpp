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
#include "tcp_connection.h"
#include "RemoteChunkLoader.h"

#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include "MAIN.H"
#include "StreamWorldFromServer.h"
#include <RemotePlayer.h>
#include "ConnectMessage.h"
#include "Entity.h"

using boost::asio::ip::tcp;




std::shared_ptr<tcp_connection> connectToServer(const std::string& ip, boost::asio::io_service& io_service)
{
	std::shared_ptr<tcp_connection> connection;
	try
	{
		tcp::resolver resolver(io_service);
		tcp::resolver::query query(ip.c_str(), "6767");
		tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
		tcp::resolver::iterator end;

		connection = tcp_connection::create(io_service);
		auto& socket = connection->socket();

		boost::system::error_code error = boost::asio::error::host_not_found;
		while (error && endpoint_iterator != end)
		{
			socket.close();
			socket.connect(*endpoint_iterator++, error);
			
		}
		if (error)
			throw boost::system::system_error(error);

		
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return connection;
}



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

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	auto& key = mouse_buttons[button];
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

struct A {
	void foo() { std::cout << "hello"; };
	void bar() {};
	void car() {};
};



int main()
{
	void(A:: * foo)() = &A::foo;
	std::cout << sizeof(foo) << std::endl;
	std::cout << foo << std::endl;
	int a;
	std::cout << sizeof(int) << std::endl;
	memcpy(&a, &foo, sizeof(foo));
	std::cout << a << std::endl;

	void(A:: * bar)() = &A::bar;
	memcpy(&a, &bar, sizeof(bar));
	std::cout << a << std::endl;

	void(A:: * car)() = &A::car;
	memcpy(&a, &car, sizeof(car));
	std::cout << a << std::endl;



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

	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetKeyCallback(window, key_callback);

	
	auto camera = std::make_shared<Camera>(glm::vec3(0.2, 4.5, 0.5));
	materialFactory.setCamera(camera);	
	
	

	std::shared_ptr<IChunkLoader> chunkLoader;
	bool singlePlayer = false;

	
	auto io_service = std::make_shared<boost::asio::io_service>();
	tcp_connection::pointer connection;

	udp_socket::pointer udp_socket;
	

	

	if (singlePlayer) {
		auto worldGenerator = std::make_shared<WorldGenerator>();
		chunkLoader = std::make_shared<ChunkLoader>(worldGenerator);
	}
	else {

		auto ip = "127.0.0.1";
		connection = connectToServer(ip, *io_service);
		if (!connection)
			return 1;

		udp_socket = udp_socket::create(*io_service);
		auto endpoint = connection->socket().remote_endpoint();
		udp_socket->socket().bind({ endpoint.address(), endpoint.port() });
		
		ConnectMessage connectMessage;
		connectMessage.address = udp_socket->socket().local_endpoint().address();
		connectMessage.udp_port = udp_socket->socket().local_endpoint().port();
		connectMessage.playerId = 0;
		connectMessage.send(*connection);
		

		chunkLoader = std::make_shared<RemoteChunkLoader>(connection);
	}

	auto networkThread = std::thread([=]() {

		if(connection)
			connection->start();
	});


	auto world = std::make_shared<World>(chunkLoader);

	

	auto streamWorld = std::make_shared<StreamWorldFromServer>(world, udp_socket);

	auto udpNetworkThread = std::thread([=]() {

		try
		{		
			if (streamWorld) {
				while (true) {
					streamWorld->recieve();
				}
			}
		}
		catch (std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}
	});
	

	auto player = std::make_shared<RemotePlayer>(world, glm::vec3(0.2,4.5,0.5));
	player->connection = connection;
	MainPlayerController mainPlayer = MainPlayerController(player, camera);
	world->addPlayer(player);

	Cow cow;
	auto server = std::make_shared<Cow::Server>();
	world->addEnitity(server);


	while (!glfwWindowShouldClose(window))
	{
		
		mainTime.update();
		glfwPollEvents();
		
		world->update();
		mainPlayer.update();
		
		glfwSwapBuffers(window);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		mouse.xoffset = mouse.yoffset = 0;
	}


	

	
	
	networkThread.join();
	glfwTerminate();
	return 0;
}
