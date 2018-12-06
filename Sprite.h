#pragma once
#include <Windows.h>

class Sprite
{
public:
	Sprite();
	Sprite(const char *m_Characters, const unsigned int a_Width, const unsigned int a_Height);
	Sprite(const Sprite &a_Other);
	~Sprite();
	void SetSprite(const char *m_Characters, const unsigned int a_Width, const unsigned int a_Height);
	//returns COORD name is GetPosition (Parameters) const nothing in the class will change in terms of values
	COORD GetPosition() const;

	COORD GetSize() const;

	void SetPosition(const unsigned int a_X, unsigned int a_Y);

	CHAR_INFO *GetBuffer();

private:

	struct Vec2 : public _COORD
	{
		Vec2() {}
		Vec2(unsigned int a_X, unsigned int a_Y) { X = a_X; Y = a_Y; }
	};
	//The buffer to contain the sprite info such as char and colour
	CHAR_INFO *m_Buffer;
	//position
	Vec2 m_Position;
	//height and width
	Vec2 m_Size;
};


//class AnimatedSprite : public Sprite
//{
//public:
//	AnimatedSprite();
//	void AddSprite(char *);
//private:
//	float m_RateOfAnimation;
//	struct LinkedList 
//	{
//		Sprite *m_First;
//		Sprite *m_Next;
//		Sprite *m_Last;
//
//	};
//};
