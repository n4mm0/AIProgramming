#include "AStar.h"

void AStar::Run(const Configuration& _configToSolve, std::vector<Configuration>& result)
{
	Node* nStart = new Node(_configToSolve);
	AddNodeToOpenList(NULL, nStart);

	Node* currentNode = NULL;
	while (!qOpenList.empty())
	{
		currentNode = VisitNode();
		if (currentNode->H == 0)
		{
			//Fine
			break;
		}
	}

	while (currentNode != NULL)
	{
		result.push_back(currentNode->cConfig);
		currentNode = currentNode->previous;
	}
}

void AStar::Clean()
{
	qOpenList.clear();
	qClosedList.clear();
}

Node* AStar::VisitNode()
{
	Node* node = GetFront();
	node->state = NodeState::Closed;
	qClosedList.push_back(node);

	node->createAdjs();

	std::list<Node*>::iterator adj;
	for (adj = node->lAdjs.begin(); adj != node->lAdjs.end(); adj++)
	{
		AddNodeToOpenList(node, *adj);
	}
	
	return node;
}

void AStar::AddNodeToOpenList(Node* pParent, Node* pNode)
{
	int cost;
	if (pParent != NULL) cost = pParent->G + 1;
	else cost = 0;

	switch (pNode->state)
	{
		case NodeState::Open: 
			if (cost < pNode->G)
			{
				//qOpenList.remove(pNode);
			}
			break;

		case NodeState::Closed:
			if (pNode->G > cost)
			{
				/*pNode->state = NodeState::Open;
				qOpenList.push_back(pNode);*/
			}
			break;

		case NodeState::Unknown:
		{
			pNode->G = cost;
			pNode->F = pNode->G + pNode->H;
			pNode->previous = pParent;
			pNode->state = NodeState::Open;

			std::vector<Node*>::iterator iter;
			for (iter = qOpenList.begin(); iter != qOpenList.end(); ++iter)
			{
				if ((*iter)->cConfig == pNode->cConfig)
				{
					if (pNode->G < (*iter)->G)
					{
						qOpenList.erase(iter);
						break;
					}
					else
					{
						return;
					}
				}
			}

			bool isInserted = false;
			for (iter = qOpenList.begin(); iter != qOpenList.end(); ++iter)
			{
				if ((*iter)->F > pNode->F)
				{
					qOpenList.insert(iter, pNode);
					isInserted = true;
					break;
				}
			}

			if (!isInserted)
				qOpenList.push_back(pNode);
			break;
		}

		default:
			break;
	}
}

Node* AStar::GetFront()
{
	std::vector<Node*>::iterator iter = qOpenList.begin();
	for ( ; iter != qOpenList.end() && (*iter)->state != NodeState::Open; ++iter)
	{ }
	Node* front = *iter;
	qOpenList.erase(iter);
	return front;
}