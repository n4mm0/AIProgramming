#include "AnimatedSprite.h"

//Width and height of a single frame of the spritesheet. FYI, all frames should have the same size!
AnimatedSprite::AnimatedSprite(unsigned int _fw, unsigned int _fh) : Sprite(), frameWidth(_fw), frameHeight(_fh) {}

AnimatedSprite::~AnimatedSprite()
{
	animations.clear();
}

void AnimatedSprite::Update(const sf::Vector2f& _position)
{
	setPosition(_position);

	if (currAnim != nullptr && !isPaused)
	{
		unsigned int animIndex = currFrame / 256;
		if (animIndex >= currAnim->getLength())
		{
			currFrame = 0;
			animIndex = 0;
		}
		unsigned int framePerRow = getTexture()->getSize().x / frameWidth;
		unsigned int frameIndex = currAnim->getFrame(animIndex);
		unsigned int frameWidthOffset = (frameIndex - framePerRow*(frameIndex / framePerRow))*frameWidth;
		unsigned int frameHeightOffset = (frameIndex / framePerRow) * frameHeight;
		++currFrame;

		setTextureRect(sf::IntRect(frameWidthOffset, frameHeightOffset, frameWidth, frameHeight));
	}
}

void AnimatedSprite::addAnim(char* _name, unsigned int* _frames, unsigned int _length, bool _loop)
{
	Animation newAnim(_name, _frames, _length);
	animations.push_back(newAnim);
}

void AnimatedSprite::playAnim(char* _name)
{
	vecAnim::iterator iter;
	for (iter = animations.begin(); iter != animations.end(); ++iter)
	{
		if (strcmp(iter->getName(), _name) == 0)
		{
			currAnim = &(*iter); //WOW!!!11
			isPlaying = true;
		}
	}
}

void AnimatedSprite::stopAnim()
{
	currAnim = nullptr;
	currFrame = 0;
	isPlaying = false;
	isPaused = false;
}

void AnimatedSprite::pauseAnim()
{
	if (isPlaying)
	{
		isPaused = true;
	}
}

void AnimatedSprite::resumeAnim()
{
	if (isPaused && isPlaying)
	{
		isPaused = false;
	}
}