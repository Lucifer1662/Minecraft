#pragma once
#include <unordered_map>
#include <glm/glm.hpp>
#include "Chunk.h"
#include <memory>
#include <vector>
#include "Event.h"
#include "IVec3KeyHasher.h"
#include "ChunkLoader.h"
#include <optional>
#include <memory>
#include "PlayerID.h"
#include "Player.h"
#include "IUpdate.h"


class World
{
	
	std::unordered_map<glm::ivec3, std::shared_ptr<Chunk>, IVec3KeyHasher> chunks;
	std::vector<std::shared_ptr<Player>> players;
	std::vector<std::shared_ptr<IUpdate>> entities;
	std::shared_ptr<IChunkLoader> chunkLoader;

public:
	static std::shared_ptr<World> mainWorld;
	World(const World&) = default;
	World(World&&) = default;
	World(std::shared_ptr<IChunkLoader> chunkLoader);
	World& operator=(const World& c) = default;
	World& operator=(World&& c) = default;


	Event<void, std::shared_ptr<Chunk>> newChunkloaded;
	std::shared_ptr<Chunk> getChunkAt(const glm::vec3& position);
	std::shared_ptr<Chunk> getChunkAtChunkPos(const glm::ivec3 worldPosition);
	std::shared_ptr<Block> getBlockAt(const glm::vec3& position);
	void addChunk(const glm::ivec3& chunkPosition, std::shared_ptr<Chunk> chunk);
	std::shared_ptr<Block> blockFromRay(glm::vec3 start, const glm::vec3& dir);
	std::optional<glm::ivec3> blockPositionFromRay(glm::vec3 start, glm::vec3 dir);
	std::optional<glm::vec3> rayCastDown(const glm::vec3& position);
	static glm::ivec3 worldToChunkPos(const glm::vec3& worldPosition);

	void addPlayer(std::shared_ptr<Player> player);
	void addEnitity(std::shared_ptr<IUpdate> entity);
	void update();

	std::shared_ptr<Player> getPlayerOfId(PlayerID id);
	std::vector<std::shared_ptr<Player>>& getPlayers();
};

