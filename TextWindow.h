#pragma once
//need to include to access api
#include <Windows.h>
#include "Sprite.h"


class Sprite;

class TextWindow
{
public:
	//constructors
	TextWindow();
	//specify size of buffers for console
	TextWindow(unsigned int a_Width, unsigned int a_Height);

	void ResizeScreenBuffers(unsigned int a_Width, unsigned int a_Height);

	void RenderSprite(Sprite a_Sprite);

	void SwapBackBuffers();

	void setColor(int num);

private:

	void ClearBackBufferScreen();
	//windows handle things
	//used to access api variables
	HANDLE m_Buffer[2]; //2 buffers to flip back buffer and reduce visual lag
	//keep track of what the current buffer is
	bool m_CurrentBuffer = false;
	COORD m_WindowSize;
};
