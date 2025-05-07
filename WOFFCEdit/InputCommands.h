#pragma once

struct InputCommands
{
	bool forward;
	bool back;
	bool left;
	bool right;
	bool rotRight;
	bool rotLeft;
	bool up;
	bool down;
	bool lookUp;
	bool lookDown;

	//needed for object picking but not used for camera
	int mouse_x;
	int mouse_y;
	bool mouse_left;
	bool mouse_right;

	//terain
	bool t_pressed;
};
