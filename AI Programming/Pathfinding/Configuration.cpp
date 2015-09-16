#include "Configuration.h"
#include <random>

Configuration::Configuration()
{
	for (int i = 0; i < 16; ++i)
	{
		iConfig[i] = i + 1;
	}
}

Configuration::Configuration(const Configuration& other)
{
	for (int i = 0; i < 16; ++i)
	{
		iConfig[i] = other.getElementAt(i);
	}
}

void Configuration::setConfiguration(int* _config)
{
	for (int i = 0; i < 16; ++i)
	{
		iConfig[i] = _config[i];
	}
}

void Configuration::swapElements(int first, int second)
{
	int temp = iConfig[first];
	iConfig[first] = iConfig[second];
	iConfig[second] = temp;
}

int Configuration::getElementAt(int _position) const
{
	return iConfig[_position];
}

int Configuration::getBlankPosition()
{
	for (int i = 0; i < 16; ++i)
	{
		//16 simboleggia la posizione senza numero
		if (iConfig[i] == 16) return i;
	}
	return -1; //Error
}

bool Configuration::operator==(const Configuration& other) const
{
	bool result = true;

	for (int i = 0; i < 16; ++i)
	{
		result = result && (iConfig[i] == other.iConfig[i]);
	}
	
	return result;
}