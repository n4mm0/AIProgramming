#include "NodeState.h"
#include <vector>

using namespace std;

struct Configuration
{
	//CAMPI
	int f = 0;
	int h = 0;
	int g = 0;
	int BlankPosition;
	int Config[16];

	vector<Configuration *> adjConfig;
	Configuration *prev;
	NodeState state = NodeState::Open;

	//COSTRUTTORI
	Configuration();
	Configuration(const Configuration& other);
	
	//DISTRUTTORE
	~Configuration();

	//METODI
	void ComputeConfigurationHeuristic();
	void SetConfig(int *conf);
	void ComputeAdj();
	void findIndexOfBlankPosition();

	bool operator==(const Configuration& other) const;
};