#include "Configuration.h"

//COSTRUTTORI
Configuration::Configuration()
{
}

Configuration::Configuration(const Configuration& other)
{
	for (int i = 0; i < 16; ++i)
		Config[i] = other.Config[i];

	BlankPosition = other.BlankPosition;
	prev = other.prev;
}

//DISTRUTTORE
Configuration::~Configuration()
{
	vector<Configuration *>::iterator adjEnd(adjConfig.end());
	for (vector<Configuration*>::iterator iter = adjConfig.begin(); iter != adjEnd; ++iter)
		delete 	*iter;
	adjConfig.clear();
}

//METODI
void Configuration::ComputeConfigurationHeuristic()
{
	int val;
	for (int i = 0; i < 16; ++i)
	{
		val = Config[i] - 1;
		int j = abs(i / 4 - val / 4) + abs(i % 4 - val % 4);
		h += j;
	}
}

void Configuration::SetConfig(int* conf)
{
	for (int i = 0; i < 16; ++i)
		Config[i] = conf[i];
}

void Configuration::ComputeAdj()
{
	Configuration* tmp;
	if (BlankPosition % 4 < 3)
	{
		tmp = new Configuration(*this);
		swap(tmp->Config[BlankPosition], tmp->Config[BlankPosition + 1]);
		tmp->BlankPosition = BlankPosition + 1;
		tmp->ComputeConfigurationHeuristic();
		adjConfig.push_back(tmp);
	}
	if (BlankPosition % 4>0)
	{
		tmp = new Configuration(*this);
		swap(tmp->Config[BlankPosition], tmp->Config[BlankPosition - 1]);
		tmp->BlankPosition = BlankPosition - 1;
		tmp->ComputeConfigurationHeuristic();
		adjConfig.push_back(tmp);
	}
	if (BlankPosition < 12)
	{
		tmp = new Configuration(*this);
		swap(tmp->Config[BlankPosition], tmp->Config[(BlankPosition / 4 + 1) * 4 + BlankPosition % 4]);
		tmp->BlankPosition = (BlankPosition / 4 + 1) * 4 + BlankPosition % 4;
		tmp->ComputeConfigurationHeuristic();
		adjConfig.push_back(tmp);
	}
	if (BlankPosition>3)
	{
		tmp = new Configuration(*this);
		swap(tmp->Config[BlankPosition], tmp->Config[(BlankPosition / 4 - 1) * 4 + BlankPosition % 4]);
		tmp->BlankPosition = (BlankPosition / 4 - 1) * 4 + BlankPosition % 4;
		tmp->ComputeConfigurationHeuristic();
		adjConfig.push_back(tmp);
	}
}

void Configuration::findIndexOfBlankPosition()
{
	for (int index = 0; index < 16; ++index)
		if (Config[index] == 16)
			BlankPosition = index;
}

bool Configuration::operator==(const Configuration& other) const
{
	bool result = true;
	for (int i = 0; i < 16 && result; ++i)
	{
		result = (Config[i] == other.Config[i]);
	}
	return result;
}