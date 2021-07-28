#include "World.h"
#include "Player.h"


std::shared_ptr<World> World::mainWorld;

World::World(std::shared_ptr<IChunkLoader> chunkLoader) : chunkLoader(chunkLoader)
{
}

std::shared_ptr<Chunk> World::getChunkAt(const glm::vec3& worldPosition)
{
    return getChunkAtChunkPos(worldToChunkPos(worldPosition));
}

std::shared_ptr<Chunk> World::getChunkAtChunkPos(const glm::ivec3 chunkPosition)
{
    auto it = chunks.find(chunkPosition);
    if (it == chunks.end()) {
        auto chunk = chunkLoader->loadChunk(chunkPosition);
        chunks.insert_or_assign(chunkPosition, chunk);
        newChunkloaded(chunk);
        return chunk;
    }
    return it->second;
}

std::shared_ptr<Block> World::getBlockAt(const glm::vec3& worldPosition)
{
    return getChunkAt(worldPosition)->blockAt(worldPosition);
}

void World::addChunk(const glm::ivec3& chunkPosition, std::shared_ptr<Chunk> chunk)
{
    chunks[chunkPosition] = chunk;
}

glm::ivec3 closestNextBlock(const glm::vec3& start, const glm::vec3& dir, glm::vec3& closestPoint) {
    auto floor_start = floor(start);
    auto isolate_start = start - floor_start;
    auto toCenter = glm::vec3(0.5f,0.5f,0.5f) - isolate_start;
    glm::vec3 offset = { -1,-1,-1 };

    auto smallestDis = 10000.0f;
    glm::ivec3 smallest;
    std::array<glm::ivec3, 6> offsets = {
        glm::ivec3(-1,0,0),
        glm::ivec3(1,0,0),
        glm::ivec3(0,1,0),
        glm::ivec3(0,-1,0),
        glm::ivec3(0,0,1),
        glm::ivec3(0,0,-1)
    };

   for(auto& offset : offsets){
        auto p = toCenter + glm::vec3(offset);
        auto t = glm::dot(p, dir);
        if (t > 0) {
            auto v = dir * t;
            auto dis = glm::distance(v, p);
            if (dis < smallestDis) {
                smallestDis = dis;
                smallest = offset;
                closestPoint = v + start;
            }
        }
    }

    return smallest + glm::ivec3(floor_start);
}

std::optional<glm::ivec3> World::blockPositionFromRay(glm::vec3 start, glm::vec3 dir)
{

    dir = glm::normalize(dir);
    std::shared_ptr<Block> block;
    glm::vec3 closest;
    glm::ivec3 blockPos;
    size_t i = 0;
    do {
        blockPos = closestNextBlock(start, dir, closest);
        start = closest;
        block = getBlockAt(blockPos);
        if (i > 5) {
            return {};
        }
        i++;
    } while (!block);

    return blockPos;
}

std::optional<glm::vec3> World::rayCastDown(const glm::vec3& position)
{
    auto chunk = getChunkAt(position);
    std::shared_ptr<Block> block;
    glm::ivec3 p = floor(position);
    do {
        block = chunk->blockAt(p);
       
        if (p.y < 0) {
            return {};
        }
        p.y -= 1;
    } while (!block || !block->isSolid());

    return glm::vec3(position.x, p.y + 2, position.z);
}

glm::ivec3 World::worldToChunkPos(const glm::vec3& worldPosition)
{
    glm::ivec3 chunkPosition = glm::ivec3(worldPosition) / glm::ivec3(Chunk::chunkWidth, Chunk::chunkHeight, Chunk::chunkWidth);
    if (worldPosition.x < 0) chunkPosition.x--;
    if (worldPosition.y < 0) chunkPosition.y--;
    if (worldPosition.z < 0) chunkPosition.z--;
    return chunkPosition;
}

std::shared_ptr<Block> World::blockFromRay(glm::vec3 start, const glm::vec3& dir)
{

    std::shared_ptr<Block> block;
    glm::vec3 closest;
    do {
        
        auto blockPos = closestNextBlock(start, dir, closest);
        start = closest;
        block = getBlockAt(blockPos);

    } while (!block);

    return block;
}

void World::update() {
    for (auto& player : players) {
        player->update();
    }

    for (auto& entity : entities) {
        entity->update();
    }
}

void World::addPlayer(std::shared_ptr<Player> player) {
    players.push_back(player);
}

void World::addEnitity(std::shared_ptr<IUpdate> entity)
{
    entities.push_back(entity);
}

std::shared_ptr<Player> World::getPlayerOfId(PlayerID id)
{
    for (auto& player : players) {
        if (player->getPlayerID() == id) {
            return player;
        }
    }
    return {};
}

std::vector<std::shared_ptr<Player>>& World::getPlayers()
{
    return players;
}
