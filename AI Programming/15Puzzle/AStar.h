#include "Configuration.h"
#include <iostream>
#include <vector>

class AStar
{
	private:
		//CAMPI
		vector<Configuration *> openList;
		Configuration* initialConfig;

		//METODI PRIVATI
		void AddNodeToOpenList(Configuration *prev, Configuration *node);
		void Search(vector<Configuration> &result);
		
		Configuration* VisitNode();
		Configuration* GetFront();
		
		void Clean();
	
	public:
		//METODI
		void Run(vector<Configuration> &result);
		void SetInitialConfiguration(Configuration *initConfig);
};