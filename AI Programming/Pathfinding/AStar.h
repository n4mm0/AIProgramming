#pragma once

#include <iostream>
#include <list>
#include "Node.h"
#include <vector>
#include "Configuration.h"

class AStar
{
	public:
		void Run(const Configuration& _configToSolve, std::vector<Configuration>& result);

	private:
		Node* VisitNode();
		Node* GetFront();
		void AddNodeToOpenList(Node* pParent, Node* pNode);
		void Clean();

		std::vector<Node*> qOpenList;
		std::vector<Node*> qClosedList;
};