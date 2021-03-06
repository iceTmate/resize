#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "graphics/graphics.hpp"
#include "gameinputcontroller.hpp"
#include "graphics/renderer.hpp"
#include "gameworld.hpp"
//#include "game/game.hpp"

int main()
{
	Graphics graphics;
	if (!graphics.init())
		return 0;

	graphics.m_camera = std::shared_ptr<Camera>(new Camera());
	graphics.m_camera->m_pos = glm::vec3(5, 5, 16);
	graphics.m_camera->setDir(glm::vec3(0, 0.00001f, -1));
	graphics.m_camera->m_lense.setPerspective(65.f, 1.f, .1f, 1000.f);

	GameWorld gameWorld;

	GameInputController gameInputController(&graphics, &gameWorld);

	//Game game;
	//if (!game.init())
	//	return 0;

	std::cout << "running game..." << std::endl;

	using namespace std::chrono_literals;
	std::chrono::steady_clock clock;
	auto beginTime = clock.now();
	auto prevTime = beginTime;
	auto curTime = beginTime;
	auto deltaTime = 0ms;

	while (!glfwWindowShouldClose(graphics.window())) {
		glfwPollEvents();
		if (glfwGetKey(graphics.window(), GLFW_KEY_ESCAPE))
			glfwSetWindowShouldClose(graphics.window(), true);

		//graphics.m_camera->m_pos.z += std::chrono::duration_cast<std::chrono::milliseconds>(deltaTime).count() / 600.f;
		gameInputController.update(deltaTime);
		//game.update(deltaTime);
		
		graphics.update();
		graphics.render(&gameWorld);

		curTime = clock.now();
		deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(curTime - prevTime);
		std::this_thread::sleep_for(std::max(0ms, 1000ms / 30 - deltaTime));
		prevTime = clock.now();

		//std::cout << getchar() << std::endl;
	}

	return 0;
}
