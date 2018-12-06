#include "TextWindow.h"

struct Vec2 : public _COORD
{
	Vec2() {}
	Vec2(unsigned int a_X, unsigned int a_Y) { X = a_X; Y = a_Y; }
};

TextWindow::TextWindow()
{
	m_Buffer[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	m_Buffer[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
}

TextWindow::TextWindow(unsigned int a_Width, unsigned int a_Height) : TextWindow()
{
	ResizeScreenBuffers(a_Width, a_Height);
}

void TextWindow::setColor(int num)
{
	SetConsoleTextAttribute(m_Buffer[0], FOREGROUND_GREEN);
	SetConsoleTextAttribute(m_Buffer[1], 5);
}

void TextWindow::ResizeScreenBuffers(unsigned int a_Width, unsigned int a_Height)
{
	m_WindowSize = Vec2(a_Width, a_Height);
	SetConsoleScreenBufferSize(m_Buffer[0], Vec2(a_Width, a_Height));
	SetConsoleScreenBufferSize(m_Buffer[1], Vec2(a_Width, a_Height));
}

void TextWindow::RenderSprite(Sprite a_Sprite)
{
	SMALL_RECT l_TempRect;
	l_TempRect.Bottom = a_Sprite.GetPosition().Y + a_Sprite.GetSize().Y;
	l_TempRect.Left = a_Sprite.GetPosition().X;
	l_TempRect.Right = a_Sprite.GetPosition().X + a_Sprite.GetSize().X;
	l_TempRect.Top = a_Sprite.GetPosition().Y;

	//a_Sprite.GetBuffer()->Attributes = FOREGROUND_GREEN | BACKGROUND_BLUE;

	WriteConsoleOutputA(m_Buffer[!m_CurrentBuffer], a_Sprite.GetBuffer(),
		a_Sprite.GetSize(), Vec2(0, 0), &l_TempRect);
	

}

void TextWindow::SwapBackBuffers()
{
	m_CurrentBuffer = !m_CurrentBuffer;

	SetConsoleActiveScreenBuffer(m_Buffer[m_CurrentBuffer]);
	ClearBackBufferScreen();
}



void TextWindow::ClearBackBufferScreen()
{
	DWORD USELESS;
	FillConsoleOutputCharacterA(m_Buffer[!m_CurrentBuffer], ' ', m_WindowSize.X * m_WindowSize.Y, Vec2(0, 0), &USELESS);
	FillConsoleOutputAttribute(m_Buffer[!m_CurrentBuffer], 0x0000, m_WindowSize.X * m_WindowSize.Y, Vec2(0, 0), &USELESS);

}