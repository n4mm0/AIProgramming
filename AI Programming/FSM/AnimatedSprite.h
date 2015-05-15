#pragma once

/*
To-Do: loop, speed
*/

#include "SFML\Graphics.hpp"
#include <vector>
#include "Animation.h"

typedef std::vector<Animation> vecAnim;

class AnimatedSprite : public sf::Sprite
{
	public:
		AnimatedSprite(unsigned int _fw, unsigned int _fh);
		AnimatedSprite(const AnimatedSprite& other);
		~AnimatedSprite();

		void Update(const sf::Vector2f& _position); //Updates position and animation

		void addAnim(char* _name, unsigned int* _frames, unsigned int _length, bool _loop);
		void playAnim(char* _name);
		void stopAnim();
		void pauseAnim();
		void resumeAnim();
		unsigned int getFrameWidth() const;
		unsigned int getFrameHeight() const;

	private:
		vecAnim animations;
		Animation* currAnim;
		unsigned int currFrame;
		unsigned int frameWidth;
		unsigned int frameHeight;
		bool isPlaying;
		bool isPaused;
};