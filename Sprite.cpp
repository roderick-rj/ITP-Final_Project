#include "Sprite.h"
#include <iostream>

Sprite::Sprite() {}

Sprite::~Sprite()
{
	if (m_Buffer != nullptr) {
		delete[] m_Buffer;
	}
}
Sprite::Sprite(const Sprite &a_Other)
{
	m_Size = a_Other.m_Size;
	m_Position = a_Other.m_Position;
	m_Buffer = new CHAR_INFO[a_Other.m_Size.X * a_Other.m_Size.Y];
	std::memcpy(m_Buffer, a_Other.m_Buffer, a_Other.m_Size.X * a_Other.m_Size.Y * sizeof(CHAR_INFO));
}
Sprite::Sprite(const char *m_Characters, const unsigned int a_Width, const unsigned int a_Height)
{
	m_Buffer = new CHAR_INFO[a_Height * a_Width];
	for (unsigned int i = 0; i < a_Width * a_Height; i++)
	{	
		m_Buffer[i].Char.AsciiChar = m_Characters[i];
		m_Buffer[i].Attributes = 4;
		
	}

	m_Size = Vec2(a_Width, a_Height);
}

void Sprite::SetSprite(const char *m_Characters, const unsigned int a_Width, const unsigned int a_Height)
{
	if (m_Buffer != nullptr)
	{
		delete[] m_Buffer;
	}

	m_Buffer = new CHAR_INFO[a_Height * a_Width];

	for (unsigned int i = 0; i < a_Width * a_Height; i++)
	{
		m_Buffer[i].Char.AsciiChar = m_Characters[i];
		if (m_Buffer[i].Char.AsciiChar == '*') {
			m_Buffer[i].Attributes = 0;
		}
		else if (m_Buffer[i].Char.AsciiChar == '-') {
			m_Buffer[i].Attributes = BACKGROUND_BLUE | FOREGROUND_BLUE;
		}
		else if (m_Buffer[i].Char.AsciiChar == '#') {
			m_Buffer[i].Attributes = 51;
		}
		else if (m_Buffer[i].Char.AsciiChar == '+') {
			m_Buffer[i].Attributes = BACKGROUND_RED | FOREGROUND_RED;
		}
		else if (m_Buffer[i].Char.AsciiChar == '=') {
			m_Buffer[i].Attributes = BACKGROUND_RED | BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_BLUE;
		}
		else {
			m_Buffer[i].Attributes = 3;
		}
		
		
	}

	m_Size = Vec2(a_Width, a_Height);
}

COORD Sprite::GetPosition() const
{
	return m_Position;
}

COORD Sprite::GetSize() const
{
	return m_Size;
}

void Sprite::SetPosition(const unsigned int a_X, unsigned int a_Y)
{
	m_Position = Vec2(a_X, a_Y);
}

CHAR_INFO *Sprite::GetBuffer()
{
	return m_Buffer;
}