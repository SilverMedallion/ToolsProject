#include "MoveObjectCommand.h"

MoveObjectCommand::MoveObjectCommand(DisplayObject* obj, const PositionData& oldData, const PositionData& newData) : m_Object(obj), m_oldData(oldData), m_newData(newData)
{
}

void MoveObjectCommand::Execute() 
{
	ApplyPositionData(m_newData); //appy new data to object
}

void MoveObjectCommand::Undo()
{
	ApplyPositionData(m_oldData);  //revert object to old data
}

void MoveObjectCommand::Redo()
{
	ApplyPositionData(m_newData);  //reapply new data same as execute
}
void MoveObjectCommand::ApplyPositionData(const PositionData& data)
{
	m_Object->m_position.x = data.posX;
	m_Object->m_position.y = data.posY;
	m_Object->m_position.z = data.posZ;
	
}




