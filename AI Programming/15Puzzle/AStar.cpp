#include "AStar.h"

//METODI PRIVATI
void AStar::AddNodeToOpenList(Configuration *prev, Configuration *node)
{
	node->prev = prev;
	node->g = (prev == NULL) ? 0 : prev->g + 1;
	node->f = node->g + node->h;
	node->state = NodeState::Open;

	vector<Configuration*>::iterator end = openList.end();
	for (vector<Configuration*>::iterator iter = openList.begin(); iter != end; ++iter)
		if (*(*iter) == *node)
			if ((*iter)->g > node->g)
			{
				openList.erase(iter);
				break;
			}
			else
			{
				return;
			}

	bool isInserted = false;
	vector<Configuration*>::iterator ListEnd = openList.end();
	for (vector<Configuration*>::iterator iter = openList.begin(); iter != ListEnd; ++iter)
	{
		Configuration* iterNode(*iter);
		if (iterNode->f > node->f)
		{
			openList.insert(iter, node);
			isInserted = true;
			break;
		}
	}

	if (!isInserted)
		openList.push_back(node);
}

void AStar::Search(vector<Configuration> &result)
{
	Configuration* currentNode = NULL;
	bool end = false;
	while (!openList.empty() && !end)
	{
		currentNode = VisitNode();
		end = currentNode->h == 0;
	}

	while (currentNode != NULL)
	{
		result.push_back(*currentNode);
		currentNode = currentNode->prev;
	}
}

Configuration* AStar::VisitNode()
{
	Configuration *currentNode = GetFront();
	currentNode->state = NodeState::Closed;
	currentNode->ComputeAdj();
	vector<Configuration *>::iterator adjEnd(currentNode->adjConfig.end());
	
	for (vector<Configuration*>::iterator iter = currentNode->adjConfig.begin(); iter != adjEnd; ++iter)
		AddNodeToOpenList(currentNode, *iter);
	
	return currentNode;
}

Configuration* AStar::GetFront()
{
	vector<Configuration *>::iterator End(openList.end());
	vector<Configuration*>::iterator iter = openList.begin();
	for (; iter != End && (*iter)->state != NodeState::Open; ++iter)
	{
	}
	return *iter;
}

void AStar::Clean()
{
	vector<Configuration *>::iterator adjEnd(initialConfig->adjConfig.end());
	for (vector<Configuration*>::iterator iter = initialConfig->adjConfig.begin(); iter != adjEnd; ++iter)
	{
		delete 	*iter;
	}
	openList.clear();
	initialConfig->adjConfig.clear();
}

//METODI
void AStar::Run(vector<Configuration> &result)
{
	Search(result);
	Clean();
}

void AStar::SetInitialConfiguration(Configuration *initConfig)
{
	AddNodeToOpenList(NULL, initConfig);
	initialConfig = initConfig;
}