#include "Animation.h"

Animation::Animation(char* _name, unsigned int* _frames, unsigned int length)
{
	name.append(_name);
	frames.reserve(length);
	while (length--)
	{
		frames.push_back(_frames[frames.capacity() - length - 1]);
	}
}

unsigned int Animation::getLength()
{
	return frames.size();
}

unsigned int Animation::getFrame(unsigned int index)
{
	return frames[index];
}

const char* Animation::getName()
{
	return name.c_str();
}