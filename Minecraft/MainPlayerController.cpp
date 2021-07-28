#include "MainPlayerController.h"
#include "Mouse.h"
#include "glm/glm.hpp"

const glm::vec3 MainPlayerController::cameraOffset = glm::vec3(0,1.5f,0);

MainPlayerController::MainPlayerController(std::shared_ptr<Player> player, std::shared_ptr<Camera> camera)
    : camera(camera), player(player), cameraController(*camera), worldRenderer(player->getWorld())
{
}

void MainPlayerController::update()
{
    //cameraController.ProccessKeyboard();
    ProccessKeyboard();
    cameraController.ProcessMouseMovement(mouse.xoffset, mouse.yoffset);
	camera->position = player->getPosition() + cameraOffset;

    if (keys[GLFW_KEY_SPACE].pressed) {
        player->jump();
    }


	if (mouse_buttons[GLFW_MOUSE_BUTTON_1].pressed) {
		glm::vec3 direction = { 0.0f, -0.7f, -1.0f };
		auto blockPos = player->getWorld()->blockPositionFromRay(camera->position, camera->front);
		if (blockPos) {
			auto chunk = player->getWorld()->getChunkAt(glm::vec3(*blockPos));
			auto& block = chunk->blockAt(*blockPos);
			block.reset();
			auto blocks = std::vector<glm::ivec3>({ *blockPos });
			chunk->blocksBrokenEvent(blocks);
		}
	}

	worldRenderer.position = player->getPosition();
	worldRenderer.render();
}



void MainPlayerController::ProccessKeyboard() {
    auto dir = glm::vec2(0, 0);
    if (forwardKey.heldDown) {
        dir.x += camera->front.x;
        dir.y += camera->front.z;
    }
    if (rightKey.heldDown) {
        dir.x += cameraController.right.x;
        dir.y += cameraController.right.z;
    }
    if (backwardsKey.heldDown) {
        dir.x -= camera->front.x;
        dir.y -= camera->front.z;
    }
    if (leftKey.heldDown) {
        dir.x -= cameraController.right.x;
        dir.y -= cameraController.right.z;
    }

    if(dir.x != 0 && dir.y != 0)
        dir = glm::normalize(dir);

    if (oldDirection != dir) {
        player->move(dir);
        oldDirection = dir;
    }
}
