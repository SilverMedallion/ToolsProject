#pragma once
#include "SceneObject.h"
#include "CommandInterface.h"
#include <stack>

#pragma once
class CommandManager
{
public:
	void ExecuteCommand(CommandInterface* command)
	{
		//execute the command passed in 
		command->Execute();
		//add it to the undo stack
		m_undoStack.push(command);
		ClearStack(m_redoStack);

	}

	void Undo()
	{
		//check that the undo stack populated before attempting
		if (!m_undoStack.empty())
		{
			CommandInterface* command = m_undoStack.top();
			m_undoStack.pop();
			command->Undo();
			m_redoStack.push(command);
		}
	}

	void Redo()
	{
		if (!m_redoStack.empty())
		{
			CommandInterface* command = m_redoStack.top();
			m_redoStack.pop();
			command->Redo();
			m_undoStack.push(command);
		}
	}

	void ClearStack(std::stack<CommandInterface*>& stack) {
		while (!stack.empty())
		{
			stack.pop();
		}
	}


private:
	std::stack<CommandInterface*> m_undoStack;
	std::stack<CommandInterface*> m_redoStack;
};

