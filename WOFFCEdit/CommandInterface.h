#pragma once
class CommandInterface
{
public:
	CommandInterface();
	virtual ~CommandInterface();

	//execute action
	virtual void Execute() = 0;

	//undo action
	virtual void Undo() = 0;

	//redo action
	virtual void Redo() = 0;


		
};

