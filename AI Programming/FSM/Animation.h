#pragma once

#include <vector>
#include <string>

class Animation
{
	public:
		Animation(char* _name, unsigned int* _frames, unsigned int length);
		unsigned int getLength();
		unsigned int getFrame(unsigned int index);
		const char* getName();

	private:
		std::string name;
		std::vector<unsigned int> frames;
};