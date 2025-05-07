#ifndef MOVE_OBJECT_COMMAND_H
#define MOVE_OBJECT_COMMAND_H


#include "DisplayObject.h"
#include "CommandInterface.h"
#include "d3d11.h"
#include <SimpleMath.h>

struct PositionData
{
	float posX, posY, posZ;
};
class MoveObjectCommand : public CommandInterface
{
public:
	MoveObjectCommand(DisplayObject* obj, const PositionData& oldData, const PositionData& newData);

	void Execute() override;
	void Undo() override;
	void Redo() override;
	void ApplyPositionData(const PositionData& data);
	
private:
	DisplayObject* m_Object;
	PositionData m_oldData;
	PositionData m_newData;
	
};

#endif 