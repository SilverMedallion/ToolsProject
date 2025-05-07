#include "ManipulateTerrainCommand.h"

ManipulateTerrainCommand::ManipulateTerrainCommand(DisplayChunk& chunk) : m_chunk(chunk) {}


void ManipulateTerrainCommand::InitialTerrainState()
{
	m_initialHeightmap.assign(std::begin(m_chunk.m_heightMap), std::end(m_chunk.m_heightMap));
}

void ManipulateTerrainCommand::ModifiedTerrainState()
{
	m_finalHeightmap.assign(std::begin(m_chunk.m_heightMap), std::end(m_chunk.m_heightMap));
}

void ManipulateTerrainCommand::Undo()
{
	std::copy(m_initialHeightmap.begin(), m_initialHeightmap.end(), std::begin(m_chunk.m_heightMap));
	m_chunk.UpdateTerrain();
	m_chunk.CalculateTerrainNormals();
}

void ManipulateTerrainCommand::Redo()
{
	std::copy(m_finalHeightmap.begin(), m_finalHeightmap.end(), std::begin(m_chunk.m_heightMap));
	m_chunk.UpdateTerrain();
	m_chunk.CalculateTerrainNormals();
}
