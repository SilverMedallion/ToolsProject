#pragma once
#include "CommandInterface.h"
#include "DisplayChunk.h"
#include <vector>

class ManipulateTerrainCommand : public CommandInterface
{
public:
	ManipulateTerrainCommand(DisplayChunk& chunk);

	void InitialTerrainState();
	void ModifiedTerrainState();

	void Undo() override;
	void Redo() override;

private:
	DisplayChunk& m_chunk;
	std::vector<unsigned char> m_initialHeightmap;
	std::vector<unsigned char> m_finalHeightmap;
};

